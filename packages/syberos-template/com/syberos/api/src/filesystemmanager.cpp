#include "filesystemmanager.h"
#include <QProcess>
#include <QFile>
#include <QDir>
#include <QFileInfo>

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

qint32 FileSystemManager::fileType(QString srcPath)
{
    QFileInfo fileinfo(srcPath);
    if (!fileinfo.exists()) {
        return "No such file or folder";
    }
    if (fileinfo.isFile()) {
        return 0;
    } else if (fileinfo.isDir()) {
        return 1;
    } else {
        return 2;
    }
}

QString FileSystemManager::remove(QString srcPath, QString fileType, QString recursive)
{
    QProcess *proc = new QProcess();

    if (fileType == 0) {
        proc->start("rm -rf " + srcPath);
    } else if (fileType == 1){
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
