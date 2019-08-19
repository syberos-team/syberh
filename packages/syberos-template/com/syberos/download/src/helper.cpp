#include "helper.h"
#include "httpclient.h"
#include <cenvironment.h>
#include <QApplication>
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QTextCodec>

Helper::Helper(QObject *parent) : QObject(parent) {
    env = new CEnvironment(this);
    appInfo = new CAppInfo();
}


bool Helper::exists(QString filePath){
    QFile file(filePath);
    return file.exists();
}


QString Helper::getWebRootPath(){
    QDir dir(qApp->applicationDirPath());
    dir.cdUp();
    dir.cd("www");
    return dir.absolutePath();
}

QString Helper::getDataRootPath(){
    return env->dataPath();
}

QString Helper::getExternStorageRootPath(){
    return env->externalStoragePath();
}

QString Helper::getInnerStorageRootPath(){
    return env->internalStoragePath();
}

QString Helper::sopid(){
    return qApp->property("sopid").toString();
}
