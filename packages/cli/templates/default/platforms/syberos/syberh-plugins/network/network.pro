#-------------------------------------------------
#
# Project created by QtCreator 2020-04-15T00:18:54
#
#-------------------------------------------------

QT       += network core

TARGET = network
TEMPLATE = lib

DEFINES += NETWORK_LIBRARY

SOURCES += network.cpp 

HEADERS += network.h\
        network_global.h

CONFIG += link_pkgconfig
CONFIG += C++11
CONFIG += plugin

PKGCONFIG += syberos-qt


INCLUDEPATH += $$absolute_path("nativesdk/src", $$SYBERH_APP)
INCLUDEPATH += $$absolute_path("pluginmanager/src", $$SYBERH_APP)

LIB_OUT_DIR = $$absolute_path("lib", $$SYBERH_APP)
LIBS += -L$$LIB_OUT_DIR -lnativesdk -lpluginmanager

DESTDIR = $$absolute_path("plugins", $$SYBERH_APP)
