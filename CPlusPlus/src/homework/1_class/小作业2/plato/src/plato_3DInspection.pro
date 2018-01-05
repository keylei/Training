TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
#QT += core
#QT += sql
#QT += xml

SOURCES += \
#    app/appsetting.cpp \
#    app/capturesetting.cpp \
#    job/measuredobjlist.cpp \
#    job/inspectiondata.cpp \
    main.cpp \
#    sdk/DB/blob.cpp \
#    sdk/DB/sqlitedb.cpp \
#    app/mainwindow.cpp \
#    app/config.cpp \
#    job/ImageSlot.cpp \
    app/Datagenerator.cpp \
    sdk/Rectangle.cpp \
    sdk/Circle.cpp \
    sdk/Shape.cpp \
    job/FiducialMark.cpp \
    job/Pad.cpp \
    job/MeasuredObj.cpp \
    job/Board.cpp \
#    sdk/FormatConvertion.cpp \
    sdk/CustomException.cpp \
    sdk/NumRandom.cpp

HEADERS += \
    sdk/customexception.hpp \
#    app/appsetting.hpp \
#    app/capturesetting.hpp \
#    job/measuredobjlist.hpp \
#    job/inspectiondata.hpp \
#    sdk/DB/blob.hpp \
#    sdk/DB/sqlitedb.hpp \
#    app/mainwindow.hpp \
#    app/config.hpp \
#    job/ImageSlot.hpp \
    app/Datagenerator.hpp \
    sdk/Rectangle.hpp \
    sdk/Circle.hpp \
    sdk/Shape.hpp \
    job/FiducialMark.hpp \
    job/Pad.hpp \
    job/MeasuredObj.hpp \
    job/Board.hpp \
    sdk/NumRandom.hpp \
#    sdk/FormatConvertion.hpp

#INCLUDEPATH += $$PWD/../include/sqlits
#INCLUDEPATH += $$PWD/../include

#unix::LIBS += -L$$PWD/../lib/ -lsqlite3

#unix:LIBS += -L/usr/lib/x86_64-linux-gnu\
#-ldl
