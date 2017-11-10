TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    dataGeneration.c \
    imageCompression.c

DISTFILES += \
    README.md

HEADERS += \
    imagecompression.h \
    datageneration.h
