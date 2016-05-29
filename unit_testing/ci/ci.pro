#-------------------------------------------------
#
# Project created by QtCreator 2016-05-29T10:15:52
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_citest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_citest.cpp

unix:!macx: LIBS += -L../../build-contexting_core-Desktop_Qt_5_5_1_GCC_64bit-Release/ -lcontexting_core

INCLUDEPATH += ../../contexting_core
DEPENDPATH += ../../contexting_core

