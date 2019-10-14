#ifndef CLIPBOARD_H
#define CLIPBOARD_H
#include <QObject>
#include <QClipboard>
#include <QApplication>
#include <QDebug>
#include <QMap>
#include "framework/nativesdkhandlerbase.h"

class Clipboard :  public NativeSdkHandlerBase{
    Q_OBJECT
public:
   Q_INVOKABLE Clipboard();
   ~Clipboard();
   void request(QString callBackID,QString actionName,QVariantMap params);
   void submit(QString typeID,QString callBackID,QString actionName,QVariant dataRowList, QVariant attachementes);
   void setClipboardData(long callBackID,QVariantMap params);
    void getClipboardData(long callBackID,QVariantMap params);
   static int typeId;
signals:

public slots:
};

#endif // CLIPBOARD_H
