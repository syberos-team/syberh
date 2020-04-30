#-------------------------------------------------
#
# Project created by QtCreator 2020-04-20T19:41:36
#
#-------------------------------------------------

QT       += gui widgets quick qml

TARGET = app
TEMPLATE = lib

DEFINES += APP_LIBRARY

SOURCES += app.cpp

HEADERS += app.h\
        app_global.h


CONFIG += link_pkgconfig
CONFIG += C++11
CONFIG += plugin

PKGCONFIG += syberos-qt

INCLUDEPATH += $$[QT_INSTALL_HEADERS]/../syberos_application
LIBS += -L/usr/lib -lsyberos-application

INCLUDEPATH += $$absolute_path("nativesdk/src", $$SYBERH_APP)
INCLUDEPATH += $$absolute_path("pluginmanager/src", $$SYBERH_APP)

LIB_OUT_DIR = $$absolute_path("lib", $$SYBERH_APP)
LIBS += -L$$LIB_OUT_DIR -lnativesdk -lpluginmanager


DESTDIR = $$absolute_path("plugins", $$SYBERH_APP)


INCLUDEPATH += /home/xuejun/syberh-v2.0/syberh/packages/syberos/nativesdk/src
INCLUDEPATH += /home/xuejun/syberh-v2.0/syberh/packages/syberos/pluginmanager/src
