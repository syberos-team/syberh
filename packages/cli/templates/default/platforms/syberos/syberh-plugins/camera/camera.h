#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QtPlugin>
#include<QQuickView>
#include <QQuickItem>

#include "iplugin/iplugin.h"
#include "camera_global.h"
#include "qmlmanager.h"

using namespace NativeSdk;

class CAMERASHARED_EXPORT Camera: public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.syberos.syberh.SyberhPlugin" FILE "plugin.json")

public:
    Q_INVOKABLE Camera();

    void extensionsInitialized();
    void invoke(QString callbackID, QString action, QVariantMap params);

    void takePhoto(QString callbackID, QVariantMap params);

private:
    long globalCallbackID;
    QmlManager qmlManager;
    //QmlObject *cameraQml;
    QQuickItem *cameraQml;

    /**
     * @brief changeCameraImagePath 修改相机图片路径
     * @param params 参数
     * @return 成功则返回图片路径。
     *      失败则返回错误码。
     */
    void changeCameraImagePath(QString callbackID, QVariantMap params);

public slots:
    void imageConfirmed(QString filePath);
    void imageCancele();
    void error(QString errorMsg);
};

#endif // CAMERA_H
