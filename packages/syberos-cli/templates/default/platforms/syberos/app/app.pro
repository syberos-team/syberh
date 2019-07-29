include(../syberos.pri)
QT += gui qml quick widgets webkit network

TEMPLATE = app

TARGET = app

CONFIG += link_pkgconfig

RESOURCES += res.qrc

PKGCONFIG += syberos-application syberos-application-cache syberos-qt-system

QML_FILES = qml/*.qml

OTHER_FILES += $$QML_FILES *.qm \
    qml/logic.js


# The .cpp file which was generated for your project.
SOURCES += src/main.cpp \
           src/Demo_Workspace.cpp \
    src/helper.cpp \
    src/ui.cpp \
    src/globalobject.cpp \
    src/httpclient.cpp \
    src/download.cpp

HEADERS += src/Demo_Workspace.h \
    src/helper.h \
    src/ui.h \
    src/globalobject.h \
    src/httpclient.h \
    src/download.h

# Installation path
target.path = $$INSTALL_DIR/bin

qm.files = *.qm
qm.path = $$INSTALL_DIR/qm

web.files = www
web.path = $$INSTALL_DIR

INSTALLS += target qm web

