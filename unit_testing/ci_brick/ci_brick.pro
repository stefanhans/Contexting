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
DEFINES += SRCDIR=\\\"$$PWD/\\\"


unix:!macx: LIBS += -L$$PWD/../../build-contexting_core-Desktop_Qt_5_5_1_GCC_64bit-Release/ -lcontexting_core

INCLUDEPATH += $$PWD/../../contexting_core
DEPENDPATH += $$PWD/../../contexting_core
