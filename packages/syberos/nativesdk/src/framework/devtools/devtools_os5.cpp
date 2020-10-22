#include "devtools.h"
#include <QMutexLocker>
#include "../../util/fileutil.h"

using namespace NativeSdk;

int DevTools::typeId = qRegisterMetaType<DevTools*>();
DevTools *DevTools::pDevTools=NULL;

DevTools::DevTools()
{
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
            qDebug() << Q_FUNC_INFO << "getInstance";
            pDevTools = new DevTools();
        }


    }
    return pDevTools;
}

DevTools::~DevTools(){
    if(pDevTools != NULL){
        delete pDevTools;
        pDevTools = NULL;
    }
}

QString DevTools::serverIp(){
    return QString();
}

int DevTools::serverPort(){
    return -1;
}

void DevTools::reload(){
}

bool DevTools::copyWWW(){
    return false;
}
