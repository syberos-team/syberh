#ifndef PATH_H
#define PATH_H

#include <QObject>
#include <QtPlugin>

#include "iplugin/iplugin.h"
#include "path_global.h"

class PATHSHARED_EXPORT Path: public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.syberos.syberh.SyberhPlugin" FILE "plugin.json")

public:
    Path();

    void invoke(QString callbackID, QString actionName, QVariantMap params);

private :

    void getExternStorageRootPath(QString callbackID);
    void getInnerStorageRootPath(QString callbackID);
    void getDataRootPath(QString callbackID);
};

#endif // PATH_H
