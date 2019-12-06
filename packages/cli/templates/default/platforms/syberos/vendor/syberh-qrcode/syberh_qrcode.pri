
DEFINES += QRCODE

RESOURCES += \
    $$PWD/syberh_qrcode.qrc

HEADERS += \
    $$PWD/src/qrcode/cqrcoder.h \
    $$PWD/src/qrcode/decodethread.h \
    $$PWD/src/qrcode/decodeworkspace.h \
    $$PWD/src/qrcode/multimediautils.h \
    $$PWD/src/qrcode/qandroidmultimediautils.h \
    $$PWD/src/qrcode/qtcamera.h \
    $$PWD/src/qrcode/zxing.h \
    $$PWD/src/qrcoderegister.h

SOURCES += \
    $$PWD/src/qrcode/cqrcoder.cpp \
    $$PWD/src/qrcode/decodethread.cpp \
    $$PWD/src/qrcode/decodeworkspace.cpp \
    $$PWD/src/qrcode/multimediautils.cpp \
    $$PWD/src/qrcode/qandroidmultimediautils.cpp \
    $$PWD/src/qrcode/qtcamera.cpp \
    $$PWD/src/qrcoderegister.cpp


LIBS += -L$$PWD/lib -lzxing

libFile.files = $$PWD/lib/*
libFile.path = $$INSTALL_DIR/libs

INSTALLS += libFile

QMAKE_LFLAGS += -Wl,-rpath=$$LIB_DIR/

DISTFILES += \
    $$PWD/lib/libzxing.so
