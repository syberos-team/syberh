include(../syberos.pri)
QT -= gui

TEMPLATE = lib

TARGET = NativeSdkFrameWork

HEADERS += \
    nativesdkmanager.h \
    nativesdkhandlerbase.h \
    natviesdkfactory.h \
    common/networkstatus.h \
    common/errorinfo.h

SOURCES += \
    nativesdkmanager.cpp \
    nativesdkfactory.cpp \
    nativesdkhandlerbase.cpp \
    common/networkstatus.cpp \
    common/errorinfo.cpp

target.path = $$INSTALL_DIR/lib
INSTALLS += target
