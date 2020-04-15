include(../syberos.pri)

QT += core network

TEMPLATE = lib
DEFINES += NATIVESDK_LIBRARY
TARGET = nativesdk

CONFIG += link_pkgconfig
CONFIG += c++11

PKGCONFIG += syberos-qt


HEADERS += \
    $$PWD/src/framework/nativesdkmanager.h \
    $$PWD/src/framework/nativesdkmanager_p.h \
    $$PWD/src/framework/nativesdkhandlerbase.h \
    $$PWD/src/framework/nativesdkfactory.h \
    $$PWD/src/framework/pluginadapter.h \
    $$PWD/src/framework/common/networkstatus.h \
    $$PWD/src/framework/common/errorinfo.h \
    $$PWD/src/framework/common/extendedconfig.h \
    $$PWD/src/framework/devtools/devtools.h \
    $$PWD/src/framework/devtools/socketclient.h \
    $$PWD/src/framework/devtools/devdownload.h \
    $$PWD/src/util/fileutil.h \
    $$PWD/src/util/log.h \
    $$PWD/src/util/validator.h \
    $$PWD/src/nativesdk_global.h \
    $$PWD/src/helper.h \
    $$PWD/src/senvironment.h 

SOURCES += \
    $$PWD/src/framework/nativesdkmanager.cpp \
    $$PWD/src/framework/nativesdkfactory.cpp \
    $$PWD/src/framework/nativesdkhandlerbase.cpp \
    $$PWD/src/framework/pluginadapter.cpp \
    $$PWD/src/framework/common/networkstatus.cpp \
    $$PWD/src/framework/common/errorinfo.cpp \
    $$PWD/src/framework/common/extendedconfig.cpp \
    $$PWD/src/framework/devtools/devtools.cpp \
    $$PWD/src/framework/devtools/socketclient.cpp \
    $$PWD/src/framework/devtools/devdownload.cpp \
    $$PWD/src/util/fileutil.cpp \
    $$PWD/src/util/log.cpp \
    $$PWD/src/util/validator.cpp \
    $$PWD/src/helper.cpp \
    $$PWD/src/senvironment.cpp 


DESTDIR += $$clean_path($$OUT_PWD/../lib)

target.path = $$INSTALL_DIR/lib
INSTALLS += target

#TARGET_LIB_DIR = $$clean_path($$[QT_INSTALL_HEADERS]/../../lib)
#LIBS += -L$$TARGET_LIB_DIR -lsyberos-qt

PLUGINMANAGER_OUT_DIR = $$clean_path($$OUT_PWD/../lib)
LIBS += -L$$PLUGINMANAGER_OUT_DIR -lpluginmanager

