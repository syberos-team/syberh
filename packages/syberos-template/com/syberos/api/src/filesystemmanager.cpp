#include "filesystemmanager.h"
#include <QProcess>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QJsonObject>
#include <QDateTime>

FileSystemManager::FileSystemManager()
{

}
QString FileSystemManager::move(QString srcPath, QString destPath)
{
    QProcess *proc = new QProcess();
    proc->start("mv " + srcPath + " " + destPath);
    proc->waitForFinished();

    QString errTmp = proc->readAllStandardError();
    if (errTmp == "") {
        return "success";
    } else {
        return errTmp;
    }
}
QString FileSystemManager::copy(QString srcPath, QString destPath)
{
    QProcess *proc = new QProcess();
    proc->start("cp -r " + srcPath + " " + destPath);
    proc->waitForFinished();

    QString errTmp = proc->readAllStandardError();
    if (errTmp == "") {
        return "success";
    } else {
        return errTmp;
    }
}

QString FileSystemManager::fileList(QString srcPath)
{
    QProcess *proc = new QProcess();
    proc->start("ls " + srcPath);
    proc->waitForFinished();

    QString errTmp = proc->readAllStandardError();
    if (errTmp == "") {
        return "success";
    } else {
        return errTmp;
    }
}

FileSystemManager::FileType FileSystemManager::fileType(QString srcPath)
{

    if (!exists(srcPath)) {
        return FileSystemManager::Unknown;
    }

    QFileInfo fileinfo(srcPath);

    if (fileinfo.isFile()) {
        return FileSystemManager::File;
    } else if (fileinfo.isDir()) {
        return FileSystemManager::Folder;
    } else {
        return FileSystemManager::Unknown;
    }
}

QString FileSystemManager::remove(QString srcPath, FileSystemManager::FileType fileType, QString recursive)
{
    QProcess *proc = new QProcess();

    if (fileType == FileSystemManager::File) {
        proc->start("rm -rf " + srcPath);
    } else if (fileType == FileSystemManager::Folder){
        if (recursive == 0) {
            proc->start("rm -f " + srcPath);
        } else {
            proc->start("rm -rf " + srcPath);
        }
    } else {
        return "Error in fileType parameter";
    }

    proc->waitForFinished();

    QString errTmp = proc->readAllStandardError();
    if (errTmp == "") {
        return "success";
    } else {
        return errTmp;
    }
}
FileInfo FileSystemManager::getInfo(QString srcPath)
{
    FileInfo file;
    if (!exists(srcPath)) {
        return file;
    }
    QFileInfo fileinfo(srcPath);

    file.path = fileinfo.path();
    file.size = fileinfo.size();
    file.created = fileinfo.created().toString("yyyy-MM-dd hh:mm:ss");

    return file;
}
bool FileSystemManager::exists(QString srcPath)
{
    QFileInfo fileinfo(srcPath);
    return fileinfo.exists();
}

