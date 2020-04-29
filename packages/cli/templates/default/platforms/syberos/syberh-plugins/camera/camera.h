#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QtPlugin>

#include "iplugin/iplugin.h"
#include "camera_global.h"

class CAMERASHARED_EXPORT Camera : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.syberos.syberh.SyberhPlugin" FILE "plugin.json")

public:
    Camera();

    void invoke(QString callbackID, QString actionName, QVariantMap params);

private :
    /**
     * @brief changeCameraImagePath 修改相机图片路径
     * @param params 参数
     * @return 成功则返回图片路径。
     *      失败则返回错误码。
     */
    void changeCameraImagePath(QString callbackID, QVariantMap params);
};

#endif // CAMERA_H
