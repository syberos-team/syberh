#include "image.h"
#include "framework/common/errorinfo.h"
#include "helper.h"
#include <QDir>
#include <QDateTime>
#include <QException>
#include <QJsonDocument>
#include <QJsonObject>
#include <QImage>

Image::Image()
{
}

void Image::invoke(QString callbackID, QString actionName, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "## invoke hello plugin(4)!!!" << "  callbackID:" << callbackID << "actionName:" << actionName << "params:" << params;

    if (actionName == "chooseImage") {
        chooseImage(callbackID, params);
    } else if (actionName == "previewImage") {
        previewImage(callbackID, params);
    } else if (actionName == "saveImageToPhotosAlbum") {
        saveImageToPhotosAlbum(callbackID, params);
    } else if (actionName == "getImageInfo") {
        getImageInfo(callbackID, params);
    }
}

void Image::chooseImage(QString callbackID, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "params" << params;
    globalCallbackID = callbackID.toLong();

    chooseImageQml = qmlManager.create("qrc:/qml/SChooseImagePage.qml");

    QJsonDocument json(QJsonObject::fromVariantMap(params));
    QString jsonString(json.toJson());

    qmlManager.connectSignal(chooseImageQml, SIGNAL(imageCancel()), this, SLOT(chooseCancel()));
    qmlManager.connectSignal(chooseImageQml, SIGNAL(receiveImageUrls(QString)), this, SLOT(receiveUrls(QString)));
    qmlManager.connectSignal(chooseImageQml, SIGNAL(chooseCameraSuccess(QString)), this, SLOT(cameraSuccess(QString)));
    qmlManager.connectSignal(chooseImageQml, SIGNAL(chooseCameraCancel()), this, SLOT(cameraCancel()));
    qmlManager.connectSignal(chooseImageQml, SIGNAL(chooseAlbumCancel()), this, SLOT(albumCancel()));

    qDebug() << Q_FUNC_INFO << "jsonString" << jsonString;

    qmlManager.call(chooseImageQml, "open(" + jsonString + ")");

    qDebug() << Q_FUNC_INFO << "currentItem***************" << qmlManager.currentItem();
}

void Image::chooseCancel()
{
    qDebug() << Q_FUNC_INFO << "chooseCancel***************";
    signalManager()->success(globalCallbackID, "");
    globalCallbackID = 0;
}

void Image::receiveUrls(QString filesPath)
{
    qDebug() << Q_FUNC_INFO << "receiveUrls***************" << filesPath;

    QJsonDocument jsonDocument = QJsonDocument::fromJson(filesPath.toLocal8Bit().data());
    if(jsonDocument.isNull()){
       qDebug()<< "===> please check the string "<< filesPath.toLocal8Bit().data();
    }

    QJsonObject result = jsonDocument.object();

    qDebug() << Q_FUNC_INFO << "result***************" << result;

    signalManager()->success(globalCallbackID, QVariant(result));
    qmlManager.destroy(chooseImageQml);
    globalCallbackID = 0;
}

void Image::cameraSuccess(QString filePath)
{
    qDebug() << Q_FUNC_INFO << "cameraSuccess***************" << filePath;

    QJsonDocument jsonDocument = QJsonDocument::fromJson(filePath.toLocal8Bit().data());
    if( jsonDocument.isNull() ){
       qDebug()<< "===> please check the string "<< filePath.toLocal8Bit().data();
    }
    QJsonObject result = jsonDocument.object();
    qDebug() << Q_FUNC_INFO << "result***************" << result;

    signalManager()->success(globalCallbackID, result);
    globalCallbackID = 0;
}

void Image::cameraCancel()
{
    qDebug() << Q_FUNC_INFO << "chooseCancel***************";
    signalManager()->success(globalCallbackID, "");
    globalCallbackID = 0;
}

void Image::albumCancel()
{
    qDebug() << Q_FUNC_INFO << "chooseCancel***************";
    signalManager()->success(globalCallbackID, "");
    globalCallbackID = 0;
}

