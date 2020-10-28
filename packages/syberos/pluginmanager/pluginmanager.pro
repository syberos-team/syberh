include(../syberos.pri)

QT += core widgets

TEMPLATE = lib
DEFINES += EXTENSIONSYSTEM_LIBRARY
TARGET = pluginmanager

CONFIG += c++11


include($$PWD/src/utils/utils.pri)
include($$PWD/src/iplugin/iplugin.pri)

SOURCES += \
        $$PWD/src/pluginmanager.cpp \
        $$PWD/src/pluginspec.cpp \
        $$PWD/src/optionsparser.cpp

HEADERS += \
    $$PWD/src/extensionsystem_global.h \
    $$PWD/src/pluginmanager.h \
    $$PWD/src/pluginmanager_p.h \
    $$PWD/src/pluginspec.h \
    $$PWD/src/pluginspec_p.h \
    $$PWD/src/optionsparser.h


DESTDIR += $$clean_path($$PWD/../lib)

target.path = $$INSTALL_DIR/lib
INSTALLS += target

CONFIG(release, debug|release){
    QMAKE_POST_LINK=$(STRIP) $(DESTDIR)$(TARGET)
}