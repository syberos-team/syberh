#ifndef QRCODEREGISTER_H
#define QRCODEREGISTER_H

#include <QObject>
#include <QQuickView>

#include "./qrcode/decodeworkspace.h"
#include "./qrcode/qtcamera.h"

class QrcodeRegister: public QObject
{
    Q_OBJECT

public:
    QrcodeRegister();
    virtual ~QrcodeRegister();

    /*!
       \brief 将qrcode模块注册到QML对象中
     */
    void init(QQuickView * m_view);
};
#endif // QRCODEREGISTER_H
