#-------------------------------------------------
#
# Project created by QtCreator 2020-04-21T14:57:44
#
#-------------------------------------------------

QT       += gui widgets quick qml core

TARGET = camera
TEMPLATE = lib

DEFINES += CAMERA_LIBRARY

SOURCES += camera.cpp

HEADERS += camera.h\
        camera_global.h


CONFIG += link_pkgconfig
CONFIG += C++11
CONFIG += plugin

PKGCONFIG += syberos-qt

INCLUDEPATH += $$[QT_INSTALL_HEADERS]/../syberos_application
INCLUDEPATH += $$absolute_path("nativesdk/src", $$SYBERH_APP)
INCLUDEPATH += $$absolute_path("pluginmanager/src", $$SYBERH_APP)

LIB_OUT_DIR = $$absolute_path("lib", $$SYBERH_APP)
LIBS += -L$$LIB_OUT_DIR -lnativesdk -lpluginmanager
LIBS += -L/usr/lib -lsyberos-application

DESTDIR = $$absolute_path("plugins", $$SYBERH_APP)

RESOURCES += \
    camera.qrc

INCLUDEPATH += /home/xuejun/syberh-v2.0/syberh/packages/syberos/nativesdk/src
INCLUDEPATH += /home/xuejun/syberh-v2.0/syberh/packages/syberos/pluginmanager/src
