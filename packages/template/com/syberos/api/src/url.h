#ifndef RUNTIME_H
#define RUNTIME_H

#include "framework/nativesdkhandlerbase.h"
#include "qurlquery.h"
class Url : public NativeSdkHandlerBase
{
    Q_OBJECT
public:
    Q_INVOKABLE Url();
    ~Url();

    void request(QString callBackID, QString actionName, QVariantMap params);

    void submit(QString typeID, QString callBackID, QString actionName,QVariant dataRowList, QVariant attachementes);

    static int typeId;

    /**
     * @brief openByUrl 通过url被应用唤起
     * @param url 路径
     * @return 成功则发送订阅信号
     */
    void openByUrl(QString url);

private:

    /**
     * @brief openUrl 唤起应用
     * @param callBackID 唤起应用的任务Id
     * @param scheme 协议
     * @param path 路径
     * @param params 参数
     * @return 成功则发送成功信号。
     *      成功则发送成功信号。
     */
    void openUrl(long callBackID, QString scheme, QString path, QVariantMap params);

    /**
     * @brief openPage 根据路径打开页面
     * @param callBackID 唤起应用的任务Id
     * @param scheme 协议
     * @param path 路径
     * @param params 参数
     * @return 成功则发送成功信号。
     *      成功则发送成功信号。
     */
    void openPage(long callBackID, QString scheme, QString path, QVariantMap params);

};

#endif // RUNTIME_H
