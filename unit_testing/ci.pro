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
DEFINES += SRCDIR=\\\"$$PWD/\\\"

unix:!macx: LIBS += -L$$PWD/../../build-contexting_core-Desktop_Qt_5_5_1_GCC_64bit-Release/ -lcontexting_core

INCLUDEPATH += $$PWD/../../contexting_core
DEPENDPATH += $$PWD/../../contexting_core

