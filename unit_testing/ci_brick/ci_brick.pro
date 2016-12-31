#-------------------------------------------------
#
# Project created by QtCreator 2016-05-28T18:47:44
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_ci_bricktest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_ci_bricktest.cpp


unix:!macx: LIBS += -L../../build-contexting_core-Desktop_Qt_5_7_1_GCC_64bit-Release/ -lcontexting_core

INCLUDEPATH += ../../contexting_core
DEPENDPATH += ../../contexting_core

#DESTDIR = ./

