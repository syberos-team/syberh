#include "socketclient.h"
#include "../common/chalk.h"

//#include "../include/quazip/JlCompress.h"

SocketClient::SocketClient(const QString &url, const int &port)
{
    helper=Helper::instance();
    this->create(url,port);
    this->getOrCreateTempPath();

    qDebug() <<Q_FUNC_INFO << "SocketClient init success" <<endl;
}

SocketClient::~SocketClient(){

}

void SocketClient::create(const QString &url, const int &port){

    socketClient = new QTcpSocket();
    socketClient -> abort();
    socketClient->connectToHost(url, port);


    if(socketClient->waitForReadyRead(1000)){
        QByteArray s = socketClient->readAll();
        QString ss = QVariant(s).toString();
    }

    //    QString str(socketClient->state());
    //     Chalk::green(str,"SocketClient","create()");
    //     socketClient->disconnectFromHost();
    //         if (socketClient->state() == QAbstractSocket::UnconnectedState ||
    //             socketClient->waitForDisconnected(1000))
    //             str="Disconnected";
    //             Chalk::green(str,"SocketClient","create()");
    //socketClient->disconnectFromHost();
    //     QString str(socketClient->state());
    //       Chalk::green(str,"SocketClient","create()");
    //    if (socketClient->state() == QAbstractSocket::UnconnectedState){
    //        QString str("SocketClient 连接["+url+":"+QString::number(port)+"]失败,请检查网络情况");
    //        Chalk::green(str,"SocketClient","create()");
    //    }
    //绑定常用信号
    connect(socketClient, &QTcpSocket::readyRead,this, &SocketClient::data);
    connect(socketClient, &QTcpSocket::disconnected,this, &SocketClient::close);
    connect(socketClient, &QTcpSocket::connected,this, &SocketClient::connection);
    connect(socketClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(socketError(QAbstractSocket::SocketError)));
    qDebug()<< "SocketClient create() 成功";

}

void SocketClient::socketError(QAbstractSocket::SocketError error){
    qDebug() <<"socketError";
    //Chalk::green("str","SocketClient","create()");
    //Chalk::green("socket socketError","SocketClient","socketError()");
}

void SocketClient::close(){
    qDebug() <<"close";
    //Chalk::green("socket close","SocketClient","close()");
}

void SocketClient::connection(){
    QString str("connection");
    Chalk::green(str,"SocketClient","create()");
    qDebug() <<"connection";
    //Chalk::green("socket connection","SocketClient","connection()");
}

void onData(QString &data){
    Chalk::green(data,"SocketClient","create()");
}

void SocketClient::data(){
    QByteArray qba= socketClient->readAll(); //读取
    QString ss=QVariant(qba).toString();

    qDebug()<<"-----------------ss:"<<ss <<endl;

    //onData(ss);
    //    if(fileSize==-1){

    int lastIndex=ss.lastIndexOf("}");
    qDebug()<<"lastIndex:"<<lastIndex;
    qDebug();
    //截取json字符串
    QString jsonString=ss.mid(0,lastIndex+1);
    //qDebug()<<"jsonString:"<<jsonString;
    //剩余字符
    QString surString=ss.mid(lastIndex+1);
    //qDebug()<<"surString:"<<surString;
    qDebug();

    QJsonDocument obj=QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject dataContent= obj.object();
    QJsonArray fileArray =dataContent.take("files").toArray();
    QString uid=dataContent.take("uid").toString();
    QString serverHost=dataContent.take("server").toString();

    //int hsize=dataContent.take("hsize").toInt();
    qDebug() <<"files:" << fileArray.size();
    total=fileArray.size();

    //QJsonArray files=subObj["files"].toArray();
    for (int npcIndex = 0; npcIndex < fileArray.size(); ++npcIndex) {
        QString filePath = fileArray[npcIndex].toString();
        Chalk::green(filePath);
        DownloadManager *downloadManager=new DownloadManager(this);
        downloadManager->setDownloadId(uid);
        QString url=serverHost+"?path="+filePath;
        qDebug() <<"url:" << url<<endl;
        downloadManager->downloadFile(url, tempPath+filePath);
        connect(downloadManager, &DownloadManager::signalReplyFinished, this, &SocketClient::onReplyFinished);
    }

}


