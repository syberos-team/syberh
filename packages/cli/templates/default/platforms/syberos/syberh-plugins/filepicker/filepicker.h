#ifndef FILEPICKER_H
#define FILEPICKER_H

#include <QObject>
#include <QtPlugin>

#include "iplugin/iplugin.h"
#include "filepicker_global.h"
#include "qmlmanager.h"


using namespace NativeSdk;

class FILEPICKERSHARED_EXPORT Filepicker: public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.syberos.syberh.SyberhPlugin" FILE "plugin.json")

public:
    Filepicker();

    void invoke(QString callbackID, QString actionName, QVariantMap params);
    void open(QString callbackID, QVariantMap params);

private:
    long globalCallbackID;
    QmlManager qmlManager;
    QmlObject *filepickerQml = nullptr;

public slots:
    void chooseOk(QString filesPath);
    void chooseCancel();
};

#endif // FILEPICKER_H
