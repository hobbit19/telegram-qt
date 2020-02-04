#include "ClientHelpOperation.hpp"

#include "DataStorage.hpp"
#include "ClientBackend.hpp"
#include "ClientConnection.hpp"
#include "ClientRpcLayer.hpp"
#include "ClientRpcHelpLayer.hpp"
#include "PendingRpcOperation.hpp"

#include "RpcError.hpp"

#ifdef DEVELOPER_BUILD
#include "MTProto/TLTypesDebug.hpp"
#endif

#include <QLoggingCategory>

namespace Telegram {

namespace Client {

HelpOperation::HelpOperation(QObject *parent) :
    PendingOperation(parent)
{
}

void HelpOperation::setBackend(Backend *backend)
{
    m_backend = backend;
}

void HelpOperation::setRunMethod(HelpOperation::RunMethod method)
{
    m_runMethod = method;
}

void HelpOperation::startImplementation()
{
    if (m_runMethod) {
        callMember<>(this, m_runMethod);
    }
}

PendingOperation *HelpOperation::requestDcConfig()
{
    PendingRpcOperation *requestCodeOperation = helpLayer()->getConfig();
    connect(requestCodeOperation, &PendingRpcOperation::finished, this, &HelpOperation::onGetDcConfigurationFinished);
    return requestCodeOperation;
}

HelpRpcLayer *HelpOperation::helpLayer() const
{
    return m_backend->helpLayer();
}

void HelpOperation::onGetDcConfigurationFinished(PendingRpcOperation *operation)
{
    if (operation->isFailed()) {
        setFinishedWithError(operation->errorDetails());
        return;
    }
    TLConfig result;
    helpLayer()->processReply(operation, &result);
    if (!result.isValid()) {
        setFinishedWithError(operation->errorDetails());
        return;
    }
    DcConfiguration config;
    for (const TLDcOption &opt : result.dcOptions) {
        DcOption o;
        o.id = opt.id;
        o.flags = opt.flags;
        o.address = opt.ipAddress;
        o.port = opt.port;
        config.dcOptions.append(o);
    }
    Connection *c = Connection::fromOperation(operation);
    DcOption thisOpt = c->dcOption();
    thisOpt.id = result.thisDc;
    c->setDcOption(thisOpt);
    config.testMode = result.testMode;
    config.chatSizeMax = result.chatSizeMax;
    config.megagroupSizeMax = result.megagroupSizeMax;
    config.forwardedCountMax = result.forwardedCountMax;
    config.onlineCloudTimeoutMs = result.onlineCloudTimeoutMs;
    config.onlineUpdatePeriodMs = result.onlineUpdatePeriodMs;
    config.offlineBlurTimeoutMs = result.offlineBlurTimeoutMs;
    config.offlineIdleTimeoutMs = result.offlineIdleTimeoutMs;
    config.meUrlPrefix = result.meUrlPrefix;
    m_backend->dataStorage()->setServerConfiguration(config);
    setFinished();
}

} // Client

} // Telegram namespace
