#include "cgui_application.h"
#include <cenvironment.h>
#include <QDir>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <csystempackagemanager.h>
#include "update.h"
#include "framework/common/extendedconfig.h"
#include "framework/common/errorinfo.h"

// 必须用这个命令空间下的qApp才可以
using namespace SYBEROS;
using namespace NativeSdk;

class SyberH5HelpperPrivate
{
public:
    SyberH5HelpperPrivate() {}
    ~SyberH5HelpperPrivate(){
        if(env){
            env->deleteLater();
        }
        if(networkAccessManager){
            networkAccessManager->deleteLater();
        }
        if(m_pSystemPackageManager){
            m_pSystemPackageManager->deleteLater();
        }
    }
    CEnvironment *env;
    QNetworkAccessManager *networkAccessManager;
    CSystemPackageManager *m_pSystemPackageManager;
};

Update::Update():d(new SyberH5HelpperPrivate())
{
    d->env = new CEnvironment(this);
    d->networkAccessManager = new QNetworkAccessManager(this);
    connect(d->networkAccessManager,SIGNAL(finished(QNetworkReply *)),this,SLOT(handleNetworkAccessReply(QNetworkReply*)));
    d->m_pSystemPackageManager = new CSystemPackageManager(this);

    NEW_VERSION_HEAD = ExtendedConfig::instance()->get("storeBaseUrl").toString();
    // 获取sop包的详细信息接口（每个客户的域名不一样，api是一样的）
    CHECK_NEWVERSION = "/api/v1/app";
    MY_APP_ID = ExtendedConfig::instance()->get("sopid").toString();
    qDebug() << Q_FUNC_INFO  << "check" << NEW_VERSION_HEAD << CHECK_NEWVERSION << MY_APP_ID << endl;
}

Update::~Update() {
    delete d;
}


void Update::invoke(QString callbackID, QString actionName, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "  callbackID:" << callbackID << "actionName:" << actionName << "params:" << params;

    if (actionName == "check") {
        check(callbackID, params);
    } else if (actionName == "toStore") {
        // 跳转到企业商店对应的app处
        qApp->openUrl("store://mainpage?operation=" + MY_APP_ID);
        signalManager()->success(callbackID.toLong(), "");
    }
}

void Update::check(QString callbackID,QVariantMap params) // 开始检测是否有新版本可用
{
    qDebug() << Q_FUNC_INFO << params;
    checkCallBackID = callbackID.toLong();
    QString url = QString("%1%2/%3").arg(NEW_VERSION_HEAD).arg(CHECK_NEWVERSION).arg(MY_APP_ID);
    qDebug() << Q_FUNC_INFO << url;
    QNetworkRequest networkRequest;
    networkRequest.setUrl(QUrl(url));
    qDebug()<<"url:"<<url;
    d->networkAccessManager->get(networkRequest);
}

void Update::handleNetworkAccessReply(QNetworkReply *reply)
{
    qDebug()<<Q_FUNC_INFO<<endl;
    QByteArray byteData = reply->readAll();

    qDebug() << Q_FUNC_INFO << byteData;
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(byteData.constData(), &error);
    if(error.error == QJsonParseError::NoError) {
        if(document.isObject()) {
            QJsonObject object = document.object();
            int vercode =  object["vercode"].toInt();
            qDebug() << "web vercode = " << vercode;
            QString m_sUpdateNote = object["desc"].toString();
            qDebug() << "web UpdateNote = " << m_sUpdateNote;

            QSharedPointer<CPackageInfo> info = d->m_pSystemPackageManager->packageInfo(MY_APP_ID);

            if(info.isNull()) {
                qWarning() << "get packageinfo by sopid error";
                signalManager()->failed(checkCallBackID, ErrorInfo::SystemError, "无法获取当前应用的详细信息");
                return;
            }

            int oldCode = info->versionCode();
            qDebug() << "oldCode = " << oldCode;

            // jieguo
            QJsonObject resultObj;
            resultObj.insert("oldCode", oldCode);
            resultObj.insert("vercode", vercode);

            if(vercode > oldCode) {
                resultObj.insert("isNeedUpdate", true);
            } else {
                resultObj.insert("isNeedUpdate", false);
            }

            qDebug() << Q_FUNC_INFO << "resultObj:" << resultObj << endl;
            signalManager()->success(checkCallBackID, QVariant(resultObj));
        }
    } else {
        signalManager()->failed(checkCallBackID, ErrorInfo::SystemError, "系统出错，未返回应用的详细信息，请检查url是否正确");
    }

    reply->deleteLater();
}
