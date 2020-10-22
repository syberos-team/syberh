#-------------------------------------------------
#
# Project created by QtCreator 2020-04-14T21:00:42
#
#-------------------------------------------------

QT       += widgets

TARGET = filemanager
TEMPLATE = lib

CONFIG += plugin
CONFIG += c++11

DEFINES += FILEMANAGER_LIBRARY

SOURCES += filemanager.cpp 

HEADERS += filemanager.h\
        filemanager_global.h


INCLUDEPATH += $$absolute_path("nativesdk/src", $$SYBERH_APP)
INCLUDEPATH += $$absolute_path("pluginmanager/src", $$SYBERH_APP)

LIB_OUT_DIR = $$absolute_path("lib", $$SYBERH_APP)
LIBS += -L$$LIB_OUT_DIR -lnativesdk -lpluginmanager

DESTDIR = $$absolute_path("plugins", $$SYBERH_APP)
