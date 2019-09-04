#include "devtools.h"
#include <QMutexLocker>

DevTools *DevTools::pDevTools=NULL;
DevTools::DevTools()
{
    qDebug()<<"~DevTools()";
    socketClient=new SocketClient(this->serverIp(),this->serverPort());
    //绑定热更新函数
    connect(socketClient,&SocketClient::hot,this,&DevTools::reload);
}

DevTools *DevTools::getInstance(){
    static QMutex mutex;
    if(pDevTools == NULL){
        QMutexLocker locker(&mutex);
        if(pDevTools == NULL)
            pDevTools = new DevTools();
    }
    return pDevTools;
}

DevTools::~DevTools(){
    qDebug();
    qDebug()<<"~DevTools";
}

QString DevTools::serverIp(){
    return QString("172.16.23.95");
}

int DevTools::serverPort(){
    return 8080;
}


void DevTools::reload(){
    qDebug();
    qDebug()<<"-----reload";
}
