
SOURCES += $$PWD/LocalCluster.cpp
SOURCES += $$PWD/ServerDhLayer.cpp
SOURCES += $$PWD/ServerRpcLayer.cpp
SOURCES += $$PWD/ServerRpcOperation.cpp
SOURCES += $$PWD/RpcOperationFactory.cpp
SOURCES += $$PWD/TelegramServer.cpp
SOURCES += $$PWD/TelegramServerClient.cpp
SOURCES += $$PWD/TelegramServerUser.cpp
SOURCES += $$PWD/CServerTcpTransport.cpp
SOURCES += $$PWD/RemoteServerConnection.cpp
SOURCES += $$PWD/FunctionStreamOperators.cpp

HEADERS += $$PWD/DcConfiguration.hpp
HEADERS += $$PWD/LocalCluster.hpp
HEADERS += $$PWD/ServerDhLayer.hpp
HEADERS += $$PWD/ServerRpcLayer.hpp
HEADERS += $$PWD/ServerRpcOperation.hpp
HEADERS += $$PWD/RpcOperationFactory.hpp
HEADERS += $$PWD/TelegramServer.hpp
HEADERS += $$PWD/TelegramServerClient.hpp
HEADERS += $$PWD/TelegramServerUser.hpp
HEADERS += $$PWD/CServerTcpTransport.hpp
HEADERS += $$PWD/RemoteServerConnection.hpp
HEADERS += $$PWD/FunctionStreamOperators.hpp

include(RpcOperations/operations.pri)