#-------------------------------------------------
#
# Project created by QtCreator 2017-02-20T21:59:47
#
#-------------------------------------------------

QT       += core network gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = base
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    base.cpp \
    httpdownload.cpp \
    log.cpp \
    base64.cpp \
    md5.c

HEADERS += \
    base.h \
    httpdownload.h \
    log.h \
    base64.h \
    md5.h

DISTFILES += \
    README.md
