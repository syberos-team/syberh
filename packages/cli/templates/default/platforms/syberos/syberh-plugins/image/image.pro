#-------------------------------------------------
#
# Project created by QtCreator 2020-04-21T17:14:45
#
#-------------------------------------------------

QT       += gui widgets quick qml

TARGET = image
TEMPLATE = lib

DEFINES += IMAGE_LIBRARY

SOURCES += image.cpp

HEADERS += image.h\
        image_global.h

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


RESOURCES += \
    image.qrc
