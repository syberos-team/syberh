include(../syberos.pri)
QT -= gui

TEMPLATE = lib

TARGET = NativeSdkFrameWork

HEADERS += \
    nativesdkmanager.h \
    nativesdkhandlerbase.h \
    natviesdkfactory.h \
    common/networkstatus.h \
    common/errorinfo.h \
    common/extendedconfig.h

SOURCES += \
    nativesdkmanager.cpp \
    nativesdkfactory.cpp \
    nativesdkhandlerbase.cpp \
    common/networkstatus.cpp \
    common/errorinfo.cpp \
    common/extendedconfig.cpp

target.path = $$INSTALL_DIR/lib
INSTALLS += target


DEFINES += EX_CONFIG=\\\"$$EX_CONFIG\\\"
