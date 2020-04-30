#include <QDir>
#include <QDateTime>
#include <QException>
#include "camera.h"
#include "framework/common/errorinfo.h"
#include "helper.h"
#include <SyberosGuiCache>
#include <QKeyEvent>

Camera::Camera()
{
}

void Camera::extensionsInitialized()
{
    // error signal
    connect(&qmlManager, SIGNAL(error(QString)), this, SLOT(error(QString)));
    qDebug() << Q_FUNC_INFO << "## hello plugin(2)!!!";
}

void Camera::invoke(QString callbackID, QString actionName, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "## invoke hello plugin(4)!!!" << "  callbackID:" << callbackID << "actionName:" << actionName << "params:" << params;

    if (actionName == "takePhoto") {
        takePhoto(callbackID, params);
    } else if (actionName == "changeCameraImagePath") {
        changeCameraImagePath(callbackID, params);
    }
}

void Camera::takePhoto(QString callbackID, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "params" << params;
    globalCallbackID = callbackID.toLong();

    QString enableCut = params.value("enableCut").toString();

    qDebug() << Q_FUNC_INFO << "currentItem***************" << qmlManager.currentItem();

    QVariant page = qmlManager.call(qmlManager.currentItem(), "var webviewPage = pageStack.currentPage;console.log(webviewPage);var cameraComponent = pageStack.push('qrc:/qml/SCamera.qml', {'pageItem': webviewPage, 'enableCut':"+ enableCut +"});cameraComponent");

    qDebug() << Q_FUNC_INFO << "page" << page;

    cameraQml = page.value<QQuickItem*>();

    connect(cameraQml, SIGNAL(imageConfirmed(QString, bool)), this, SLOT(imageConfirmed(QString)));
    connect(cameraQml, SIGNAL(imageCancele()), this, SLOT(imageCancele()));
}

void Camera::imageConfirmed(QString filePath)
{
    qDebug() << Q_FUNC_INFO << "filePath" << filePath<< "****************************";

    QJsonObject jsonObject;
    jsonObject.insert("path", filePath);

    signalManager()->success(globalCallbackID, QVariant(jsonObject));

    globalCallbackID = 0;

    qmlManager.call(cameraQml, "cameraBack()");
}

void Camera::error(QString errorMsg)
{
    qDebug() << Q_FUNC_INFO << "errorMsg::" << errorMsg;
    globalCallbackID = 0;
}


void Camera::imageCancele()
{
    qDebug() << Q_FUNC_INFO << "****************************";

    signalManager()->success(globalCallbackID, "");
    globalCallbackID = 0;
}


void Camera::changeCameraImagePath(QString callbackID, QVariantMap params){
    qDebug() << Q_FUNC_INFO << "changeCameraImagePath" << params << endl;
    globalCallbackID = callbackID.toLong();

    QString filePath = params.value("path").toString();

    QFile file(filePath);
    if (!file.exists()) {
        qDebug() << Q_FUNC_INFO << "文件地址不存在：" << filePath << endl;
        signalManager()->failed(globalCallbackID, ErrorInfo::InvalidURLError, "无效的url:照片文件不存在");
        return;
    }

    //设置系统相机路径
    QString path = Helper::instance()->getInnerStorageRootPath() + "/DCIM";
    QDir dir(path);
    if (!dir.exists()) {
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
        signalManager()->failed(globalCallbackID, ErrorInfo::SystemError, "系统错误:将照片移动到系统相册失败");
        return;
    }

    QJsonObject jsonObject;
    jsonObject.insert("path", newFile);
    QJsonValue::fromVariant(jsonObject);
    signalManager()->success(globalCallbackID, QVariant(jsonObject));
    globalCallbackID = 0;
}

