TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

QT += core
QT += sql
QT += xml

HEADERS += \
    SDK/customexception.hpp\
    SDK/rectangle.hpp \
    SDK/formatconversion.hpp \
    SDK/randomdigit.hpp \
    Job/board.hpp \
    Job/inspectiondata.hpp \
    Job/measuredlist.hpp \
    Job/measuredobj.hpp \
    App/appsetting.hpp \
    App/capturesetting.hpp \
    App/mainWindow.hpp \
    DB/sqlitedb.hpp \
    DB/sqlitedbtest.hpp \
    DB/blob.hpp

SOURCES += main.cpp \
    SDK/customexception.cpp\
    SDK/rectangle.cpp\
    Job/board.cpp \
    Job/inspectiondata.cpp \
    Job/measuredlist.cpp \
    Job/measuredobj.cpp \
    App/appsetting.cpp \
    App/capturesetting.cpp \
    App/mainWindow.cpp \
    DB/sqlitedb.cpp \
    DB/sqlitedbtest.cpp \
    DB/blob.cpp


INCLUDEPATH += $$PWD/../include/sqlite
INCLUDEPATH += $$PWD/../include

unix: : LIBS += -L$$PWD/../lib/ -lsqlite3

unix:LIBS +=  -L/usr/lib/x86_64-linux-gnu\
-ldl
