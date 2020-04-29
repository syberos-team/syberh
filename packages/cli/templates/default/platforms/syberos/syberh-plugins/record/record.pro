#-------------------------------------------------
#
# Project created by QtCreator 2020-04-15T18:34:46
#
#-------------------------------------------------

QT       += gui multimedia sql

TARGET = record
TEMPLATE = lib

DEFINES += RECORD_LIBRARY

CONFIG += link_pkgconfig
CONFIG += C++11
CONFIG += plugin

PKGCONFIG += syberos-qt

SOURCES += record.cpp \
           historydata.cpp

HEADERS += record.h\
        record_global.h \
        historydata.h


INCLUDEPATH += $$absolute_path("nativesdk/src", $$SYBERH_APP)
INCLUDEPATH += $$absolute_path("pluginmanager/src", $$SYBERH_APP)

LIB_OUT_DIR = $$absolute_path("lib", $$SYBERH_APP)
LIBS += -L$$LIB_OUT_DIR -lnativesdk -lpluginmanager

DESTDIR = $$absolute_path("plugins", $$SYBERH_APP)

