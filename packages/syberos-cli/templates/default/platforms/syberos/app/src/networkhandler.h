#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include "../framework/nativesdkhandlerbase.h"
class NetWorkHandler : public NativeSdkHandlerBase
{
    Q_OBJECT

public:

    Q_INVOKABLE NetWorkHandler();
    ~NetWorkHandler();

    void request(QString callBackID,QString actionName,QVariantMap params);

    static int typeId;

 public slots:
    void failed(long callBackID, QString result, long errorCode);
    void sucess(long callBackID,QString result);

 private :
    void start(long callBackID,QVariantMap params);
};

#endif // NETWORKHANDLER_H
