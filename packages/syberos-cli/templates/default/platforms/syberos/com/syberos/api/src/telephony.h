#ifndef TELEPHONYHANDLER_H
#define TELEPHONYHANDLER_H
#include "framework/nativesdkhandlerbase.h"

class Telephony : public NativeSdkHandlerBase
{
    Q_OBJECT
public:
    Q_INVOKABLE Telephony();
    ~Telephony();
    void request(QString callBackID,QString actionName,QVariantMap params);
    void submit(QString typeID,QString callBackID,QString actionName,QVariant dataRowList, QVariant attachementes);

    static int typeId;

};
#endif // TELEPHONYHANDLER_H
