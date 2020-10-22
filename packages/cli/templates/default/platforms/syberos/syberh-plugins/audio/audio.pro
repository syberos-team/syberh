#-------------------------------------------------
#
# Project created by QtCreator 2020-04-10T20:26:31
#
#-------------------------------------------------

QT       += gui multimedia

TARGET = audio
TEMPLATE = lib

CONFIG += c++11
CONFIG += plugin

DEFINES += AUDIO_LIBRARY

SOURCES += audio.cpp

HEADERS += audio.h\
        audio_global.h

OTHER_FILES += plugin.json

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
#!isEmpty(target.path): INSTALLS += target


INCLUDEPATH += $$absolute_path("nativesdk/src", $$SYBERH_APP)
INCLUDEPATH += $$absolute_path("pluginmanager/src", $$SYBERH_APP)

LIB_OUT_DIR = $$absolute_path("lib", $$SYBERH_APP)
LIBS += -L$$LIB_OUT_DIR -lnativesdk -lpluginmanager

DESTDIR = $$absolute_path("plugins", $$SYBERH_APP)
