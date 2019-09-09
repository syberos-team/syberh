#ifndef RUNTIME_H
#define RUNTIME_H

#include "framework/nativesdkhandlerbase.h"
class Runtime : public NativeSdkHandlerBase
{
    Q_OBJECT
public:
    Q_INVOKABLE Runtime();
    ~Runtime();

    void request(QString callBackID, QString actionName, QVariantMap params);
    void submit(QString typeID, QString callBackID, QString actionName,QVariant dataRowList, QVariant attachementes);

    static int typeId;

private:

    /**
     * @brief openUrl 唤起应用
     * @param callBackID 唤起应用的任务Id
     * @param url 地址
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void openUrl(long callBackID, QString url);
};

#endif // RUNTIME_H
