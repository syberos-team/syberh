#ifndef PATH_H
#define PATH_H

#include <QObject>
#include "framework/nativesdkhandlerbase.h"

class Path : public NativeSdkHandlerBase
{
    Q_OBJECT
public:
    Q_INVOKABLE Path();
    ~Path();

    void request(QString callBackID,QString actionName,QVariantMap params);

    static int typeId;

private:
    void getExternStorageRootPath(QString callBackID);
    void getInnerStorageRootPath(QString callBackID);
    void getDataRootPath(QString callBackID);
};

#endif // PATH_H
