#ifndef MODAL_H
#define MODAL_H

#include <QObject>
#include <QtPlugin>

#include "iplugin/iplugin.h"
#include "modal_global.h"
#include "qmlmanager.h"

using namespace NativeSdk;

class MODALSHARED_EXPORT Modal: public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.syberos.syberh.SyberhPlugin" FILE "plugin.json")

public:
    Q_INVOKABLE Modal();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    bool delayedInitialize();
    void invoke(QString callbackID, QString action, QVariantMap params);

    void alert(QString callbackID, QVariantMap params);
    void confirm(QString callbackID, QVariantMap params);
    void prompt(QString callbackID, QVariantMap params);
    void toast(QString callbackID, QVariantMap params);
    void gtoast(QString callbackID, QVariantMap params);


private:
    long globalCallbackID;
    QmlManager qmlManager;
    QmlObject *alertQml;
    QmlObject *confirmQml;
    QmlObject *promptQml;
    QmlObject *toastQml;


public slots:
    void alertSuccess();
    void confirmSuccess();
    void confirmReject();
    void promptAccepted(QVariant value);
    void promptCancel();
};

#endif // MODAL_H
