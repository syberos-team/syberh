#include "camerahandler.h"
#include "download.h"
#include "qtcamera.h"
#include <QDebug>
int CameraHandler::typeId = qRegisterMetaType<CameraHandler *>();
CameraHandler::CameraHandler(){
    connect(QtCamera::getInstance(),SIGNAL(savedImage(int,QString)),this,SLOT(saveImage(int,QString)));


}
CameraHandler::~CameraHandler(){

}
void CameraHandler::request(QString callBackID,QString actionName,QVariantMap params){
    Q_UNUSED(callBackID)
    Q_UNUSED(params)
   qDebug()<<Q_FUNC_INFO ;
    if(actionName == "start"){
        QtCamera::getInstance()->startCameraAndSetZoom();
    }else if(actionName == "stop"){
        QtCamera::getInstance()->stopCamera();
    }


}
QObject * CameraHandler::getUiSource(QString actionName){
    Q_UNUSED(actionName)
    return QtCamera::getInstance();
}
void CameraHandler::saveImage(int id, QString filePath){

    emit success(id,filePath);
}
