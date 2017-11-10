TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    datageneration.c \
    datahelper.c \
    datacompression.c

HEADERS += \
    datageneration.h \
    datacompression.h \
    datahelper.h

DISTFILES += \
    config
