#include <QObject>
#include <QDebug>
#include <QException>
#include <QCameraInfo>
#include <QCameraImageCapture>
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QDateTime>

#include "camera.h"
#include "helper.h"
#include "framework/common/errorinfo.h"

using namespace NativeSdk;

Camera::Camera()
{
}


void Camera::invoke(QString callbackID, QString actionName, QVariantMap params)
{
    qDebug() << "  callbackID:" << callbackID << "actionName:" << actionName << "params:" << params;

    if (actionName == "changeImagePath") {
        changeCameraImagePath(callbackID, params);
    }
}

void Camera::changeCameraImagePath(QString callbackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "changeCameraImagePath" << params << endl;
    QString filePath = params.value("path").toString();

    QFile file(filePath);
    if(!file.exists()){
        qDebug() << Q_FUNC_INFO << "文件地址不存在：" << filePath << endl;
        signalManager()->failed(callbackID.toLong(), ErrorInfo::InvalidURLError, "无效的url:照片文件不存在");
        return;
    }

    //设置系统相机路径
    QString path = Helper::instance()->getInnerStorageRootPath() + "/DCIM";
    QDir dir(path);
    if(!dir.exists()){
        dir.mkpath(path);
    }
    QFileInfo fileInfo(file);

    //设置文件名
    QDateTime time = QDateTime::currentDateTime();   //获取当前时间
    int timeT = time.toTime_t();                     //将当前时间转为时间戳
    QStringList filenameArr = fileInfo.fileName().split(".");
    QString filename = filenameArr[0]+"_"+ QString::number(timeT)+"."+filenameArr[1];
    QString newFile = path + "/" + filename;

    try  {
        //将照片复制到系统相册后，删除原地址照片
        QFile::copy(filePath, newFile);
        file.remove();
    } catch (QException e) {
        qDebug() << Q_FUNC_INFO << "将照片移动到系统相册失败" << endl;
        signalManager()->failed(callbackID.toLong(), ErrorInfo::SystemError, "系统错误:将照片移动到系统相册失败");
        return;
    }

    QJsonObject jsonObject;
    jsonObject.insert("path", newFile);
    QJsonValue::fromVariant(jsonObject);
    signalManager()->success(callbackID.toLong(), QVariant(jsonObject));

//    camera = new QCamera;
//    QCameraInfo cameraInfo(camera);
//    cameraInfo.orientation();//获取照片角度
//    qDebug() << Q_FUNC_INFO << "cameraInfo.orientation(): " << cameraInfo.orientation() << endl;

}



