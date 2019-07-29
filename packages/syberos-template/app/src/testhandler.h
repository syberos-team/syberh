#ifndef TESTHANDLER_H
#define TESTHANDLER_H

#include "../framework/nativesdkhandlerbase.h"
class TestHandler : public NativeSdkHandlerBase{
    Q_OBJECT
public:
  Q_INVOKABLE TestHandler();
   ~TestHandler();
   void request(QString callBackID,QString actionName,QVariantMap params);
   void submit();

   static int typeId;

public slots:
   void downLoadFailed(long downloadID, QString result, long errorCode);
   void downLoadSucess(long downloadID,QString result);
private :
   void  downLoadStart(long callBackID,QVariantMap params);

};

#endif // TESTHANDLER_H
