#-------------------------------------------------
#
# Project created by QtCreator 2020-04-14T10:25:58
#
#-------------------------------------------------

QT       += gui

TARGET = battery
TEMPLATE = lib

CONFIG += link_pkgconfig
CONFIG += C++11
CONFIG += plugin

DEFINES += BATTERY_LIBRARY

SOURCES += battery.cpp

HEADERS += battery.h\
        battery_global.h

PKGCONFIG += syberos-qt

INCLUDEPATH += $$absolute_path("nativesdk/src", $$SYBERH_APP)
INCLUDEPATH += $$absolute_path("pluginmanager/src", $$SYBERH_APP)

LIB_OUT_DIR = $$absolute_path("lib", $$SYBERH_APP)
LIBS += -L$$LIB_OUT_DIR -lnativesdk -lpluginmanager

DESTDIR = $$absolute_path("plugins", $$SYBERH_APP)
