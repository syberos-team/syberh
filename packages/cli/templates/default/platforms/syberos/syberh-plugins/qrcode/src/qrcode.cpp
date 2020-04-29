#include "qrcode.h"
#include "qrcode_p.h"

#include "qrcoderegister.h"
#include "qmlmanager.h"
#include "qmlobject.h"

#include <SyberosGuiCache>

using namespace NativeSdk;

Qrcode::Qrcode()
{
    d = new QrcodePrivate();
}

Qrcode::~Qrcode()
{
    delete d;
}

void Qrcode::extensionsInitialized()
{
    QQuickView *m_view = SYBEROS::SyberosGuiCache::qQuickView();
    QrcodeRegister qrcode;
    qrcode.init(m_view);
}

void Qrcode::invoke(QString callbackID, QString action, QVariantMap params)
{
    Q_UNUSED(params)

    if(action == "scan"){
        scan(callbackID);
    }
}

void Qrcode::decodeFinished(QString decodeContent)
{
    QJsonObject json;
    json.insert("result", decodeContent);
    signalManager()->success(d->callbackID.toLong(), json);
}

void Qrcode::cancel()
{
    signalManager()->success(d->callbackID.toLong(), QVariant());
}

void Qrcode::scan(QString callbackID)
{
    d->callbackID = callbackID;

    QmlManager manager;

    d->qmlObject = manager.open("qrc:/qml/BarCodeScan.qml");

    manager.connectSignal(d->qmlObject, SIGNAL(decodeFinished(QString)), this, SLOT(decodeFinished(QString)));
    manager.connectSignal(d->qmlObject, SIGNAL(cancel()), this, SLOT(cancel()));
}

