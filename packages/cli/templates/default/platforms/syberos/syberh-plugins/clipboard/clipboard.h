#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <QObject>
#include <QtPlugin>

#include "iplugin/iplugin.h"
#include "clipboard_global.h"

class CLIPBOARDSHARED_EXPORT Clipboard: public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.syberos.syberh.SyberhPlugin" FILE "plugin.json")

public:
    Q_INVOKABLE Clipboard();

    void invoke(QString callbackID, QString actionName, QVariantMap params);
    
    void setClipboardData(QString callbackID,QVariantMap params);
    void getClipboardData(QString callbackID,QVariantMap params);
  
};

#endif // CLIPBOARD_H
