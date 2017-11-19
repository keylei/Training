TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
QT += core
QT += sql

SOURCES += \
    sdk.cpp \
    0.basicUsage.cpp \
    1.performance.cpp \
    job.cpp \
    2.app.cpp \
    3.stlExClass.cpp \
    customexception.cpp \
    4.customEx.cpp \
    5.settingEx.cpp \
    6.loadJob.cpp \
    DB/blob.cpp \
    DB/sqlitedb.cpp \
    DB/sqlitedbtest.cpp

HEADERS += \
    job.hpp \
    sdk.hpp \
    customexception.hpp \
    DB/blob.hpp \
    DB/sqlitedb.hpp \
    DB/sqlitedbtest.hpp

DISTFILES +=

INCLUDEPATH += $$PWD/../../../include/sqlite
INCLUDEPATH += $$PWD/../../../include

unix: : LIBS += -L$$PWD/../../../lib/ -lsqlite3

unix:LIBS +=  -L/usr/lib/x86_64-linux-gnu\
-ldl

