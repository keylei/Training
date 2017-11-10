TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    dataGeneration.c \
    imageCompression.c \
    ioHelper.c

DISTFILES += \
    README.md

HEADERS += \
    imagecompression.h \
    iohelper.h \
    datageneration.h
