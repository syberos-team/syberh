#include "testhandler.h"
#include "download.h"
#include <QDebug>
int TestHandler::typeId = qRegisterMetaType<TestHandler *>();
TestHandler::TestHandler(){
    connect(Download::instance(),SIGNAL(downloadFailed(long,QString,long)),this,SLOT(downLoadFailed(long,QString,long)));

}
TestHandler::~TestHandler(){

}
void TestHandler::request(QString callBackID,QString actionName,QVariantMap params){
    /// 根据实际请求，判断网络是否连接
//    if(!netWorkConnected()){
//        emit failed(callBackID.toLong(),NETWORK_ERROR,ErrorInfo::m_errorCode.value(NETWORK_ERROR));
//    }
    if(actionName == "start"){
        downLoadStart(callBackID.toLong(),params);
    }


}
void TestHandler::submit(){

}
void TestHandler::downLoadFailed(long downloadID, QString result, long errorCode){
    qDebug()<<Q_FUNC_INFO << result << errorCode;
    emit failed(downloadID,errorCode,result);
}
void TestHandler::downLoadSucess(long downloadID, QString result){
    emit sucess(downloadID,QVariant(result));
}

void TestHandler::downLoadStart(long callBackID, QVariantMap params){
    QString url = params.value("url").toString();
    QString name = params.value("name").toString();
    qDebug()<<Q_FUNC_INFO <<"callbackID is"<<callBackID <<"url is"<< url << "name is"<<name;
    Download::instance()->start(callBackID,url,name);
}
