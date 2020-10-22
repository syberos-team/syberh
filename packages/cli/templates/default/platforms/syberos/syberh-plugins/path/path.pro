#-------------------------------------------------
#
# Project created by QtCreator 2020-04-15T04:02:51
#
#-------------------------------------------------

QT       -= gui

TARGET = path
TEMPLATE = lib

DEFINES += PATH_LIBRARY

SOURCES += path.cpp

HEADERS += path.h\
        path_global.h 

CONFIG += C++11
CONFIG += plugin


INCLUDEPATH += $$absolute_path("nativesdk/src", $$SYBERH_APP)
INCLUDEPATH += $$absolute_path("pluginmanager/src", $$SYBERH_APP)

LIB_OUT_DIR = $$absolute_path("lib", $$SYBERH_APP)
LIBS += -L$$LIB_OUT_DIR -lnativesdk -lpluginmanager

DESTDIR = $$absolute_path("plugins", $$SYBERH_APP)
