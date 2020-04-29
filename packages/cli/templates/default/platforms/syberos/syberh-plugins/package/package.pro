#-------------------------------------------------
#
# Project created by QtCreator 2020-04-15T03:41:28
#
#-------------------------------------------------

QT       += widgets

TARGET = package
TEMPLATE = lib

DEFINES += PACKAGE_LIBRARY

SOURCES += package.cpp

HEADERS += package.h\
        package_global.h

CONFIG += link_pkgconfig
CONFIG += C++11
CONFIG += plugin

PKGCONFIG += syberos-qt

INCLUDEPATH += /usr/include/syberos_application

LIBS += -L/usr/lib -lsyberos-application


INCLUDEPATH += $$absolute_path("nativesdk/src", $$SYBERH_APP)
INCLUDEPATH += $$absolute_path("pluginmanager/src", $$SYBERH_APP)

LIB_OUT_DIR = $$absolute_path("lib", $$SYBERH_APP)
LIBS += -L$$LIB_OUT_DIR -lnativesdk -lpluginmanager

DESTDIR = $$absolute_path("plugins", $$SYBERH_APP)
