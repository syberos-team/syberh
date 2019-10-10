#include "package.h"
#include "cgui_application.h"
#include <QDebug>

int Package::typeId = qRegisterMetaType<Package *>();
Package::Package()
{

}
Package::~Package()
{

}

void Package::request(QString callBackID, QString actionName, QVariantMap params)
{
    Q_UNUSED(callBackID);
    Q_UNUSED(actionName);
    Q_UNUSED(params);
    qDebug() << "params: " << params << endl;

    long callBackIDLong = callBackID.toLong();
    if (actionName == "openUrl") {

        QString scheme = params.value("scheme").toString();
        QString path = params.value("path").toString();
        QVariantMap pathParams = params.value("params").toMap();

        openUrl(callBackIDLong, scheme, path, pathParams);

    }else if(actionName == "openByUrl"){

        QString url = params.value("url").toString();
        qDebug() << "url:" << url << endl;

        openByUrl(url);

    }else if(actionName == "openDocument"){

        QString sopId = params.value("sopid").toString();
        QString uiappId = params.value("uiappid").toString();
        QString action = params.value("action").toString();
        QString path = params.value("path").toString();
        QVariantMap pathParams = params.value("params").toMap();

        openDocument(callBackIDLong, sopId, uiappId, action, path, pathParams);

    }else if(actionName == "openByDocument"){
        QString action = params.value("action").toString();
        QString mimetype = params.value("mimetype").toString();
        QString filePath = params.value("filePath").toString();
        openByDocument(action, mimetype, filePath);
    }
}

void Package::submit(QString typeID, QString callBackID, QString actionName, QVariant dataRowList, QVariant attachementes)
{
    Q_UNUSED(typeID);
    Q_UNUSED(callBackID);
    Q_UNUSED(actionName);
    Q_UNUSED(dataRowList);
    Q_UNUSED(attachementes);
}

void Package::openUrl(long callBackID, QString scheme, QString path, QVariantMap params){
    using namespace SYBEROS;

    if(scheme.isEmpty()){
        emit failed(callBackID, ErrorInfo::InvalidParameter, "scheme参数不能为空");
        return;
    }

    QStringList schemeList = scheme.split(":");
    if(schemeList.size() != 2){
        emit failed(callBackID, ErrorInfo::InvalidParameter, "scheme参数不合法");
        return;
    }

    if(schemeList.value(1).indexOf("openPage") >= 0){
        openPage(callBackID, scheme, path, params);
    }else{
        qApp->openUrl(scheme + path);
        emit success(callBackID, "success");
    }
}

void Package::openPage(long callBackID, QString scheme, QString path, QVariantMap params){
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

void Package::openByUrl(QString url){

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

    QVariantMap result;
    if(path.isEmpty()){
        path = "index.html";
    }
    result.insert("path", path);
    result.insert("params", query);

    emit subscribe("onShow", result);
}

void Package::openDocument(long callBackID, QString sopId, QString uiappId,
                  QString action, QString path, QVariantMap params){

    using namespace SYBEROS;

    if(sopId.isEmpty()){
        emit failed(callBackID, ErrorInfo::InvalidParameter, "sopid is empty");
        return;
    }

    if(uiappId.isEmpty()){
        emit failed(callBackID, ErrorInfo::InvalidParameter, "uiappid is empty");
        return;
    }

    QString mimeType = params.value("mimeType").toString();
    if(mimeType.isEmpty()){
        mimeType = "*";
    }
    QString filePath = params.value("filePath").toString();

    if(action != "openPage"){
        qApp->runDocument(sopId, uiappId, action, mimeType, filePath);
        emit success(callBackID, "success");
        return;
    }

    params.insert("action", action);
    QVariantMap pathParam;
    QVariantMap::Iterator it = params.begin();
    while(it != params.end())
    {
        if(it.key() == "filePath" || it.key() == "mimeType"){
            it++;
            continue;
        }
        pathParam.insert(it.key(), it.value().toString());
        it++;
    }
    path = convertParamToUrl(path, pathParam);
    action = path;
    qDebug() << "openDocument request: " << action << endl;

    qApp->runDocument(sopId, uiappId, action, mimeType, filePath);
    emit success(callBackID, "success");
}

void Package::openByDocument(QString action, QString mimetype, QString filePath){

    QString path = action;
    if(path.isEmpty()){
        path = "index.html";
    }

    QVariantMap params;
    params = parseUrlToParam(path, params);
    params.insert("mimeType", mimetype);
    params.insert("filePath", filePath);

    QJsonObject query;
    QVariantMap::Iterator it = params.begin();
    while(it != params.end())
    {
        query.insert(it.key(), it.value().toString());
        it++;
    }

    path = convertParamToUrl(path, params);
    QVariantMap result;
    result.insert("path", path);
    result.insert("params", query);

    qDebug() << "final subscribe result: " << result << endl;

    emit subscribe("onShow", result);
}

QString Package::convertParamToUrl(QString url, QVariantMap paramMap){

    QMap<QString, QVariant>::Iterator it = paramMap.begin();

    QString paramStr;
    int i = 0;
    while(it != paramMap.end())
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

    if(url.indexOf("?") > -1){
        url = url + "&" + paramStr;
    }else{
        url = url + "?" + paramStr;
    }
    return url;
}

QVariantMap Package::parseUrlToParam(QString url, QVariantMap paramMap){

    if(url.isEmpty()){
        return paramMap;
    }

    QStringList list = url.split("?");
    if(list.size() < 2){
        return paramMap;
    }

    QStringList paramList = list.value(1).split("&");

    for(int i = 0; i < paramList.size(); i++){
        QString item = paramList.value(i);
        QStringList itemList = item.split("=");
        if(itemList.size() != 2){
            continue;
        }
        paramMap.insert(itemList.value(0), itemList.value(1));
    }
    return paramMap;

}


