#include "devtools.h"
#include <QMutexLocker>
#include "../../util/fileutil.h"
int DevTools::typeId = qRegisterMetaType<DevTools*>();
DevTools *DevTools::pDevTools=NULL;
DevTools::DevTools()
{
    qDebug()<<Q_FUNC_INFO <<endl;
    extendConfig= ExtendedConfig::instance();
    QVariant debug = extendConfig->get("debug");
    if(debug.toBool()){
        //拷贝www到data目录下
        this->copyWWW();
        socketClient=new SocketClient(serverIp(),serverPort());
        //绑定热更新函数
        connect(socketClient,&SocketClient::update,this,&DevTools::reload);
    }

}

void DevTools::request(QString callBackID, QString actionName, QVariantMap params){
    qDebug()<<Q_FUNC_INFO<<endl;
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
    qDebug()<<Q_FUNC_INFO;
}

QString DevTools::serverIp(){
    extendConfig->get("serverIp").toString();
    QString serverIp=extendConfig->get("serverIp").toString();
    if(serverIp.isEmpty()){
        qDebug()<<Q_FUNC_INFO<<"serverIP不存在"<<serverIp <<endl;
    }else{
        qDebug()<<Q_FUNC_INFO<<"serverIp"<<serverIp <<endl;
    }

    return serverIp;
}

int DevTools::serverPort(){

    int port=8080;
    int sport=extendConfig->get("port").toInt();
    if(sport>0){
        port=sport;
    }
    qDebug()<<Q_FUNC_INFO<<"server port"<<port<<endl;
    return port;
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
    Helper::instance()->emptyDir(dataPath);
    FileUtil::remove(dataPath,1);
    FileUtil::copy(webPath,dataPath);

}
