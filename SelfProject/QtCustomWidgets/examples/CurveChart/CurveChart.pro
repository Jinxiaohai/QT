#-------------------------------------------------
#
# Project created by QtCreator 2017-02-24T23:14:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CurveChart
TEMPLATE = app


SOURCES += main.cpp\
    curvecharttest.cpp

HEADERS  += curvecharttest.h

FORMS += \
    curvecharttest.ui

CONFIG += release
MOC_DIR = temp/moc
RCC_DIR = temp/rcc
UI_DIR = temp/ui
OBJECTS_DIR = temp/obj
DESTDIR = bin

include(../../CurveChart/CurveChart.pri)
