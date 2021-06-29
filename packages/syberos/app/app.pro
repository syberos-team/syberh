include(../syberos.pri)

SYBERH_QT_VERSION = $$[QT_VERSION]
SYBERH_QT_VERSION = $$split(SYBERH_QT_VERSION, ".")
QT_VER_MIN = $$member(SYBERH_QT_VERSION, 1)

QT += gui qml quick widgets core

TEMPLATE = app

TARGET = app

CONFIG += link_pkgconfig
CONFIG += C++11

RESOURCES += app.qrc

lessThan(QT_VER_MIN, 12) {
    lessThan(QT_VER_MIN, 6) {
        message(Qt版本小于5.6)
        QT += webkit
        RESOURCES += res2.qrc
    } else {
        message(Qt版本大于等于5.6小于5.12)
        QT += webengine webchannel
        RESOURCES += res4.qrc
    }
} else {
    message(Qt版本大于等于5.12)
    QT += webengine webchannel
    RESOURCES += res5.qrc
}

PKGCONFIG += syberos-application syberos-application-cache syberos-qt

QML_FILES = qml/*.qml

OTHER_FILES += $$QML_FILES *.qm

QMAKE_LFLAGS += -Wl,-rpath=$$INSTALL_DIR/lib
# The .cpp file which was generated for your project.
SOURCES += src/main.cpp \
    src/App_Workspace.cpp


HEADERS += \
    src/App_Workspace.h

# Installation path
target.path = $$INSTALL_DIR/bin

qm.files = *.qm
qm.path = $$INSTALL_DIR/qm

res.files = res/*.png
res.path = $$INSTALL_DIR/res

web.files = www
web.path = $$INSTALL_DIR

INSTALLS += target qm web res

DISTFILES += \
    res/app.png

LIB_OUT_DIR = $$clean_path($$PWD/../lib)
LIBS += -L$$LIB_OUT_DIR -lpluginmanager
LIBS += -L$$LIB_OUT_DIR -lnativesdk

CONFIG(release, debug|release){
    QMAKE_POST_LINK=$(STRIP) $(TARGET)
}