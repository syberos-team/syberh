#ifndef QRCODE_P_H
#define QRCODE_P_H

#include <QString>
#include "qmlobject.h"


class QrcodePrivate {
public:
    QString callbackID;

    NativeSdk::QmlObject *qmlObject;
};

#endif // QRCODE_P_H
