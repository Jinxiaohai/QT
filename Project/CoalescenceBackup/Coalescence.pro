QT += core gui widgets

INCLUDEPATH += ./include
INCLUDEPATH += /opt/root/install/include
LIBS += $$system(root-config --libs)
LIBS += $$system(root-config --glibs)


SOURCES += \
    src/mainwindow.cpp \
    src/main.cpp \
    src/AMPT.cpp \
    src/track.cpp


HEADERS += \
    include/mainwindow.h \
    include/AMPT.h \
    include/track.h



RESOURCES += \
    resource/resources.qrc

FORMS += \
    resource/mainwindow.ui
