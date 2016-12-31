#-------------------------------------------------
#
# Project created by QtCreator 2016-07-11T08:17:17
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_ci_datatest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_ci_datatest.cpp

unix:!macx: LIBS += -L../../build-contexting_core-Desktop_Qt_5_7_1_GCC_64bit-Release/ -lcontexting_core

INCLUDEPATH += ../../contexting_core
DEPENDPATH += ../../contexting_core
