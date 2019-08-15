#ifndef BARCODE_H
#define BARCODE_H

#include "../framework/nativesdkhandlerbase.h"

class Barcode : public NativeSdkHandlerBase
{
    Q_OBJECT
public:
    Q_INVOKABLE Barcode();
    ~Barcode();
    void request(QString callBackID,QString actionName,QVariantMap params);
    void submit(QString typeID,QString callBackID,QString actionName,QVariant dataRowList, QVariant attachementes);

    QString scan(QString callbackId, QString filePath);

    static int typeId;
};

#endif // BARCODE_H
