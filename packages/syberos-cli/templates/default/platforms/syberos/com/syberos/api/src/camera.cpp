#include "camera.h"
#include "helper.h"
#include <QObject>
#include <QDebug>
#include <QCameraInfo>
#include <QCameraImageCapture>

int Camera::typeId = qRegisterMetaType<Camera *>();
Camera::Camera()
{

}
Camera::~Camera()
{

}

void Camera::request(QString callBackID, QString actionName, QVariantMap params)
{
  if (actionName == "changeImagePath")
  {
    changeCameraImagePath(callBackID.toLong(), params);
  }

}
void Camera::submit(QString typeID, QString callBackID, QString actionName, QVariant dataRowList, QVariant attachementes)
{
    Q_UNUSED(typeID)
    Q_UNUSED(callBackID)
    Q_UNUSED(actionName)
    Q_UNUSED(dataRowList)
    Q_UNUSED(attachementes)
}

void  Camera::changeCameraImagePath(long callBackID,QVariantMap params){
    QString filePath = params.value("path").toString();

    QFile file(filePath);
    if(!file.exists()){
        qDebug() << Q_FUNC_INFO << "file not exists" << filePath << endl;
    }

    QString path = Helper::instance()->getInnerStorageRootPath() + "/DCIM";
    QDir dir(path);
    if(!dir.exists()){
        dir.mkpath(path);
    }
    QFileInfo fileInfo(file);

    QDateTime time = QDateTime::currentDateTime();   //获取当前时间
    int timeT = time.toTime_t();                     //将当前时间转为时间戳
    QStringList filenameArr = fileInfo.fileName().split(".");
    QString filename = filenameArr[0]+"_"+ QString::number(timeT)+"."+filenameArr[1];
    qDebug() << Q_FUNC_INFO << "filename" << filename << endl;

    QString newFile = path + "/" + filename;
    qDebug() << Q_FUNC_INFO << "copy" << filePath << newFile << endl;

    bool rs = QFile::copy(filePath, newFile);
    qDebug() << Q_FUNC_INFO << "copy result" << rs << endl;

    bool removeRs = file.remove();
    qDebug() << Q_FUNC_INFO << "remove result" << removeRs << endl;

    QJsonObject jsonObject;
    jsonObject.insert("imgPath", newFile);

    QJsonValue jsonObjectValue = QJsonValue::fromVariant(jsonObject);
    qDebug() << Q_FUNC_INFO << "imgPath: " << jsonObjectValue.toString() << endl;

//    camera = new QCamera;
//    QCameraInfo cameraInfo(camera);
//    cameraInfo.orientation();
//    qDebug() << Q_FUNC_INFO << "cameraInfo.orientation(): " << cameraInfo.orientation() << endl;

    emit success(callBackID, QVariant(jsonObject));
}


