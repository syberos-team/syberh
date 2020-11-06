#include "devtools.h"
#include <QMutexLocker>
#include "../../util/fileutil.h"
#include "../common/projectconfig.h"

using namespace NativeSdk;

int DevTools::typeId = qRegisterMetaType<DevTools*>();
DevTools *DevTools::pDevTools=NULL;
DevTools::DevTools()
{
    qDebug() << Q_FUNC_INFO << endl;
    
    bool useHot = ProjectConfig::instance()->isUseHot();
    qDebug()<< Q_FUNC_INFO << "use hot:" << useHot << endl;

    if(useHot){
        if(socketClient==NULL){
             qDebug() << Q_FUNC_INFO << "hot模式";
            //拷贝www到data目录下
            this->copyWWW();
            socketClient=new SocketClient(serverIp(),serverPort());
            //绑定热更新函数
            connect(socketClient,&SocketClient::update,this,&DevTools::reload);
        }
    }
    qDebug() << Q_FUNC_INFO << "------DevTools" << endl;
}

void DevTools::request(QString callBackID, QString actionName, QVariantMap params){
    Q_UNUSED(callBackID);
    Q_UNUSED(actionName);
    Q_UNUSED(params);
    qDebug()<<Q_FUNC_INFO<<endl;
}

DevTools *DevTools::getInstance(){
    static QMutex mutex;

    if(pDevTools == NULL){
        QMutexLocker locker(&mutex);
        if(pDevTools == NULL){
            qDebug()<<Q_FUNC_INFO<<"getInstance";
            pDevTools = new DevTools();
        }


    }
    return pDevTools;
}

DevTools::~DevTools(){
    qDebug()<<Q_FUNC_INFO;
}

QString DevTools::serverIp(){
    QString serverIp=ProjectConfig::instance()->getDevServerIP();
    if(serverIp.isEmpty()){

        qDebug()<<Q_FUNC_INFO<<"serverIP不存在,设置默认值"<<serverIp <<endl;

    }else{
        qDebug()<<Q_FUNC_INFO<<"serverIp"<<serverIp <<endl;
    }

    return serverIp;
}

int DevTools::serverPort(){

    int port=4399;
    QString sport=ProjectConfig::instance()->getDevServerPort();
    if(!sport.isEmpty()){
        port=sport.toInt();
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
    FileUtil::chmodr(dataPath);
    FileUtil::remove(dataPath,1);
    RespResult resp = FileUtil::copy(webPath,dataPath.replace("/www", ""));
    if (resp.flag){
        FileUtil::chmodr(dataPath);
        return true;
    } else {
        qDebug()<<Q_FUNC_INFO<<"copyWWW failed " + resp.msg <<endl;
        return false;
    }
}
