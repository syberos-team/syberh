#include "fileutil.h"
#include <QProcess>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QJsonObject>
#include <QDateTime>
#include <QDebug>

FileUtil::FileUtil()
{

}
QString FileUtil::move(QString srcPath, QString destPath)
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
QString FileUtil::copy(QString srcPath, QString destPath)
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

QString FileUtil::fileList(QString srcPath)
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

FileUtil::FileType FileUtil::fileType(QString srcPath)
{

    if (!exists(srcPath)) {
        return FileUtil::Unknown;
    }

    QFileInfo fileinfo(srcPath);

    if (fileinfo.isFile()) {
        return FileUtil::File;
    } else if (fileinfo.isDir()) {
        return FileUtil::Folder;
    } else {
        return FileUtil::Unknown;
    }
}

QString FileUtil::remove(QString srcPath, int recursive)
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
FileInfo FileUtil::getInfo(QString srcPath)
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
bool FileUtil::exists(QString srcPath)
{
    QFileInfo fileinfo(srcPath);
    return fileinfo.exists();
}

