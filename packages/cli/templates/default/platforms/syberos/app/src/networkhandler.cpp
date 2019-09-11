#include "networkhandler.h"
#include <QDebug>

int NetWorkHandler::typeId = qRegisterMetaType<NetWorkHandler *>();

NetWorkHandler::NetWorkHandler()
{

}
NetWorkHandler::~NetWorkHandler()
{

}
void NetWorkHandler::request(QString callBackID, QString actionName, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "NetWorkHandler callbackID is" << callBackID << "actionName is" << actionName << "params is" << params;
}
