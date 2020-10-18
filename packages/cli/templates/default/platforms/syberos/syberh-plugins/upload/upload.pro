#-------------------------------------------------
#
# Project created by QtCreator 2020-04-23T20:36:25
#
#-------------------------------------------------

QT       += network core

TARGET = upload
TEMPLATE = lib

DEFINES += UPLOAD_LIBRARY

SOURCES += upload.cpp \
    util/uploadmanager.cpp

HEADERS += upload.h\
        upload_global.h \
    util/uploadmanager.h

CONFIG += link_pkgconfig
CONFIG += C++11
CONFIG += plugin

PKGCONFIG += syberos-qt

INCLUDEPATH += $$absolute_path("nativesdk/src", $$SYBERH_APP)
INCLUDEPATH += $$absolute_path("pluginmanager/src", $$SYBERH_APP)

LIB_OUT_DIR = $$absolute_path("lib", $$SYBERH_APP)
LIBS += -L$$LIB_OUT_DIR -lnativesdk -lpluginmanager

DESTDIR = $$absolute_path("plugins", $$SYBERH_APP)