void Image::previewImage(QString callbackID, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "params" << params;
    globalCallbackID = callbackID.toLong();

    previewQml = qmlManager.open("qrc:/qml/SPreviewImage.qml");

    qmlManager.connectSignal(previewQml, SIGNAL(success()), this, SLOT(previewImageSuccess()));

    QJsonDocument json(QJsonObject::fromVariantMap(params));
    QString jsonString(json.toJson());

    qmlManager.call(previewQml, "showPage(" + jsonString + ")");
}

void Image::previewImageSuccess()
{
    qDebug() << Q_FUNC_INFO;
    signalManager()->success(globalCallbackID, "");
    globalCallbackID = 0;
}

void Image::saveImageToPhotosAlbum(QString callbackID, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "params" << params << endl;
    globalCallbackID = callbackID.toLong();

    QString filePath = params.value("filePath").toString();

    if (filePath.isEmpty()) {
        qDebug() << Q_FUNC_INFO << "文件路径不能为空" << endl;
        signalManager()->failed(globalCallbackID, ErrorInfo::InvalidParameter, "不合法的参数:filePath不能为空");
        return;
    }

    bool ret = Helper::instance()->isPicture(filePath);
    if (!ret) {
        qDebug() << Q_FUNC_INFO << "不是图片文件" << endl;
        signalManager()->failed(globalCallbackID, ErrorInfo::IllegalMediaTypeError, "不合法的媒体文件类型:不是图片文件");
        return;
    }

    QFile file(filePath);
    if (!file.exists()) {
        qDebug() << Q_FUNC_INFO << "文件不存在：" << filePath << endl;
        signalManager()->failed(globalCallbackID, ErrorInfo::InvalidURLError, "无效的url:图片不存在");
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
        //将照片复制到系统相册
        QFile::copy(filePath, newFile);
    } catch (QException e) {
        qDebug() << Q_FUNC_INFO << "保存图片到系统相册失败" << endl;
        signalManager()->failed(globalCallbackID, ErrorInfo::SystemError, "系统错误:保存图片到系统相册失败");
        return;
    }

    signalManager()->success(globalCallbackID, newFile);
    globalCallbackID = 0;
}


void Image::getImageInfo(QString callbackID, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "params" << params << endl;
    globalCallbackID = callbackID.toLong();

    QString filePath = params.value("path").toString();

    if (filePath.isEmpty()) {
        qDebug() << Q_FUNC_INFO << "文件路径不能为空" << endl;
        signalManager()->failed(globalCallbackID, ErrorInfo::InvalidParameter, "不合法的参数:path不能为空");
        return;
    }

    QFile file(filePath);
    if (!file.exists()) {
        qDebug() << Q_FUNC_INFO << "图片不存在：" << filePath << endl;
        signalManager()->failed(globalCallbackID, ErrorInfo::InvalidURLError, "无效的url:图片不存在");
        return;
    }

    bool ret = Helper::instance()->isPicture(filePath);
    if (!ret) {
        qDebug() << Q_FUNC_INFO << "不是图片文件" << endl;
        signalManager()->failed(globalCallbackID, ErrorInfo::IllegalMediaTypeError, "不合法的媒体文件类型:不是图片文件");
        return;
    }

    QJsonObject jsonObject;

    QImage imageInfo = QImage(filePath);
    jsonObject.insert("width", imageInfo.width());
    jsonObject.insert("height", imageInfo.height());

    QFileInfo fileInfo(file);
    jsonObject.insert("fileName", fileInfo.fileName());
    jsonObject.insert("size", fileInfo.size());
    jsonObject.insert("created", fileInfo.created().toString("yyyy-MM-dd hh:mm:ss"));

    QStringList filenameArr = fileInfo.fileName().split(".");
    jsonObject.insert("type", filenameArr[filenameArr.length()-1]);

    signalManager()->success(globalCallbackID, QVariant(jsonObject));
    globalCallbackID = 0;
}


