#include "devtools.h"
#include <QMutexLocker>
#include "../../util/fileutil.h"
int DevTools::typeId = qRegisterMetaType<DevTools*>();
DevTools *DevTools::pDevTools=NULL;
DevTools::DevTools()
{
    qDebug()<<"~DevTools()";
     extendConfig=ExtendedConfig::instance();
    //拷贝www到data目录下
    this->copyWWW();
    socketClient=new SocketClient(this->serverIp(),this->serverPort());
    //绑定热更新函数
    connect(socketClient,&SocketClient::update,this,&DevTools::reload);
}

void DevTools::request(QString callBackID, QString actionName, QVariantMap params){
    qDebug()<<Q_FUNC_INFO<<"----------------------request"<<callBackID <<actionName <<endl;
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
    QString ip("127.0.0.1");
    QString serverIp=extendConfig->get("serverIP").toString();
    if(!serverIp.isEmpty()){
       ip=serverIp;
    }
    qDebug()<<Q_FUNC_INFO<<"serverIP"<<ip <<endl;
    return ip;
}

int DevTools::serverPort(){

    int port=8080;
    int sport=extendConfig->get("serverIP").toInt();
    if(sport>0){
        port=sport;
    }
    return 8080;
}


void DevTools::reload(){
    emit subscribe("DevToolsReload",true);
}

/**
 * @brief DevTools::copyWWW
 * @return
 */
bool DevTools::copyWWW(){
    //获取data目录
    QString dataPath=Helper::instance()->getDataWebRootPath();
    //获取默认目录
    QString webPath=Helper::instance()->getDefaultWebRootPath();

    FileUtil::copy(webPath,dataPath);

}
