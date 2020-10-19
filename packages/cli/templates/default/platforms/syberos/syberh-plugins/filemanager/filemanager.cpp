#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>
#include "filemanager.h"
#include "util/fileutil.h"

using namespace NativeSdk;

FileManager::FileManager()
{
}


void FileManager::invoke(QString callbackID, QString actionName, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "## invoke hello plugin(4)!!!" << "  callbackID:" << callbackID << "actionName:" << actionName << "params:" << params;
    if (actionName == "move") {
        move(callbackID, params.value("srcPath").toString(), params.value("destPath").toString());
    } else if (actionName == "copy") {
        copy(callbackID, params.value("srcPath").toString(), params.value("destPath").toString());
    } else if (actionName == "fileList") {
        fileList(callbackID, params.value("srcPath").toString());
    } else if (actionName == "getInfo") {
        getInfo(callbackID, params.value("srcPath").toString());
    } else if (actionName == "remove") {
        bool ok;
        remove(callbackID, params.value("srcPath").toString(), params.value("recursive").toString().toInt(&ok,10));
    }
}

void FileManager::move(QString callbackID, QString srcPath, QString destPath) {
    RespResult resp = FileUtil::move(srcPath, destPath);
    if (resp.flag) {
        QJsonObject jsonObj;
        jsonObj.insert("result", resp.flag);
        signalManager()->success(callbackID.toLong(), jsonObj);
    } else {
        signalManager()->failed(callbackID.toLong(), resp.code, resp.msg);
    }
}
void FileManager::copy(QString callbackID, QString srcPath, QString destPath) {
    RespResult resp = FileUtil::copy(srcPath, destPath);

    if (resp.flag) {
        QJsonObject jsonObj;
        jsonObj.insert("result", resp.flag);
        signalManager()->success(callbackID.toLong(), jsonObj);
    } else {
        signalManager()->failed(callbackID.toLong(), resp.code, resp.msg);
    }

}
void FileManager::fileList(QString callbackID, QString srcPath) {
    QFileInfoList fileInfos = FileUtil::fileList(srcPath);
    QJsonArray jsonArr;
    if (fileInfos.size() != 0) {
        for (int i = 0; i < fileInfos.size(); i++) {
            QJsonObject jsonObj;
            jsonObj.insert("path", fileInfos.at(i).filePath());
            jsonObj.insert("size", fileInfos.at(i).size());
            jsonObj.insert("created", fileInfos.at(i).created().toString("yyyy-MM-dd hh:mm:ss"));
            if (fileInfos.at(i).isDir()) {
                jsonObj.insert("isDir", true);
            } else {
                jsonObj.insert("isDir", false);
            }
            jsonArr.append(jsonObj);
        }
    }
    signalManager()->success(callbackID.toLong(), jsonArr);
}

void FileManager::getInfo(QString callbackID, QString srcPath) {
    FileInfo fileInfo = FileUtil::getInfo(srcPath);
    QJsonObject jsonObj;
    jsonObj.insert("created", fileInfo.created);
    jsonObj.insert("filePath", fileInfo.path);
    if (fileInfo.path == "") {
        jsonObj.insert("size", 0);
    } else {
        jsonObj.insert("size", fileInfo.size);
    }

    signalManager()->success(callbackID.toLong(), jsonObj);
}

void FileManager::remove(QString callbackID, QString srcPath, int recursive) {
    RespResult resp = FileUtil::remove(srcPath, recursive);

    if (resp.flag) {
        QJsonObject jsonObj;
        jsonObj.insert("result", resp.flag);
        signalManager()->success(callbackID.toLong(), jsonObj);
    } else {
        signalManager()->failed(callbackID.toLong(), resp.code, resp.msg);
    }
}
