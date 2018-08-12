#-------------------------------------------------
#
# Project created by QtCreator 2017-02-20T19:57:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CustomWidgetTest
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    form.cpp

HEADERS  += widget.h \
    form.h

FORMS    += widget.ui \
    form.ui

CONFIG += release
MOC_DIR = temp/moc
RCC_DIR = temp/rcc
UI_DIR = temp/ui
OBJECTS_DIR = temp/obj
DESTDIR = bin

include(CustomWidget.pri)
LIBS += $$PWD/include/customwidgetlistplugin.lib
