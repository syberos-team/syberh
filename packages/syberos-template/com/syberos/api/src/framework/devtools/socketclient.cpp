#include "socketclient.h"
#include "../common/chalk.h"

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
    socketClient->waitForReadyRead();
    socketClient->disconnectFromHost();
    if (socketClient->state() == QAbstractSocket::UnconnectedState){
        QString str("SocketClient 连接["+url+":"+QString::number(port)+"]失败,请检查网络情况");
        Chalk::green(str,"SocketClient","create()");
    }
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
    //Chalk::green("socket connection","SocketClient","connection()");
}

void SocketClient::data(){

    if(fileSize==-1){
        QByteArray qba= socketClient->readAll(); //读取

        QString ss=QVariant(qba).toString();
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
        QJsonObject subObj =dataContent.take("fileInfo").toObject();
        int uid=dataContent.take("uid").toInt();
        //int hsize=dataContent.take("hsize").toInt();
        qDebug() <<"dataContent id:" << uid;
        fileSize=subObj["size"].toInt();
        fileName=subObj["name"].toString();

        zfilePath=tempPath+"/"+QString::number(uid)+"-"+fileName;
        QFile zfile(zfilePath);
        if(zfile.exists()){
            zfile.remove();
        }
        qDebug() <<"name-----:" << fileName;
        qDebug() <<"size-----:" << fileSize;
        qDebug() <<"zfilePath-----:" << zfilePath;
        QString fok="ok";
        socketClient->write(fok.toUtf8());

        //处理剩余字符串
        if(surString.length()>0||lastIndex==-1){
            QByteArray qba=  surString.toUtf8();
            this->appendFile(QByteArray::fromHex(qba));
        }
    }else{

        // 通过formHex把十六进制的转换为QByteArray
        QByteArray fqba=QByteArray::fromHex(socketClient->readAll());

        this->appendFile(fqba);

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
        QString lpath(fqba);
        qDebug() <<"文件接受完成,文件大小"<<hasSend << "更新时间"<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        // 重置参数,等待下次更新
        this->initParams();
        //this->zxvfWWW(lpath);
    }
}


void SocketClient::zxvfWWW(const QString &path){
    QString webPath=Helper::instance()->getWebRootPath();
    //清空web目录
    //this->ensureWebRoot(webPath);

    QString cmd="tar zxvf "+path+" -C ../www"+webPath;
    qDebug() <<"解压缩命令" << cmd;
    QProcess::execute(cmd);

    qDebug() <<"解压完成" << cmd;
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
    QDir *temp=new QDir(tempPath);
    if(!temp->exists(tempPath)){
        temp->mkpath(tempPath);
        qDebug()<<"临时路径不存在:"<<tempPath <<"重新创建";
    }else{
        qDebug()<<"存在临时路径:"<<tempPath;
    }
    return tempPath;
}


