#-------------------------------------------------
#
# Project created by QtCreator 2015-01-06T14:27:43
#
#-------------------------------------------------

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = openvas_gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    instance.cpp \
    genxml.cpp \
    omp.cpp

HEADERS  += mainwindow.h \
    instance.h \
    genxml.h \
    params.h \
    omp.h

FORMS    += mainwindow.ui \
    instance.ui

UI_DIR = ./UI

RESOURCES +=
