#-------------------------------------------------
#
# Project created by QtCreator 2017-04-12T21:03:21
#
#-------------------------------------------------
TARGET = SSDK
TEMPLATE = lib
CONFIG += LIBS
CONFIG += c++11
CONFIG += static

QT  += gui
QT += core
QT += qml quick
QT += widgets

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    Archive/xml.cpp \
    Archive/fileinfo.cpp \
    Archive/Json/json.cpp \
    DB/sqlitedb.cpp \
    DB/blob.cpp \
    Exception/customexception.cpp \
    Exception/handlerinfo.cpp \
    stringop.cpp \
    Archive/parquet.cpp \
    Archive/protocolbuffer.cpp \
    Asio/asiocommon.cpp \
    Asio/TCP/connection.cpp \
    Asio/TCP/server.cpp \
    Asio/TCP/rwhandler.cpp \
    dataconvert.cpp \
    Asio/message.cpp \
    Asio/message.cpp

HEADERS += \
    Archive/xml.hpp \
    Archive/fileinfo.hpp \
    Archive/Json/ijsonserializable.hpp \
    Archive/Json/json.hpp \
    DB/sqlitedb.hpp \
    DB/blob.hpp \
    Exception/idisposal.hpp \
    Exception/customexception.hpp \
    Exception/handlerinfo.hpp \
    Exception/marcoexception.hpp \
    GUI/qml.hpp \
    GUI/qml.hpp \
    TypeTraits/functionaltraits.hpp \
    TypeTraits/typetraits.hpp \
    inonassignable.hpp \
    inoncopyable.hpp \
    stringop.hpp \
    Archive/parquet.hpp \
    Archive/protocolbuffer.hpp \
    Asio/asiocommon.hpp \
    Asio/TCP/connection.hpp \
    Asio/TCP/server.hpp \
    Asio/TCP/rwhandler.hpp \
    metaeeum.hpp \
    dataconvert.hpp \
    Asio/message.hpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    Doc/Json序列化和反序列化对象.md \
    Doc/Parquet,Sqlite和Json效率对比.md \
    Doc/Parquet格式说明.md \
    Doc/异常的使用说明.md \
    Doc/重新编译fPIC問題.md \
    Doc/ProtocolBuf的使用说明.md \
    Doc/TCP代码调用Demo.md \
    Doc/TCP说明.md \
    Doc/Socket的说明.md

INCLUDEPATH += $$PWD/../../include

include(SSDKDependencies.pri)
