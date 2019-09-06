#include "filesystemmanager.h"
#include <QProcess>

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

QString FileSystemManager::remove(QString srcPath)
{
    QProcess *proc = new QProcess();
    proc->start("rm -rf " + srcPath);
    proc->waitForFinished();

    QString errTmp = proc->readAllStandardError();
    if (errTmp == "") {
        return "success";
    } else {
        return errTmp;
    }
}
