#include "socketclient.h"
#include "../../util/chalk.h"
#include "../../util/fileutil.h"
SocketClient *SocketClient::pSocket=NULL;
SocketClient::SocketClient(const QString &url, const int &port)
{
    helper=Helper::instance();
    bool debug=ExtendedConfig::instance()->get("debug").toBool();
    purl=url;
    pport=port;
    total=0;
    downloadTotal=0;
    uid=-1;
    fileSize=-1;
    hasSend=0;
    TEMP_PATH_NAME="tmp";

    if(debug){
        qDebug() <<Q_FUNC_INFO << "SocketClient dubug:true" <<endl;
       create(url,port);
        getOrCreateTempPath();
    }

    qDebug() <<Q_FUNC_INFO << "SocketClient init success" <<endl;
}

SocketClient *SocketClient::getInstance(const QString &url, const int &port){
    static QMutex mutex;
    if(pSocket == NULL){
        QMutexLocker locker(&mutex);
        if(pSocket == NULL)
            pSocket = new SocketClient(url,port);
    }
    return pSocket;
}


SocketClient::~SocketClient(){

}

void SocketClient::create(const QString &url, const int &port){
    qDebug() <<Q_FUNC_INFO <<url << port<<endl;
    m_bServerConnected = false;
    socketClient = new QTcpSocket();
    //socketClient -> abort();
    //    socketClient->connectToHost(url, port);


    //    if(socketClient->waitForReadyRead(1000)){
    //        QByteArray s = socketClient->readAll();
    //        QString ss = QVariant(s).toString();
    //        qDebug() <<Q_FUNC_INFO <<ss << port<<endl;
    //    }
    QTimer *timer = new QTimer(this);
    //绑定常用信号
    connect(socketClient, &QTcpSocket::readyRead,this, &SocketClient::data);
    connect(socketClient, &QTcpSocket::disconnected,this, &SocketClient::disconnected);
    connect(socketClient, &QTcpSocket::connected,this, &SocketClient::connection);
    connect(socketClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(socketError(QAbstractSocket::SocketError)));
    connect(timer, SIGNAL(timeout()), this, SLOT(onProgress()));
    //timer.setInterval(2000);
    timer->start(30000);
    qDebug()<< "SocketClient create() 成功";

}

void SocketClient::socketError(QAbstractSocket::SocketError error){
    Q_UNUSED(error);
    qDebug() <<Q_FUNC_INFO <<"socketError";

}


/**
 * @brief SocketClient::onDisconnected 断开链接slot
 */
void SocketClient::disconnected(){
    m_bServerConnected = false;
    qDebug() <<Q_FUNC_INFO<<"SocketClient 断开链接:";
    //重连操作
}

void SocketClient::connection(){
    QString str("Socket连接成功");
    m_bServerConnected = true;
    Chalk::green(str,"SocketClient","connection()");
}


void SocketClient::data(){
    QByteArray qba= socketClient->readAll(); //读取
    QString ss=QVariant(qba).toString();
    int lastIndex=ss.lastIndexOf("}");

    //截取json字符串
    QString jsonString=ss.mid(0,lastIndex+1);
    //剩余字符
    QString surString=ss.mid(lastIndex+1);
    QJsonDocument obj=QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject dataContent= obj.object();
    QJsonArray fileArray =dataContent.take("files").toArray();
    QString uid=dataContent.take("uid").toString();
    QString serverHost=dataContent.take("server").toString();

    total=fileArray.size();
    FileUtil::remove(tempPath+"/www",1);
    for (int npcIndex = 0; npcIndex < fileArray.size(); ++npcIndex) {
        QString filePath = fileArray[npcIndex].toString();
        DownloadManager *downloadManager=new DownloadManager(this);
        downloadManager->setDownloadId(uid);
        QString url=serverHost+"?path="+filePath;
        QString webroot=Helper::instance()->getDataWebRootPath();
        int lst=webroot.lastIndexOf("/www");
        QString rpath=webroot.mid(0,lst+1);
        QString downloadPath=rpath+"/"+filePath;
        //创建目录
        int li=downloadPath.lastIndexOf("/");
        QString dirPath= downloadPath.mid(0,li+1);
        QFile dfile(downloadPath);
        if(dfile.exists()){
            dfile.remove();
        }
        QDir dir(dirPath);
        if(!dir.exists()){
            dir.mkpath(dir.absolutePath());
        }

        downloadManager->downloadFile(url,downloadPath );
        connect(downloadManager, &DownloadManager::signalReplyFinished, this, &SocketClient::onReplyFinished);
    }

}


void SocketClient::onReplyFinished(QString downloadId, QString path, int statusCode, QString errorMessage){
    Q_UNUSED(downloadId);
    Q_UNUSED(path);
    Q_UNUSED(statusCode);
    Q_UNUSED(errorMessage);
    downloadTotal+=1;
    if(total==downloadTotal){
        updateWebRoot();
    }
}

void SocketClient::updateWebRoot(){
    this->initParams();
    QString dataRoot= Helper::instance()->getDataWebRootPath();
    QString tmpwww=tempPath+"/www/";
    //FileUtil::remove(dataRoot,1);
    //FileUtil::copy(tmpwww,dataRoot);
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



void SocketClient::onProgress()
{

    if(!m_bServerConnected)
    {
        qDebug()<< Q_FUNC_INFO<<"------------:"<< m_bServerConnected<<endl;
        socketClient->abort();
        socketClient->connectToHost(purl, pport);
        socketClient->waitForConnected(1000);
    }
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


