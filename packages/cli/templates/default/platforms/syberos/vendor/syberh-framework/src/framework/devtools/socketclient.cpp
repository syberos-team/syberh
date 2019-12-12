#include "socketclient.h"
#include "../../util/fileutil.h"
#include "../../util/log.h"

static QMap<QString,DevDownload*> downloadTasks;

SocketClient *SocketClient::pSocket=NULL;
SocketClient::SocketClient(const QString &url, const int &port)
{
    log=Log::instance();

    connectCount=0;
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
    socketClient->deleteLater();
    delete log;
}

void SocketClient::create(const QString &url, const int &port){
    Q_UNUSED(url);
    Q_UNUSED(port);
    m_bServerConnected = false;
    socketClient = new QTcpSocket();
    timer= new QTimer(this);
    //绑定常用信号
    connect(socketClient, &QTcpSocket::readyRead,this, &SocketClient::data);
    connect(socketClient, &QTcpSocket::disconnected,this, &SocketClient::disconnected);
    connect(socketClient, &QTcpSocket::connected,this, &SocketClient::connection);
    connect(socketClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(socketError(QAbstractSocket::SocketError)));
    connect(timer, SIGNAL(timeout()), this, SLOT(onProgress()));
    timer->start(3000);
    qDebug()<< "热更新服务 create()成功";
}

void SocketClient::socketError(QAbstractSocket::SocketError error){
    Q_UNUSED(error);
    if(connectCount<3){
        connectCount+=1;
    }else{
        timer->stop();
        qDebug() <<Q_FUNC_INFO <<"stop timer";
    }
    qDebug() <<Q_FUNC_INFO <<"socketError";

}


/**
 * @brief SocketClient::onDisconnected 断开链接slot
 */
void SocketClient::disconnected(){
    m_bServerConnected = false;
    log->red() <<Q_FUNC_INFO  <<"热更新服务断开链接" <<log->end();
    //重连操作
    timer->start(3000);

}

void SocketClient::connection(){
    m_bServerConnected = true;
    log->green() <<Q_FUNC_INFO  <<"热更新服务[客户端]连接成功" <<log->end();
    timer->stop();
}


void SocketClient::data(){
    QByteArray qba= socketClient->readAll(); //读取
    QString ss=QVariant(qba).toString();
    log->green() << qba << log->end();
    int lastIndex=ss.lastIndexOf("}");
    //截取json字符串
    QString jsonString=ss.mid(0,lastIndex+1);
    QJsonDocument obj=QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject dataContent= obj.object();
    QJsonArray fileArray =dataContent.take("files").toArray();
    QString uid=dataContent.take("uid").toString();
    QString serverHost=dataContent.take("server").toString();

    total=fileArray.size();
    QString webroot=Helper::instance()->getDataWebRootPath();
    FileUtil::remove(tempPath+"/www",1);
    for (int npcIndex = 0; npcIndex < fileArray.size(); ++npcIndex) {
        QString filePath = fileArray[npcIndex].toString();

        DevDownload *downloadManager =new DevDownload(this);
        downloadManager->setDownloadId(uid);
        downloadTasks.insert(uid, downloadManager);

        QString url=serverHost+"?path="+filePath;
        int lst=webroot.lastIndexOf("/www");
        QString rpath=webroot.mid(0,lst);
        log->red() <<Q_FUNC_INFO << rpath <<log->end();
        QString downloadPath=rpath+filePath;
         QFile toFile(downloadPath);
        if(toFile.exists()){
             log->verbose()<<Q_FUNC_INFO <<"删除历史文件" <<endl;
            toFile.remove();
        }

        downloadManager->downloadFile(url,downloadPath );
        connect(downloadManager, &DevDownload::signalReplyFinished, this, &SocketClient::onReplyFinished);
    }

}


void SocketClient::onReplyFinished(QString downloadId, QString path, int statusCode, QString errorMessage){
    Q_UNUSED(path);
    Q_UNUSED(statusCode);
    Q_UNUSED(errorMessage);
    log->red() << Q_FUNC_INFO << downloadId << log->end();
    downloadTotal+=1;
    if(total==downloadTotal){
        updateWebRoot();
    }
    if(downloadTasks.contains(downloadId)){
        DevDownload *task = downloadTasks.value(downloadId);
        task->deleteLater();
        task = NULL;
        downloadTasks.remove(downloadId);
    }
}

void SocketClient::updateWebRoot(){
    this->initParams();
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


