#include "filemanager.h"
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QDebug>
#include <QProcess>
#include "util/fileutil.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QDateTime>
#include <QJsonDocument>

int FileManager::typeId = qRegisterMetaType<FileManager *>();


FileManager::FileManager()
{
}
FileManager::~FileManager()
{

}
void FileManager::request(QString callBackID, QString actionName, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "FileManager callbackID is" << callBackID << "actionName is" << actionName << "params is" << params << endl;
    if (actionName == "move") {
        move(callBackID, params.value("srcPath").toString(), params.value("destPath").toString());
    } else if (actionName == "copy") {
        copy(callBackID, params.value("srcPath").toString(), params.value("destPath").toString());
    } else if (actionName == "fileList") {
        fileList(callBackID, params.value("srcPath").toString());
    } else if (actionName == "getInfo") {
        getInfo(callBackID, params.value("srcPath").toString());
    } else if (actionName == "remove") {
        bool ok;
        remove(callBackID, params.value("srcPath").toString(), params.value("recursive").toString().toInt(&ok,10));
    }
}

void FileManager::move(QString callbackId, QString srcPath, QString destPath)
{
    bool res = FileUtil::move(srcPath, destPath);
    emit success(callbackId.toLong(), res);
}
void FileManager::copy(QString callbackId, QString srcPath, QString destPath)
{
    bool res = FileUtil::copy(srcPath, destPath);
    emit success(callbackId.toLong(), res);
}
void FileManager::fileList(QString callbackId, QString srcPath)
{
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
    emit success(callbackId.toLong(), jsonArr);
}

void FileManager::getInfo(QString callBackID, QString srcPath)
{
    FileInfo fileInfo = FileUtil::getInfo(srcPath);
    QJsonObject jsonObj;
    jsonObj.insert("created", fileInfo.created);
    jsonObj.insert("filePath", fileInfo.path);
    if (fileInfo.path == "") {
        jsonObj.insert("size", 0);
    } else {
        jsonObj.insert("size", fileInfo.size);
    }

    emit success(callBackID.toLong(), jsonObj);
}

void FileManager::remove(QString callBackID, QString srcPath, int recursive)
{
    bool res = FileUtil::remove(srcPath, recursive);
    emit success(callBackID.toLong(), res);
}
