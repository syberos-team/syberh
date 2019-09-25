#include "fileutil.h"
#include <QProcess>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QJsonObject>
#include <QDateTime>
#include <QDebug>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>


FileUtil::FileUtil()
{

}
RespResult FileUtil::move(QString srcPath, QString destPath)
{

    RespResult respResult;
    // 判断目标文件是否存在
    QFileInfo destInfo(destPath);
    if (!destInfo.exists()) {
        respResult.flag = false;
        respResult.msg = "文件路径：" + destPath + "，不存在。";
        return respResult;
    }
    // 判断目标文件是否是文件夹
    if (!destInfo.isDir()) {
        respResult.flag = false;
        respResult.msg = "文件路径：" + destPath + "，不是文件夹。";
        return respResult;
    }
    // 判断目标文件是否有写权限
    if (!destInfo.isWritable()) {
        respResult.flag = false;
        respResult.msg = "文件路径：" + destPath + "，权限不足。";
        return respResult;
    }

    // 判断文件读写权限
    // 如果文件没有权限，exists 为false
    QFileInfo srcInfo(srcPath);
    if (!srcInfo.exists() || !srcInfo.isReadable() || !srcInfo.isWritable()) {
        respResult.flag = false;
        respResult.msg = "文件路径：" + srcPath + "，不存在或权限不足。";
        return respResult;
    }

    QProcess *proc = new QProcess();
    QString cmd="mv -f " + srcPath + " " + destPath;
    proc->start(cmd);
    proc->waitForFinished();

    QString errTmp = proc->readAllStandardError();
    if (errTmp == "") {
        respResult.flag = true;
        return respResult;
    } else {
        qDebug() << Q_FUNC_INFO << "error : " << errTmp << endl;       
        respResult.flag = false;
        respResult.msg = errTmp;
        return respResult;

    }
}

bool FileUtil::chmodr(QString path)
{
    if (path.isEmpty()){
        return false;
    }
    QDir dir(path);
    if(!dir.exists()){
        return false;
    }
    chmod(path.toStdString().c_str(), S_IRWXU|S_IRWXG|S_IRWXO);
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach (QFileInfo fi, fileList){
        if (fi.isFile()) {
            QString p = path +"/" + fi.fileName();
            chmod(p.toStdString().c_str(), S_IRWXU|S_IRWXG|S_IRWXO);
        } else if (fi.isDir()) {
            chmod(fi.absoluteFilePath().toStdString().c_str(), S_IRWXU|S_IRWXG|S_IRWXO);
            chmodr(fi.absoluteFilePath());
        }
        else{
        }
    }
    return true;
}

RespResult FileUtil::copy(QString srcPath, QString destPath)
{

    RespResult respResult;
    // 判断目标文件是否存在
    QFileInfo destInfo(destPath);
    if (!destInfo.exists()) {
        respResult.flag = false;
        respResult.msg = "文件路径：" + destPath + "，不存在。";
        return respResult;
    }
    // 判断目标文件是否是文件夹
    if (!destInfo.isDir()) {
        respResult.flag = false;
        respResult.msg = "文件路径：" + destPath + "，不是文件夹。";
        return respResult;
    }
    // 判断目标文件是否有写权限
    if (!destInfo.isWritable()) {
        respResult.flag = false;
        respResult.msg = "文件路径：" + destPath + "，权限不足。";
        return respResult;
    }

    QFileInfo srcInfo(srcPath);
    // 判断文件读写权限
    // 如果文件没有权限，exists 为false
    if (!srcInfo.exists() || !srcInfo.isReadable()) {
        respResult.flag = false;
        respResult.msg = "文件路径：" + srcPath + "，不存在或权限不足。";
        return respResult;
    }

    QProcess *proc = new QProcess();
    proc->start("cp -rf " + srcPath + " " + destPath);
    proc->waitForFinished();

    QString errTmp = proc->readAllStandardError();

    if (errTmp == "") {
        respResult.flag = true;
        return respResult;
    } else {
        qDebug() << Q_FUNC_INFO << "error : " << errTmp << endl;      
        respResult.flag = false;
        respResult.msg = errTmp;
        return respResult;

    }
}

QFileInfoList FileUtil::fileList(QString srcPath)
{
    QDir dir(srcPath);
    QStringList filters;
    return dir.entryInfoList(filters, QDir::AllDirs|QDir::Files);
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

RespResult FileUtil::remove(QString srcPath, int recursive)
{
    RespResult respResult;

    QFileInfo srcInfo(srcPath);
    if (!srcInfo.exists()) {
        respResult.flag = false;
        respResult.msg = "文件路径：" + srcPath + "，不存在。";
        return respResult;
    }
    // 判断文件读写权限
    if (!srcInfo.isReadable() || !srcInfo.isWritable()) {
        respResult.flag = false;
        respResult.msg = "文件路径：" + srcPath + "，权限不足。";
        return respResult;
    }

    QProcess *proc = new QProcess();
    if (recursive == 0) {
        proc->start("rm -f " + srcPath);
    } else {
        proc->start("rm -rf " + srcPath);
    }

    proc->waitForFinished();

    QString errTmp = proc->readAllStandardError();

    if (errTmp == "") {
        respResult.flag = true;
        return respResult;
    } else {
        qDebug() << Q_FUNC_INFO << "error : " << errTmp << endl;       
        respResult.flag = false;
        respResult.msg = errTmp;
        return respResult;

    }
}
FileInfo FileUtil::getInfo(QString srcPath)
{
    FileInfo file;
    if (!exists(srcPath)) {
        return file;
    }
    QFileInfo fileinfo(srcPath);

    file.path = fileinfo.filePath();
    file.size = fileinfo.size();
    file.created = fileinfo.created().toString("yyyy-MM-dd hh:mm:ss");

    return file;
}

qint64 FileUtil::getInfoSize(QString srcPath)
{
    FileInfo file;
    if (!exists(srcPath)) {
        return 0;
    }
    QFileInfo fileinfo(srcPath);

    file.size = fileinfo.size();

    return file.size;
}

bool FileUtil::exists(QString srcPath)
{
    QFileInfo fileinfo(srcPath);
    return fileinfo.exists();
}
RespResult FileUtil::rename(QString srcPath, QString newName)
{
    RespResult respResult;

    QFileInfo srcInfo(srcPath);
    if (!srcInfo.exists()) {
        respResult.flag = false;
        respResult.msg = "文件：" + srcPath + "，不存在。";
        return respResult;
    }
    // 判断文件读写权限
    if (!srcInfo.isReadable() || !srcInfo.isWritable()) {
        respResult.flag = false;
        respResult.msg = "文件：" + srcPath + "，权限不足。";
        return respResult;
    }
    QFile srcFile(srcPath);

    respResult.flag = srcFile.rename(newName);

    return respResult;

}



