#-------------------------------------------------
#
# Project created by QtCreator 2020-04-20T11:30:47
#
#-------------------------------------------------

QT       += gui widgets quick qml

TARGET = modal
TEMPLATE = lib

DEFINES += MODAL_LIBRARY

SOURCES += modal.cpp

HEADERS += modal.h\
        modal_global.h


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
    modal.qrc
