#include "url.h"
#include "cgui_application.h"
#include <QDebug>

int Url::typeId = qRegisterMetaType<Url *>();
Url::Url()
{

}
Url::~Url()
{

}

void Url::request(QString callBackID, QString actionName, QVariantMap params)
{
    Q_UNUSED(callBackID);
    Q_UNUSED(actionName);
    Q_UNUSED(params);
    qDebug() << "params: " << params << endl;

    if (actionName == "openUrl") {

        QString scheme = params.value("scheme").toString();
        QString path = params.value("path").toString();
        QVariantMap pathParams = params.value("params").toMap();

        qDebug() << "scheme: " << scheme << endl;
        qDebug() << "path: " << path << endl;
        qDebug() << "pathParams: " << pathParams << endl;
        openUrl(callBackID.toLong(), scheme, path, pathParams);

    }else if(actionName == "openByUrl"){
        QString url = params.value("url").toString();
        qDebug() << "url:" << url << endl;
        openByUrl(url);
    }
}

void Url::submit(QString typeID, QString callBackID, QString actionName, QVariant dataRowList, QVariant attachementes)
{
    Q_UNUSED(typeID);
    Q_UNUSED(callBackID);
    Q_UNUSED(actionName);
    Q_UNUSED(dataRowList);
    Q_UNUSED(attachementes);
}

void Url::openUrl(long callBackID, QString scheme, QString path, QVariantMap params){
    using namespace SYBEROS;

    if(scheme.isEmpty()){
        emit failed(callBackID, 500, "Illegal parameters");
        return;
    }

    QStringList schemeList = scheme.split(":");
    if(schemeList.size() != 2){
        emit failed(callBackID, 500, "Illegal parameters");
        return;
    }

    if(schemeList.value(1).indexOf("openPage") >= 0){
        openPage(callBackID, scheme, path, params);
    }else{
        qApp->openUrl(scheme + path);
        emit success(callBackID, "success");
    }
}

void Url::openPage(long callBackID, QString scheme, QString path, QVariantMap params){
    using namespace SYBEROS;

    //遍历params拼接成key=value&key=value格式
    QString paramStr = "";
    QMap<QString, QVariant>::Iterator it = params.begin();
    int i = 0;
    while(it != params.end())
    {
        if(i > 0){
            paramStr.append("&");
        }
        paramStr.append(it.key());
        paramStr.append("=");
        paramStr.append(it.value().toString());
        it++;
        i++;
    }

    //如果路径包含多个?，提示路径错误
    QStringList list = path.split("?");
    if(list.size() != 2){
        emit failed(callBackID, 500, "Illegal Path");
        return;
    }
    if(list.size() == 1){
        path = path + "?" + paramStr;
    }else{
        path = path + "&" + paramStr;
    }
    path = scheme + "/" + path;
    //唤起APP
    qDebug() << "唤起APP的路径: " << path << endl;
    qApp->openUrl(path);
    emit success(callBackID, "success");
}

void Url::openByUrl(QString url){

    //url格式为: scheme://openPage/index.html?key=value&key=value
    QStringList list = url.split("://");
    if(list.size() != 2){
        return;
    }

    QString methodAndPathStr = list.value(1);
    QStringList methodAndPath = methodAndPathStr.split("/");
    if(methodAndPath.size() < 1){
        return;
    }

    //判断方法是否为openPage
    QString method = methodAndPath.value(0);
    if(method.toLower() != "openpage"){
        return;
    }

    QString path = "";
    for(int i = 1; i < methodAndPath.size(); i++){
        if(i > 1){
            path.append("/");
        }
        path.append(methodAndPath.value(i));
    }

    //将参数转换为QJsonObject
    QJsonObject query;
    QStringList pathList = path.split("?");
    if(pathList.size() == 2){
        QStringList list = pathList.value(1).split("&");
        for(int i = 0; i < list.size(); i++){
            QString item = list.value(i);
            QStringList itemList = item.split("=");
            if(itemList.size() != 2){
                continue;
            }
            query.insert(itemList.value(0), itemList.value(1));
        }
    }

    qDebug() << "openByUrl path: " << path << endl;
    qDebug() << "openByUrl query: " << query << endl;

    QVariantMap params;
    if(path.isEmpty()){
        path = "index.html";
    }
    params.insert("path", path);
    params.insert("params", query);

    emit subscribe("onShow", params);
}


