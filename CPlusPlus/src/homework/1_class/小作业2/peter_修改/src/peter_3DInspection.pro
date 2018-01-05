TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
QT += core
QT += sql
QT += xml

SOURCES += \
    main.cpp \
    job/ImageSlot.cpp \
    app/AppSetting.cpp \
    app/CaptureSetting.cpp \
    app/Config.cpp \
    app/DataGenerator.cpp \
    app/MainWindow.cpp \
    job/Board.cpp \
    job/InspectionData.cpp \
    job/MeasuredObj.cpp \
    job/MeasuredObjList.cpp \
    sdk/DB/Blob.cpp \
    sdk/DB/SqlitedDb.cpp \
    sdk/CustomException.cpp \
    sdk/FormatConvertor.cpp \
    sdk/NumRandom.cpp \
    sdk/Rectangle.cpp \
    sdk/Circle.cpp \
    sdk/Shape.cpp \
    job/Pad.cpp \
    job/FiducialMark.cpp

HEADERS += \
    job/ImageSlot.hpp \
    app/AppSetting.hpp \
    app/CaptureSetting.hpp \
    app/Config.hpp \
    app/DataGenerator.hpp \
    app/MainWindow.hpp \
    job/Board.hpp \
    job/InspectionData.hpp \
    job/MeasuredObj.hpp \
    sdk/DB/Blob.hpp \
    sdk/DB/SqliteDb.hpp \
    sdk/CustomException.hpp \
    sdk/FormatConvertor.hpp \
    sdk/NumRandom.hpp \
    sdk/Rectangle.hpp \
    job/MeasuredObjList.hpp \
    sdk/Circle.hpp \
    sdk/Shape.hpp \
    job/Pad.hpp \
    job/FiducialMark.hpp

INCLUDEPATH += $$PWD/../include/sqlits
INCLUDEPATH += $$PWD/../include

unix::LIBS += -L$$PWD/../lib/ -lsqlite3

unix:LIBS += -L/usr/lib/x86_64-linux-gnu\
-ldl
