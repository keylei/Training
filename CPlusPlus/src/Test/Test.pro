TEMPLATE = app

QT += widgets testlib
QT += qml quick
QT += quick quickcontrols2
QT += widgets
QT       += core
QT       += gui

CONFIG += c++11

#QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    SSDK/Exception/exceptionDemoDlg.cpp \
    SSDK/Exception/icanshowexmsgdlg.cpp \
    SSDK/Exception/qcustomexception.cpp \
    commontool.cpp \
    SSDK/Protoc/protocolBuffer.typeCollection.pb.cc

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include(TestDependencies.pri)

HEADERS += \
    unittester.hpp \
    SSDK/testjson.hpp \
    SSDK/testsqlite.hpp \
    SSDK/testexception.hpp \
    SSDK/Exception/exceptionDemoDlg.hpp \
    SSDK/Exception/icanshowexmsgdlg.hpp \
    SSDK/Exception/qcustomexception.hpp \
    SSDK/testfileinfo.hpp \
    SSDK/testparquet.hpp \
    commontool.hpp \
    SSDK/testprotocolbuffer.hpp \
    SSDK/Protoc/protocolBuffer.typeCollection.pb.h \
    SSDK/testtcp.hpp

DISTFILES += \
    data/Json/glossary.json \
    data/Json/menu.json \
    data/Json/widget.json \
    data/Json/items.json \
    data/Json/mixed.json \
    data/Json/person.json \
    data/Json/student.json \
    data/Json/teacher.json \
    data/ProtoBuf/protocolBuffer.typeCollection.proto \
    data/ProtoBuf/unittest.proto
