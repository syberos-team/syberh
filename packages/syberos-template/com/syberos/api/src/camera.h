#ifndef SYSTEM_H
#define SYSTEM_H

#include "framework/nativesdkhandlerbase.h"
class Camera : public NativeSdkHandlerBase
{
    Q_OBJECT
public:
    Q_INVOKABLE Camera();
    ~Camera();

    void request(QString callBackID,QString actionName,QVariantMap params);
    void submit(QString typeID,QString callBackID,QString actionName,QVariant dataRowList, QVariant attachementes);

    static int typeId;

private :

    /**
     * @brief changeCameraImagePath 修改相机图片路径
     * @param params 参数
     * @return 成功则返回图片路径。
     *      失败则返回错误码。
     */
    void changeCameraImagePath(long callBackID, QVariantMap params);

};

#endif // SYSTEMINFO_H
