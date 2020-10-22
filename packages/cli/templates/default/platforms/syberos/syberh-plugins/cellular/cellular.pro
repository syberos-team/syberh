#-------------------------------------------------
#
# Project created by QtCreator 2020-04-14T20:55:59
#
#-------------------------------------------------

QT       -= gui

TARGET = cellular
TEMPLATE = lib

DEFINES += CELLULAR_LIBRARY

SOURCES += cellular.cpp

HEADERS += cellular.h\
        cellular_global.h

CONFIG += link_pkgconfig
CONFIG += C++11
CONFIG += plugin

PKGCONFIG += syberos-qt

INCLUDEPATH += $$absolute_path("nativesdk/src", $$SYBERH_APP)
INCLUDEPATH += $$absolute_path("pluginmanager/src", $$SYBERH_APP)

LIB_OUT_DIR = $$absolute_path("lib", $$SYBERH_APP)
LIBS += -L$$LIB_OUT_DIR -lnativesdk -lpluginmanager

DESTDIR = $$absolute_path("plugins", $$SYBERH_APP)
