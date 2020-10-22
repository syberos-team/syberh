#-------------------------------------------------
#
# Project created by QtCreator 2020-04-14T20:42:07
#
#-------------------------------------------------

QT       += core gui quick multimedia qml widgets

TARGET = qrcode
TEMPLATE = lib

DEFINES += QRCODE_LIBRARY

CONFIG += plugin
CONFIG += C++11
CONFIG += link_pkgconfig

contains(DEFINES, S1) {
    message('>> build with S1')
    PKGCONFIG += gstreamer-egl-0.10 android-headers
    HEADERS += $$PWD/src/qrcode/gralloc_priv.h
}else{
    message('>> build without S1')
}

RESOURCES += \
    $$PWD/qrcode.qrc


HEADERS += \
    $$PWD/src/qrcode/cqrcoder.h \
    $$PWD/src/qrcode/decodethread.h \
    $$PWD/src/qrcode/decodeworkspace.h \
    $$PWD/src/qrcode/multimediautils.h \
    $$PWD/src/qrcode/qandroidmultimediautils.h \
    $$PWD/src/qrcode/qtcamera.h \
    $$PWD/src/qrcode/zxing.h \
    $$PWD/src/qrcoderegister.h \
    $$PWD/src/qrcode_global.h \
    $$PWD/src/qrcode_p.h \
    $$PWD/src/qrcode.h

SOURCES += \
    $$PWD/src/qrcode/cqrcoder.cpp \
    $$PWD/src/qrcode/decodethread.cpp \
    $$PWD/src/qrcode/decodeworkspace.cpp \
    $$PWD/src/qrcode/multimediautils.cpp \
    $$PWD/src/qrcode/qandroidmultimediautils.cpp \
    $$PWD/src/qrcode/qtcamera.cpp \
    $$PWD/src/qrcoderegister.cpp \
    $$PWD/src/qrcode.cpp



INCLUDEPATH += $$[QT_INSTALL_HEADERS]/../syberos_application
LIBS += -L/usr/lib/ -lsyberos-application

INCLUDEPATH += $$absolute_path("nativesdk/src", $$SYBERH_APP)
INCLUDEPATH += $$absolute_path("pluginmanager/src", $$SYBERH_APP)

LIB_OUT_DIR = $$absolute_path("lib", $$SYBERH_APP)
LIBS += -L$$LIB_OUT_DIR -lnativesdk -lpluginmanager

PLUGIN_OUT_DIR = $$absolute_path("plugins", $$SYBERH_APP)
DESTDIR = $$PLUGIN_OUT_DIR


QMAKE_LFLAGS += -Wl,-rpath=/data/apps/$$SOPID/lib


SYBERH_QT_VERSION = $$[QT_VERSION]
SYBERH_QT_VERSION = $$split(SYBERH_QT_VERSION, ".")
QT_VER_MIN = $$member(SYBERH_QT_VERSION, 1)


lessThan(QT_VER_MIN, 12) {
    message(Qt版本小于5.12)
    LIB_ZXING = $$PWD/lib/libzxing.so
    DISTFILES += $$LIB_ZXING
    QMAKE_PRE_LINK += $$system("cp $$LIB_ZXING $$LIB_OUT_DIR/libzxing.so")
    LIBS += -L$$PWD/lib -lzxing
} else {
    message(Qt版本大于等于5.12)
    LIB_ZXING = $$PWD/lib/libzxing_os5.so
    DISTFILES += $$LIB_ZXING
    QMAKE_PRE_LINK += $$system("cp $$LIB_ZXING $$LIB_OUT_DIR/libzxing_os5.so")
    LIBS += -L$$PWD/lib -lzxing_os5
}
