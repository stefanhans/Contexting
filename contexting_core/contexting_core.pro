#-------------------------------------------------
#
# Project created by QtCreator 2016-05-28T15:15:23
#
#-------------------------------------------------

QT       -= gui
QT       += core network

TARGET = contexting_core
TEMPLATE = lib

DEFINES += CONTEXTING_CORE_LIBRARY

SOURCES += \
    ci_brick.cpp \
    ci.cpp \
    cip.cpp \
    gateway.cpp \
    packaging.cpp \
    storage.cpp

HEADERS += contexting_core.h\
        contexting_core_global.h \
    ci_brick.h \
    ci.h \
    packaging.h \
    storage.h \
    gateway.h \
    cip.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
