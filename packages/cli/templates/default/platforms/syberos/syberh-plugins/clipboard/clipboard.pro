#-------------------------------------------------
#
# Project created by QtCreator 2020-04-27T19:51:42
#
#-------------------------------------------------

QT       += widgets

TARGET = clipboard
TEMPLATE = lib

DEFINES += CLIPBOARD_LIBRARY

SOURCES += clipboard.cpp

HEADERS += clipboard.h\
        clipboard_global.h

CONFIG += link_pkgconfig
CONFIG += C++11
CONFIG += plugin

PKGCONFIG += syberos-qt

INCLUDEPATH += $$absolute_path("nativesdk/src", $$SYBERH_APP)
INCLUDEPATH += $$absolute_path("pluginmanager/src", $$SYBERH_APP)

LIB_OUT_DIR = $$absolute_path("lib", $$SYBERH_APP)
LIBS += -L$$LIB_OUT_DIR -lnativesdk -lpluginmanager


DESTDIR = $$absolute_path("plugins", $$SYBERH_APP)
