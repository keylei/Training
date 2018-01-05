TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
QT += core
QT += sql
QT += xml

SOURCES += \
    main.cpp \
    sdk/DB/blob.cpp \
    sdk/DB/sqlitedb.cpp \
    job/ImageSlot.cpp \
    job/Image.cpp \
    job/Pad.cpp \
    sdk/Circle.cpp \
    sdk/Point.cpp \
    sdk/Shape.cpp \
    job/FiducialMark.cpp \
    job/MeasuredObject.cpp \
    job/Board.cpp \
    job/InspectionData.cpp \
    app/DataGenerator.cpp \
    app/Config.cpp \
    app/CaptureSetting.cpp \
    app/AppSetting.cpp \
    sdk/CustomException.cpp \
    sdk/Rectangle.cpp \
    sdk/NumRandom.cpp \
    sdk/FormatConvertion.cpp \
    sdk/IAreaCalculatable.cpp

HEADERS += \
    sdk/DB/blob.hpp \
    sdk/DB/sqlitedb.hpp \
    job/ImageSlot.hpp \
    job/Image.hpp \
    job/Pad.hpp \
    sdk/Circle.hpp \
    sdk/Point.hpp \
    sdk/Shape.hpp \
    job/FiducialMark.hpp \
    job/MeasuredObject.hpp \
    job/Board.hpp \
    job/InspectionData.hpp \
    app/DataGenerator.hpp \
    app/Config.hpp \
    app/CaptureSetting.hpp \
    app/AppSetting.hpp \
    sdk/CustomException.hpp \
    sdk/Rectangle.hpp \
    sdk/NumRandom.hpp \
    sdk/FormatConvertion.hpp \
    sdk/IAreaCalculatable.hpp

INCLUDEPATH += $$PWD/../include/sqlits
INCLUDEPATH += $$PWD/../include

unix::LIBS += -L$$PWD/../lib/ -lsqlite3

unix:LIBS += -L/usr/lib/x86_64-linux-gnu\
-ldl
