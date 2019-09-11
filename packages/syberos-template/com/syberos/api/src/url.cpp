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
        QString method = params.value("method").toString();
        QString path = params.value("path").toString();
        QVariantMap pathParams = params.value("params").toMap();

        qDebug() << "scheme: " << scheme << endl;
        qDebug() << "method: " << method << endl;
        qDebug() << "path: " << path << endl;
        qDebug() << "pathParams: " << pathParams << endl;
        openUrl(callBackID.toLong(), scheme, method, path, pathParams);

    }else if(actionName == "openByUrl"){
        QString path = params.value("path").toString();
        QString query = params.value("query").toString();
        qDebug() << "path:"<<path;
        qDebug() << "query:"<<query;
        openByUrl(path, query);
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

void Url::openUrl(long callBackID, QString scheme, QString method, QString path, QVariantMap params){

    if(scheme == "" || method == "" || path == ""){
        emit failed(callBackID, 500, "Illegal parameters");
        return;
    }

    if(method == "openPage"){
        openPage(callBackID, scheme, path, params);
    }
    emit success(callBackID, "success");
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
    path = scheme + ":" + path;
    //唤起APP
    qDebug() << "唤起APP的路径: " << path << endl;
    qApp->openUrl(path);
}

void Url::openByUrl(QString path, QString query){
    qDebug() << "openByUrl path: " << path << endl;
    qDebug() << "openByUrl query: " << query << endl;

    path = path +"?"+ query;

    qDebug() << "openByUrl final path: " << path << endl;

    QVariantMap params;
    params.insert("path", path);

    QJsonObject paramJson;

    QStringList list = query.split("&");
    for(int i = 0; i < list.size(); i++){
        QString item = list.value(i);

        QStringList itemList = item.split("=");
        if(itemList.size() != 2){
            continue;
        }

        paramJson.insert(itemList.value(0), itemList.value(1));
    }
    params.insert("params", paramJson);

    emit subscribe("openUrl", params);
}


