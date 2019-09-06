#include "filesystemmanager.h"
#include <QProcess>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QJsonObject>
#include <QDateTime>
#include <QDebug>

FileSystemManager::FileSystemManager()
{

}
QString FileSystemManager::move(QString srcPath, QString destPath)
{
    QProcess *proc = new QProcess();
    QString cmd="mv -f " + srcPath + " " + destPath;
    proc->start(cmd);
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
    proc->start("cp -rf " + srcPath + " " + destPath);
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

QString FileSystemManager::remove(QString srcPath, int recursive)
{
    QProcess *proc = new QProcess();
    if (recursive == 0) {
        proc->start("rm -f " + srcPath);
    } else {
        proc->start("rm -rf " + srcPath);
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

