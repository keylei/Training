TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    job/FiducialMark.cpp \
    job/Pad.cpp \
    sdk/Circle.cpp \
    sdk/Point.cpp \
    sdk/Shape.cpp \
    app/DataGenerator.cpp \
    job/Board.cpp \
    job/MeasuredObj.cpp \
    sdk/CustomException.cpp \
    sdk/FormatConvertor.cpp \
    sdk/NumRandom.cpp \
    sdk/Rectangle.cpp

HEADERS += \
    job/FiducialMark.hpp \
    job/Pad.hpp \
    sdk/Circle.hpp \
    sdk/Point.hpp \
    sdk/Shape.hpp \
    app/DataGenerator.hpp \
    job/Board.hpp \
    job/MeasuredObj.hpp \
    sdk/CustomException.hpp \
    sdk/FormatConvertor.hpp \
    sdk/NumRandom.hpp \
    sdk/Rectangle.hpp
