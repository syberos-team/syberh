#include <QDebug>
#include <QQmlContext>
#include <QQmlEngine>
#include <QtQml>

#include "qrcoderegister.h"

QrcodeRegister::QrcodeRegister() {

}

QrcodeRegister::~QrcodeRegister() {

}

void QrcodeRegister::init(QQuickView * m_view) {
    qmlRegisterType<DecodeWorkSpace>("com.syberos.decodeWorkSpace", 1, 0, "DecodeWorkSpace");

    QtCamera *camera = QtCamera::getInstance();
    qDebug() << "QtCamera *camera = QtCamera::getInstance() ok";
    QQmlEngine::setObjectOwnership(camera, QQmlEngine::CppOwnership);
    m_view->rootContext()->setContextProperty("QtCamera", camera);
}
