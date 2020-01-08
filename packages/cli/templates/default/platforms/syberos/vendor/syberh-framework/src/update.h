#ifndef UPDATE_H
#define UPDATE_H
#include "framework/nativesdkhandlerbase.h"

#include <QObject>
#include <QNetworkReply>

class SyberH5HelpperPrivate;
class Update : public NativeSdkHandlerBase
{
    Q_OBJECT

public:
    Q_INVOKABLE Update();
    ~Update();

    void request(QString callBackID, QString actionName, QVariantMap params);
    void submit(QString typeID, QString callBackID, QString actionName,QVariant dataRowList, QVariant attachementes);

    static int typeId;

private:

    /**
     * @brief check jiancha shi fou geng xin
     * @param callBackID 任务Id
     * @param params 参数
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void check(long callBackID,QVariantMap params);

    SyberH5HelpperPrivate *d;
    QString MY_APP_ID;
    QString NEW_VERSION_HEAD;
    QString CHECK_NEWVERSION;
    long checkCallBackID;

private slots:
    void handleNetworkAccessReply(QNetworkReply *reply);
};

#endif // UPDATE_H
