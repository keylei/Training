TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    fov.cpp\
    datahelper.cpp \
    lightcheck.cpp \
    image.cpp

HEADERS += \
    fov.hpp \
    datahelper.hpp \
    lightcheck.hpp \
    image.hpp
