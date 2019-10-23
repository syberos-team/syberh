#include "network.h"
#include <QDebug>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QNetworkReply>
#include "framework/common/errorinfo.h"
#include "util/validator.h"

int Network::typeId = qRegisterMetaType<Network *>();

Network::Network()
{
  manager = new QNetworkAccessManager(this);
  connect(manager, SIGNAL(finished(QNetworkReply *)),
          this, SLOT(finished(QNetworkReply *)));
}
Network::~Network()
{
  delete manager;
}
void Network::request(QString callBackID, QString actionName, QVariantMap params)
{

  // 检查网络
  if (!netWorkConnected())
  {
    emit failed(callBackID.toLong(), ErrorInfo::NetworkError, ErrorInfo::message(ErrorInfo::NetworkError, "请检查网络状态"));
    return;
  }

  qDebug() << Q_FUNC_INFO << "NetWork callbackID is" << callBackID << "actionName is" << actionName << "params is" << params << endl;

  QString url = params.value("url").toString();
  QString method = params.value("method").toString();
  if (method == "")
  {
    qDebug() << Q_FUNC_INFO << "params type is null, set default values: get callbackID is " << callBackID << endl;
    method = "get";
  }

  //检查url
  if(!Validator::isHttpUrl(url)){
      qDebug() << "url parameter is not starts with http or https: " << params << endl;
      emit failed(callBackID.toLong(), ErrorInfo::InvalidParameter, ErrorInfo::message(ErrorInfo::InvalidParameter, "URL无效"));
      return;
  }


  QString dataType = params.value("dataType").toString();
  if (dataType == "")
  {
    dataType = "json";
  }

  if (dataType.toLower() != "json" && dataType.toLower() != "text")
  {
    emit failed(callBackID.toLong(), ErrorInfo::InvalidParameter, ErrorInfo::message(ErrorInfo::InvalidParameter, "dataType"));
    return;
  }

  QNetworkRequest request;

  QString urlAddr = url.toLower();
  if (urlAddr.startsWith("https"))
  {
    QSslConfiguration config;
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::UnknownProtocol);
    request.setSslConfiguration(config);
  }

  QVariantMap headers = params.value("header").toMap();

  qDebug() << Q_FUNC_INFO << "header is " << headers << endl;

  QVariantMap::Iterator headerIt = headers.begin();
  while (headerIt != headers.end())
  {
    request.setRawHeader(headerIt.key().toUtf8(), headerIt.value().toString().toUtf8());
    headerIt++;
  }
  if (!headers.contains("Content-Type"))
  {
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
  }

  request.setUrl(url);

  QNetworkReply *reply;

  if ("get" == method.toLower())
  {
    reply = manager->get(request);
  }
  else if ("post" == method.toLower())
  {
    QVariantMap data = params.value("data").toMap();
    QVariantMap::Iterator it = data.begin();
    QString content;
    while (it != data.end())
    {
      content.append(it.key()).append("=").append(it.value().toString());
      it++;
      if (it != data.end())
      {
        content.append("&");
      }
    }
    reply = manager->post(request, content.toUtf8());
  }
  else if ("put" == method.toLower())
  {
    QVariantMap data = params.value("data").toMap();
    QVariantMap::Iterator it = data.begin();
    QString content;
    while (it != data.end())
    {
      content.append(it.key()).append("=").append(it.value().toString());
      it++;
      if (it != data.end())
      {
        content.append("&");
      }
    }
    reply = manager->put(request, content.toUtf8());
  }
  else if ("delete" == method.toLower())
  {
    reply = manager->deleteResource(request);
  }
  else
  {
      emit failed(callBackID.toLong(), ErrorInfo::InvalidParameter, ErrorInfo::message(ErrorInfo::InvalidParameter, "type"));
    return;
  }

  TaskInfo *taskInfo = new TaskInfo();
  taskInfo->dataType = dataType;
  taskInfo->reply = reply;

  tasks[callBackID] = taskInfo;
}

void Network::finished(QNetworkReply *reply)
{
  qDebug() << Q_FUNC_INFO << endl;

  QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

  qDebug() << Q_FUNC_INFO << " statusCode: " << statusCode.toString() << " error: " << reply->error() << endl;

  QJsonObject headers;

  QList<QPair<QByteArray, QByteArray>> ls = reply->rawHeaderPairs();
  for (qint64 i = 0; i < ls.size(); i++)
  {
    QByteArray key = ls.at(i).first;
    QByteArray val = ls.at(i).second;
    headers.insert(QString(key), QString(val));
  }

  QString result = QString(reply->readAll());

  qDebug() << Q_FUNC_INFO << " result: " << result << " url:" << reply->url().url() << endl;

  QString callBackId;
  QString datatype;

  QMap<QString, TaskInfo *>::Iterator it = tasks.begin();
  while (it != tasks.end())
  {
    TaskInfo *taskInfo = it.value();
    if (taskInfo->reply == reply)
    {
      callBackId = it.key();
      datatype = taskInfo->dataType;
      tasks.remove(it.key());
      delete taskInfo;
      taskInfo = NULL;
      break;
    }
    it++;
  }

  if (QNetworkReply::NoError == reply->error())
  {
    QJsonObject json;
    json.insert("statusCode", statusCode.toString());
    json.insert("header", headers);
    if (datatype.toLower() == "json")
    {
      json.insert("data", QJsonDocument::fromJson(result.toLocal8Bit().data()).object());
      emit success(callBackId.toLong(), json);
    }
    else
    {
      json.insert("data", result);
      emit success(callBackId.toLong(), json);
    }
  }
  else
  {
    qDebug() << Q_FUNC_INFO << " result error " << endl;
    emit failed(callBackId.toLong(), ErrorInfo::NetworkError, ErrorInfo::message(ErrorInfo::NetworkError, reply->errorString()));
  }

  reply->deleteLater();
}