void SocketClient::onReplyFinished(QString downloadId, QString path, int statusCode, QString errorMessage){
    downloadTotal+=1;
    if(this->total==this->downloadTotal){
        qDebug() << Q_FUNC_INFO << "download success " <<this->downloadTotal << endl;
    }

}

//保存字符到文件
void SocketClient::appendFile(const QByteArray &fqba){

    hasSend=hasSend+fqba.length();
    // qDebug() <<"hasSend-----:"<<hasSend ;
    //压缩的文件
    QFile zfile(zfilePath);

    zfile.open(QIODevice::WriteOnly|QIODevice::Append);
    zfile.write(fqba);
    //qDebug()<< hasSend<< (int)((hasSend / fileSize) * 100) << "%";
    //qDebug() <<"hasSend-----:"<<hasSend << "fileSize:"<<fileSize;
    //接受完成
    if(hasSend >= fileSize){
        zfile.close();
        //临时目录
        //QString lpath(fqba);
        qDebug() <<"文件接受完成,文件大小"<<hasSend << "更新时间"<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        //处理压缩文件
        qDebug() <<"压缩文件地址" << zfilePath <<endl;
        this->zxvfWWW(zfilePath);
        // 重置参数,等待下次更新
        this->initParams();
    }
}


void SocketClient::zxvfWWW(QString path){

    //Chalk::green("压缩文件地址"+path);

    qDebug() <<"压缩文件地址" << path <<endl;

    QString webPath=Helper::instance()->getWebRootPath();

    //清空web目录
    bool ensure =Helper::instance()->emptyDir(webPath);
    qDebug() << "清空web目录" <<webPath << ensure;
    QDir dir(webPath);
    dir.mkpath(dir.absolutePath());

    //JlCompress::extractDir(path, webPath);

    //QString cmd="/bin/tar zxvf "+path;
    //QString cmd="cp "+path+" "+webPath;
    //qDebug() <<"解压缩命令" << cmd;
    //QProcess p(0);
    //p.start(cmd);
    //p.waitForFinished();
    //proc->start("tar zxvf "+path+" -C "+webPath);
    //proc->waitForFinished();
    //int code= p.exitCode();
    //qDebug()<<QString::fromLocal8Bit(p.readAllStandardError());
    //qDebug() <<"code:" << code <<endl;
    //命令执行有误，获取错误信息
    //    QString errTmp = proc.readAllStandardError();
    //    qDebug() <<"errTmp:" << errTmp <<endl;
    //    //命令执行结果
    //    QString optTmp = proc->readAllStandardOutput();

    //qDebug() <<"optTmp:" << optTmp <<endl;
    //QProcess::execute(cmd);
    qDebug() <<"解压完成" <<endl;
}

void SocketClient::ensureWebRoot(const QString &path){

    bool ensure=Helper::instance()->emptyDir(path);
    qDebug() << "清空web目录" <<path<<ensure;
}


void SocketClient::initParams(){
    fileSize=-1;
    hasSend=0;
    uid=-1;
    fileName="";
    zfilePath="";
    this->total=0;
    this->downloadTotal=0;
}



///**
// * @brief SocketClient::onDisconnected 断开链接slot
// */
//void SocketClient::disconnected(){
//    qDebug();
//    qDebug() <<"SocketClient 断开链接:";
//    //重连操作
//}

QString SocketClient::getOrCreateTempPath(){
    tempPath=Helper::instance()->getDataRootPath()+"/"+this->TEMP_PATH_NAME;
    //tempPath="/tmp/www";
    QDir *temp=new QDir(tempPath);
    if(!temp->exists(tempPath)){
        temp->mkpath(tempPath);
        qDebug()<<"临时路径不存在:"<<tempPath <<"重新创建";
    }else{
        qDebug()<<"存在临时路径:"<<tempPath;
    }
    return tempPath;
}


