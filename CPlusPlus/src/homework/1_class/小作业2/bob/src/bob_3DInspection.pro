TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
QT += core
QT += sql
QT += xml

SOURCES += \
    sdk/customexception.cpp \
    app/appsetting.cpp \
    app/capturesetting.cpp \
    job/measuredobj.cpp \
    job/measuredobjlist.cpp \
    job/board.cpp \
    job/inspectiondata.cpp \
    main.cpp \
    sdk/DB/blob.cpp \
    sdk/DB/sqlitedb.cpp \
    app/mainwindow.cpp \
    app/config.cpp \
    sdk/numrandom.cpp \
    job/ImageSlot.cpp \
    sdk/formatconvertor.cpp \
    app/datagenerator.cpp \
    sdk/Circle.cpp \
    job/FiducialMark.cpp \
    sdk/Shape.cpp \
    sdk/Point.cpp \
    sdk/Rectangle.cpp \
    job/Pad.cpp

HEADERS += \
    sdk/customexception.hpp \
    app/appsetting.hpp \
    app/capturesetting.hpp \
    job/measuredobj.hpp \
    job/measuredobjlist.hpp \
    job/board.hpp \
    job/inspectiondata.hpp \
    sdk/DB/blob.hpp \
    sdk/DB/sqlitedb.hpp \
    app/mainwindow.hpp \
    app/config.hpp \
    sdk/numrandom.hpp \
    job/ImageSlot.hpp \
    sdk/formatconvertor.hpp \
    app/datagenerator.hpp \
    sdk/Circle.hpp \
    job/FiducialMark.hpp \
    sdk/Shape.hpp \
    sdk/Point.hpp \
    sdk/Rectangle.hpp \
    job/Pad.hpp

INCLUDEPATH += $$PWD/../include/sqlits
INCLUDEPATH += $$PWD/../include

unix::LIBS += -L$$PWD/../lib/ -lsqlite3

unix:LIBS += -L/usr/lib/x86_64-linux-gnu\
-ldl
