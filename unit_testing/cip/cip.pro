#-------------------------------------------------
#
# Project created by QtCreator 2016-07-11T17:52:57
#
#-------------------------------------------------

QT       += testlib
QT       += network

QT       -= gui

TARGET = tst_ciptest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_ciptest.cpp

unix:!macx: LIBS += -L../../build-contexting_core-Desktop_Qt_5_7_1_GCC_64bit-Release/ -lcontexting_core

INCLUDEPATH += ../../contexting_core
DEPENDPATH += ../../contexting_core
