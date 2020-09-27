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

namespace NativeSdk {

FileUtil::FileUtil()
{

}
RespResult FileUtil::move(QString srcPath, QString destPath)
{
    qDebug() << Q_FUNC_INFO << "srcPath: " << srcPath << " destPath: " << destPath;

    RespResult respResult;
    // 判断目标文件是否存在
    QFileInfo destInfo(destPath);
    if (!destInfo.exists()) {
        qDebug() << Q_FUNC_INFO << "判断目标文件是否存在: " << destInfo.exists();
        respResult.code = ErrorInfo::FileNotExists;
        respResult.flag = false;
        respResult.msg = ErrorInfo::message(ErrorInfo::FileNotExists, destPath);
        return respResult;
    }
    // 判断目标文件是否是文件夹
    if (!destInfo.isDir()) {
        qDebug() << Q_FUNC_INFO << "判断目标文件是否是文件夹: " << destInfo.isDir();
        respResult.flag = false;
        respResult.code = ErrorInfo::IllegalFileType;
        respResult.msg = ErrorInfo::message(ErrorInfo::IllegalFileType, destPath);
        return respResult;
    }
    // 判断目标文件是否有写权限
    if (!destInfo.isWritable()) {
        qDebug() << Q_FUNC_INFO << "判断目标文件是否有写权限: " << destInfo.isWritable();
        respResult.flag = false;
        respResult.code = ErrorInfo::InvalidFilePermission;
        respResult.msg = ErrorInfo::message(ErrorInfo::InvalidFilePermission, destPath);
        return respResult;
    }

    // 判断文件读写权限
    // 如果文件没有权限，exists 为false
    QFileInfo srcInfo(srcPath);
    if (!srcInfo.exists() || !srcInfo.isReadable() || !srcInfo.isWritable()) {
        qDebug() << Q_FUNC_INFO << "判断文件读写权限: " << "srcInfo.exists: " << srcInfo.exists();
        qDebug() << Q_FUNC_INFO << "判断文件读写权限: " << "srcInfo.isReadable: " << srcInfo.isReadable();
        qDebug() << Q_FUNC_INFO << "判断文件读写权限: " << "srcInfo.isWritable: " << srcInfo.isWritable();
        respResult.flag = false;
        respResult.code = ErrorInfo::InvalidFilePermission;
        respResult.msg = ErrorInfo::message(ErrorInfo::InvalidFilePermission, srcPath + "，或不存在");
        return respResult;
    }

    QProcess proc;// = new QProcess();
    QString cmd="mv -f \"" + srcPath + "\" \"" + destPath + "\"";
    qDebug() << Q_FUNC_INFO << "执行命令: "  << cmd;
    proc.start(cmd);
    proc.waitForFinished();

    QString errTmp = proc.readAllStandardError();

    qDebug() << Q_FUNC_INFO << "errTmp: "  << errTmp;

    if (errTmp == "") {
        respResult.flag = true;
        return respResult;
    } else {
        qDebug() << Q_FUNC_INFO << "error : " << errTmp << endl;
        respResult.flag = false;
        respResult.code = ErrorInfo::SystemError;
        respResult.msg = ErrorInfo::message(ErrorInfo::SystemError, errTmp);
        return respResult;

    }
}

bool FileUtil::chmodr(QString path)
{
    qDebug() << Q_FUNC_INFO << "path: " << path;

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
    qDebug() << Q_FUNC_INFO << "srcPath: " << srcPath << " destPath: " << destPath;

    RespResult respResult;
    // 判断目标文件是否存在
    QFileInfo destInfo(destPath);
    if (!destInfo.exists()) {
        qDebug() << Q_FUNC_INFO << "判断目标文件是否存在: " << destInfo.exists();

        respResult.code = ErrorInfo::FileNotExists;
        respResult.flag = false;
        respResult.msg = ErrorInfo::message(ErrorInfo::FileNotExists, destPath);
        return respResult;
    }
    // 判断目标文件是否是文件夹
    if (!destInfo.isDir()) {
        qDebug() << Q_FUNC_INFO << "判断目标文件是否是文件夹: " << destInfo.isDir();

        respResult.flag = false;
        respResult.code = ErrorInfo::IllegalFileType;
        respResult.msg = ErrorInfo::message(ErrorInfo::IllegalFileType, destPath);
        return respResult;
    }
    // 判断目标文件是否有写权限
    if (!destInfo.isWritable()) {
        qDebug() << Q_FUNC_INFO << "判断目标文件是否有写权限: " << destInfo.isWritable();

        respResult.flag = false;
        respResult.code = ErrorInfo::InvalidFilePermission;
        respResult.msg = ErrorInfo::message(ErrorInfo::InvalidFilePermission, destPath);
        return respResult;
    }

    QFileInfo srcInfo(srcPath);
    // 判断文件读写权限
    // 如果文件没有权限，exists 为false
    if (!srcInfo.exists() || !srcInfo.isReadable()) {
        qDebug() << Q_FUNC_INFO << "判断文件读写权限: " << "srcInfo.exists: " << srcInfo.exists();
        qDebug() << Q_FUNC_INFO << "判断文件读写权限: " << "srcInfo.isReadable: " << srcInfo.isReadable();

        respResult.flag = false;
        respResult.code = ErrorInfo::InvalidFilePermission;
        respResult.msg = ErrorInfo::message(ErrorInfo::InvalidFilePermission, "不存在");
        return respResult;
    }

    QProcess proc;// = new QProcess();
    QString cmd = "cp -rf \"" + srcPath + "\" \"" + destPath + "\"";

    qDebug() << Q_FUNC_INFO << "拷贝命令: " << cmd;

    proc.start(cmd);
    proc.waitForFinished();

    QString errTmp = proc.readAllStandardError();

    qDebug() << Q_FUNC_INFO << "errTmp: " << errTmp;

    if (errTmp == "") {
        respResult.flag = true;
        return respResult;
    } else {
        qDebug() << Q_FUNC_INFO << "error : " << errTmp << endl;

        respResult.flag = false;
        respResult.code = ErrorInfo::SystemError;
        respResult.msg = ErrorInfo::message(ErrorInfo::SystemError, errTmp);
        return respResult;
    }
}

QFileInfoList FileUtil::fileList(QString srcPath)
{
    qDebug() << Q_FUNC_INFO << "srcPath: " << srcPath;

    QDir dir(srcPath);
    QStringList filters;
    return dir.entryInfoList(filters, QDir::AllDirs|QDir::Files);
}

FileUtil::FileType FileUtil::fileType(QString srcPath)
{
    qDebug() << Q_FUNC_INFO << "srcPath: " << srcPath;

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
    qDebug() << Q_FUNC_INFO << "srcPath: " << srcPath << " recursive: " << recursive;

    RespResult respResult;

    QFileInfo srcInfo(srcPath);
    if (!srcInfo.exists()) {
        respResult.code = ErrorInfo::FileNotExists;
        respResult.flag = false;
        respResult.msg = ErrorInfo::message(ErrorInfo::FileNotExists, srcPath);
        return respResult;
    }
    // 判断文件读写权限
    if (!srcInfo.isReadable() || !srcInfo.isWritable()) {
        respResult.flag = false;
        respResult.code = ErrorInfo::InvalidFilePermission;
        respResult.msg = ErrorInfo::message(ErrorInfo::InvalidFilePermission, srcPath);
        return respResult;
    }

    QProcess proc;// = new QProcess();
    QString cmd = "rm -rf \"" + srcPath + "\"";
    if (recursive == 0) {
        cmd = "rm -f \"" + srcPath + "\"";
    }
    qDebug() << Q_FUNC_INFO << "执行命令: " << cmd;
    proc.start(cmd);

    proc.waitForFinished();

    QString errTmp = proc.readAllStandardError();

    qDebug() << Q_FUNC_INFO << "errTmp" << errTmp;

    if (errTmp == "") {
        respResult.flag = true;
        return respResult;
    } else {
        qDebug() << Q_FUNC_INFO << "error : " << errTmp << endl;

        respResult.flag = false;
        respResult.code = ErrorInfo::SystemError;
        respResult.msg = ErrorInfo::message(ErrorInfo::SystemError, errTmp);
        return respResult;
    }
}
FileInfo FileUtil::getInfo(QString srcPath)
{
    qDebug() << Q_FUNC_INFO << "srcPath: " << srcPath;

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
    qDebug() << Q_FUNC_INFO << "srcPath: " << srcPath;

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
    qDebug() << Q_FUNC_INFO << "srcPath: " << srcPath;

    QFileInfo fileinfo(srcPath);
    return fileinfo.exists();
}
RespResult FileUtil::rename(QString srcPath, QString newName)
{
    qDebug() << Q_FUNC_INFO << "srcPath: " << srcPath << "newName: " << newName;

    RespResult respResult;

    QFileInfo srcInfo(srcPath);
    if (!srcInfo.exists()) {
        qDebug() << Q_FUNC_INFO << "srcInfo.exists: " << srcInfo.exists();

        respResult.code = ErrorInfo::FileNotExists;
        respResult.flag = false;
        respResult.msg = ErrorInfo::message(ErrorInfo::FileNotExists, srcPath);
        return respResult;
    }
    // 判断文件读写权限
    if (!srcInfo.isReadable() || !srcInfo.isWritable()) {
        qDebug() << Q_FUNC_INFO << "判断文件读写权限: " << srcInfo.isReadable() << srcInfo.isWritable();

        respResult.flag = false;
        respResult.code = ErrorInfo::InvalidFilePermission;
        respResult.msg = ErrorInfo::message(ErrorInfo::InvalidFilePermission, srcPath);
        return respResult;
    }
    QFile srcFile(srcPath);

    respResult.flag = srcFile.rename(newName);

    qDebug() << Q_FUNC_INFO << "respResult.flag: " << respResult.flag;

    return respResult;
}

}

