#ifndef CONTACT_H
#define CONTACT_H

#include <QObject>
#include "framework/nativesdkhandlerbase.h"
#include <ccontactmodel.h>

class Contact : public NativeSdkHandlerBase
{

    Q_OBJECT
public:
    Q_INVOKABLE Contact();
    ~Contact();

    void request(QString callBackID,QString actionName,QVariantMap params);
    void submit(QString typeID,QString callBackID,QString actionName,QVariant dataRowList, QVariant attachementes);

    void pick(long callBackID, QVariantMap params);
    static int typeId;

private:
    CContactModel *ccontant;
};

#endif // CONTACT_H
