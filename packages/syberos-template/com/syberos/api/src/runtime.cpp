#include "runtime.h"
#include "cgui_application.h"
#include <QDebug>

int Runtime::typeId = qRegisterMetaType<Runtime *>();
Runtime::Runtime()
{

}
Runtime::~Runtime()
{

}

void Runtime::request(QString callBackID, QString actionName, QVariantMap params)
{
    Q_UNUSED(actionName);
    Q_UNUSED(params);
    QString url = params.value("url").toString();
    qDebug() << "url: " << url << endl;
    openUrl(callBackID.toLong(), url);
}

void Runtime::submit(QString typeID, QString callBackID, QString actionName, QVariant dataRowList, QVariant attachementes)
{
    Q_UNUSED(typeID);
    Q_UNUSED(callBackID);
    Q_UNUSED(actionName);
    Q_UNUSED(dataRowList);
    Q_UNUSED(attachementes);
}

/**
 * @brief openUrl 唤起应用
 * @param callBackID 唤起应用的任务Id
 * @param url 地址
 * @return 成功则无返回。
 *      失败则返回错误码。
 */
void Runtime::openUrl(long callBackID, QString url){
    using namespace SYBEROS;
    qApp->openUrl(url);
    emit success(callBackID, "success");
}
