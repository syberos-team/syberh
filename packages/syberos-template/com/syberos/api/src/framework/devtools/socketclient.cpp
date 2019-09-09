#include "socketclient.h"
#include "../../util/chalk.h"
#include "../../util/fileutil.h";
//#include "../include/quazip/JlCompress.h"

SocketClient::SocketClient(const QString &url, const int &port)
{
    helper=Helper::instance();

    if(!socketClient){
        this->create(url,port);
    }

    this->getOrCreateTempPath();

    qDebug() <<Q_FUNC_INFO << "SocketClient init success" <<endl;
}

SocketClient::~SocketClient(){

}

void SocketClient::create(const QString &url, const int &port){
    qDebug() <<Q_FUNC_INFO <<url << port<<endl;

    socketClient = new QTcpSocket();
    socketClient -> abort();
    socketClient->connectToHost(url, port);


    if(socketClient->waitForReadyRead(1000)){
        QByteArray s = socketClient->readAll();
        QString ss = QVariant(s).toString();
    }
    //绑定常用信号
    connect(socketClient, &QTcpSocket::readyRead,this, &SocketClient::data);
    connect(socketClient, &QTcpSocket::disconnected,this, &SocketClient::disconnected);
    connect(socketClient, &QTcpSocket::connected,this, &SocketClient::connection);
    connect(socketClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(socketError(QAbstractSocket::SocketError)));
    qDebug()<< "SocketClient create() 成功";

}

void SocketClient::socketError(QAbstractSocket::SocketError error){
    qDebug() <<"socketError";

}


/**
 * @brief SocketClient::onDisconnected 断开链接slot
 */
void SocketClient::disconnected(){

    qDebug() <<"SocketClient 断开链接:";
    //重连操作
}

void SocketClient::connection(){
    QString str("connection");
    Chalk::green(str,"SocketClient","create()");
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
    FileUtil::remove(tempPath+"/www",1);
    //QJsonArray files=subObj["files"].toArray();
    for (int npcIndex = 0; npcIndex < fileArray.size(); ++npcIndex) {
        QString filePath = fileArray[npcIndex].toString();
        Chalk::green(filePath);
        DownloadManager *downloadManager=new DownloadManager(this);
        downloadManager->setDownloadId(uid);
        QString url=serverHost+"?path="+filePath;

        QString downloadPath=tempPath+"/"+filePath;
        //创建目录
        int li=downloadPath.lastIndexOf("/");
        QString dirPath= downloadPath.mid(0,li+1);
        QDir dir(dirPath);
        if(!dir.exists()){
            dir.mkpath(dir.absolutePath());
        }

        downloadManager->downloadFile(url,downloadPath );
        connect(downloadManager, &DownloadManager::signalReplyFinished, this, &SocketClient::onReplyFinished);
    }

}


void SocketClient::onReplyFinished(QString downloadId, QString path, int statusCode, QString errorMessage){
    downloadTotal+=1;
    if(this->total==this->downloadTotal){
        qDebug() << Q_FUNC_INFO << "download success " <<this->downloadTotal << endl;
        this->updateWebRoot();
    }

}




void SocketClient::updateWebRoot(){
    this->initParams();
    QString dataRoot= Helper::instance()->getDataWebRootPath();
    QString tmpwww=tempPath+"/www";

    FileUtil::remove(dataRoot,1);
    FileUtil::copy(tmpwww,dataRoot);

    emit update();

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





QString SocketClient::getOrCreateTempPath(){
    tempPath=Helper::instance()->getDataRootPath()+"/"+this->TEMP_PATH_NAME;
    QDir *temp=new QDir(tempPath);
    if(!temp->exists(tempPath)){
        temp->mkpath(tempPath);
        qDebug()<< Q_FUNC_INFO<<"临时路径不存在:"<<tempPath <<"重新创建";
    }else{
        qDebug()<< Q_FUNC_INFO<<"存在临时路径:"<<tempPath;
    }
    return tempPath;
}


