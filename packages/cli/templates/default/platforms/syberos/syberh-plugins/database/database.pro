#-------------------------------------------------
#
# Project created by QtCreator 2020-04-14T19:09:54
#
#-------------------------------------------------

QT -= gui
QT += sql

TARGET = database
TEMPLATE = lib

DEFINES += DATABASE_LIBRARY

SOURCES += database.cpp

HEADERS += database.h\
        database_global.h

CONFIG += link_pkgconfig
CONFIG += C++11
CONFIG += plugin

PKGCONFIG += syberos-qt

INCLUDEPATH += $$absolute_path("nativesdk/src", $$SYBERH_APP)
INCLUDEPATH += $$absolute_path("pluginmanager/src", $$SYBERH_APP)

LIB_OUT_DIR = $$absolute_path("lib", $$SYBERH_APP)
LIBS += -L$$LIB_OUT_DIR -lnativesdk -lpluginmanager

DESTDIR = $$absolute_path("plugins", $$SYBERH_APP)
