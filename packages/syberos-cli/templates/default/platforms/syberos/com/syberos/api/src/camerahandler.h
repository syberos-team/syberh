#ifndef TESTHANDLER_H
#define TESTHANDLER_H

#include "framework/nativesdkhandlerbase.h"
class CameraHandler : public NativeSdkHandlerBase{
    Q_OBJECT
public:
  Q_INVOKABLE CameraHandler();
   ~CameraHandler();
   void request(QString callBackID,QString actionName,QVariantMap params);
   QObject * getUiSource(QString actionName);
   static int typeId;

public slots:
   void saveImage(int id,QString filePath);


};

#endif // TESTHANDLER_H
