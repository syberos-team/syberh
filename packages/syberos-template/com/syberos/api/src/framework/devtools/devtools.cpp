#include "devtools.h"
#include <QMutexLocker>

int DevTools::typeId = qRegisterMetaType<DevTools*>();
DevTools *DevTools::pDevTools=NULL;
DevTools::DevTools()
{
    qDebug()<<"~DevTools()";
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
    QString ip("172.16.25.52");
    qDebug()<<Q_FUNC_INFO<<"serverIP"<<ip <<endl;
    return ip;
}

int DevTools::serverPort(){
    return 8080;
}


void DevTools::reload(){
    qDebug();
    qDebug()<<"-----reload";

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
    bool res=this->copyDirectoryFiles(webPath,dataPath,true);
    return res;
}

//拷贝文件：
bool DevTools::copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist)
{
    toDir.replace("\\","/");
    if (sourceDir == toDir){
        return true;
    }
    if (!QFile::exists(sourceDir)){
        return false;
    }
    QDir *createfile     = new QDir;
    bool exist = createfile->exists(toDir);
    if (exist){
        if(coverFileIfExist){
            createfile->remove(toDir);
        }
    }//end if

    if(!QFile::copy(sourceDir, toDir))
    {
        return false;
    }
    return true;
}

//拷贝文件夹：
bool DevTools::copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist){
    QDir sourceDir(fromDir);
    QDir targetDir(toDir);
    if(!targetDir.exists()){    /**< 如果目标目录不存在，则进行创建 */
        if(!targetDir.mkdir(targetDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList){
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        if(fileInfo.isDir()){    /**< 当为目录时，递归的进行copy */
            if(!copyDirectoryFiles(fileInfo.filePath(),
                                   targetDir.filePath(fileInfo.fileName()),
                                   coverFileIfExist))
                return false;
        }
        else{            /**< 当允许覆盖操作时，将旧文件进行删除操作 */
            if(coverFileIfExist && targetDir.exists(fileInfo.fileName())){
                targetDir.remove(fileInfo.fileName());
            }

            /// 进行文件copy
            if(!QFile::copy(fileInfo.filePath(),
                            targetDir.filePath(fileInfo.fileName()))){
                return false;
            }
        }
    }
    return true;
}
