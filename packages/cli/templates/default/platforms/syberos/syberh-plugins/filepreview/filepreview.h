#ifndef FILEPREVIEW_H
#define FILEPREVIEW_H

#include <QObject>
#include <QtPlugin>

#include "iplugin/iplugin.h"
#include "filepreview_global.h"
#include "qmlmanager.h"


using namespace NativeSdk;

class FilePreviewPrivate;

class FILEPREVIEWSHARED_EXPORT FilePreview: public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.syberos.syberh.SyberhPlugin" FILE "plugin.json")

public:
    FilePreview();

    void invoke(QString callbackID, QString actionName, QVariantMap params);
private:
    FilePreviewPrivate *d = nullptr;
};

#endif // FILEPREVIEW_H
