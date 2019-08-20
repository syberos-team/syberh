include(../syberos.pri)
include (../com/syberos/download/download.pri)
include (../com/syberos/core/core.pri)

QT += gui qml quick widgets webkit network multimedia core

TEMPLATE = app

TARGET = app

CONFIG += link_pkgconfig

RESOURCES += res.qrc

PKGCONFIG += syberos-application syberos-application-cache syberos-qt-system syberos-qt

QML_FILES = qml/*.qml

OTHER_FILES += $$QML_FILES *.qm

LIBS += -L../framework -lNativeSdkFrameWork
QMAKE_LFLAGS += -Wl,-rpath,$$INSTALL_DIR/lib
# The .cpp file which was generated for your project.
SOURCES += src/main.cpp \
           src/Demo_Workspace.cpp \


HEADERS += src/Demo_Workspace.h

# Installation path
target.path = $$INSTALL_DIR/bin

qm.files = *.qm
qm.path = $$INSTALL_DIR/qm

web.files = www
web.path = $$INSTALL_DIR

INSTALLS += target qm web

DISTFILES += \
    res/app.png

