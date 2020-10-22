#-------------------------------------------------
#
# Project created by QtCreator 2020-04-15T19:11:15
#
#-------------------------------------------------

QT -= gui
QT += core

TARGET = storage
TEMPLATE = lib

DEFINES += STORAGE_LIBRARY

CONFIG += plugin
CONFIG += c++11
CONFIG += link_pkgconfig

PKGCONFIG += syberos-qt


SYBERH_QT_VERSION = $$[QT_VERSION]
SYBERH_QT_VERSION = $$split(SYBERH_QT_VERSION, ".")
QT_VER_MIN = $$member(SYBERH_QT_VERSION, 1)


HEADERS += storage.h\
        storage_global.h

lessThan(QT_VER_MIN, 12) {
    SOURCES += storage.cpp
} else {
    SOURCES += storage_os5.cpp
}

OTHER_FILES += plugin.json


INCLUDEPATH += $$absolute_path("nativesdk/src", $$SYBERH_APP)
INCLUDEPATH += $$absolute_path("pluginmanager/src", $$SYBERH_APP)

DESTDIR = $$absolute_path("plugins", $$SYBERH_APP)

LIB_OUT_DIR = $$absolute_path("lib", $$SYBERH_APP)
LIBS += -L$$LIB_OUT_DIR -lnativesdk
