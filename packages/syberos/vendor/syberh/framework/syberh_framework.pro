include (syberh_framework.pri)

QT += gui qml quick widgets webkit network multimedia core sql dbus

TARGET = syberh_framework

TEMPLATE = lib

CONFIG += link_pkgconfig
CONFIG += C++11

PKGCONFIG += syberos-application syberos-application-cache syberos-qt-system syberos-qt

INCLUDEPATH += $$[QT_INSTALL_HEADERS]/../syberos_application \
                           $$[QT_INSTALL_HEADERS]/../framework
