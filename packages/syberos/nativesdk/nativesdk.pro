include(../syberos.pri)

QT += core network quick

TEMPLATE = lib
DEFINES += NATIVESDK_LIBRARY
TARGET = nativesdk

CONFIG += link_pkgconfig
CONFIG += c++11
CONFIG += plugin

PKGCONFIG += syberos-qt

DEFINES += EX_CONFIG=\\\"$$EX_CONFIG\\\"

HEADERS += \
    $$PWD/src/framework/nativesdkmanager.h \
    $$PWD/src/framework/nativesdkmanager_p.h \
    $$PWD/src/framework/nativesdkhandlerbase.h \
    $$PWD/src/framework/nativesdkfactory.h \
    $$PWD/src/framework/pluginadapter.h \
    $$PWD/src/framework/common/networkstatus.h \
    $$PWD/src/framework/common/errorinfo.h \
    $$PWD/src/framework/common/extendedconfig.h \
    $$PWD/src/framework/common/projectconfig.h \
    $$PWD/src/framework/devtools/devtools.h \
    $$PWD/src/framework/devtools/socketclient.h \
    $$PWD/src/framework/devtools/devdownload.h \
    $$PWD/src/util/fileutil.h \
    $$PWD/src/util/log.h \
    $$PWD/src/util/validator.h \
    $$PWD/src/nativesdk_global.h \
    $$PWD/src/helper.h \
    $$PWD/src/helper_p.h \
    $$PWD/src/senvironment.h \ 
    $$PWD/src/qmlobject.h \
    $$PWD/src/qmlobject_p.h \
    $$PWD/src/qmlmanager.h


SOURCES += \
    $$PWD/src/framework/nativesdkmanager.cpp \
    $$PWD/src/framework/nativesdkfactory.cpp \
    $$PWD/src/framework/nativesdkhandlerbase.cpp \
    $$PWD/src/framework/pluginadapter.cpp \
    $$PWD/src/framework/common/networkstatus.cpp \
    $$PWD/src/framework/common/errorinfo.cpp \
    $$PWD/src/framework/common/extendedconfig.cpp \
    $$PWD/src/framework/common/projectconfig.cpp \
    $$PWD/src/framework/devtools/socketclient.cpp \
    $$PWD/src/framework/devtools/devdownload.cpp \
    $$PWD/src/util/fileutil.cpp \
    $$PWD/src/util/log.cpp \
    $$PWD/src/util/validator.cpp \
    $$PWD/src/helper.cpp \
    $$PWD/src/senvironment.cpp \ 
    $$PWD/src/qmlobject.cpp \
    $$PWD/src/qmlmanager.cpp


SYBERH_QT_VERSION = $$[QT_VERSION]
SYBERH_QT_VERSION = $$split(SYBERH_QT_VERSION, ".")
QT_VER_MIN = $$member(SYBERH_QT_VERSION, 1)

# //TODO 5.0暂时不适用热更新
lessThan(QT_VER_MIN, 12) {
    SOURCES += $$PWD/src/framework/devtools/devtools.cpp
} else {
    SOURCES += $$PWD/src/framework/devtools/devtools_os5.cpp
}


DESTDIR += $$clean_path($$PWD/../lib)

target.path = $$INSTALL_DIR/lib
INSTALLS += target

#TARGET_LIB_DIR = $$clean_path($$[QT_INSTALL_HEADERS]/../../lib)
#LIBS += -L$$TARGET_LIB_DIR -lsyberos-qt

LIB_OUT_DIR = $$clean_path($$PWD/../lib)
LIBS += -L$$LIB_OUT_DIR -lpluginmanager

CONFIG(release, debug|release){
    QMAKE_POST_LINK=$(STRIP) $(DESTDIR)$(TARGET)
}