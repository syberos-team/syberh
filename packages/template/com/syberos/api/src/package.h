#ifndef PACKAGE_H
#define PACKAGE_H

#include "framework/nativesdkhandlerbase.h"
#include "qurlquery.h"
class Package : public NativeSdkHandlerBase
{
    Q_OBJECT
public:
    Q_INVOKABLE Package();
    ~Package();

    void request(QString callBackID, QString actionName, QVariantMap params);

    void submit(QString typeID, QString callBackID, QString actionName,QVariant dataRowList, QVariant attachementes);

    static int typeId;

    /**
     * @brief openByUrl 被应用唤起
     * @param url 路径
     * @return 成功则发送订阅信号
     */
    void openByUrl(QString url);

    /**
     * @brief openByDocument 被应用唤起
     * @param action 要执行的操作
     * @param mimetype 文件内容类型
     * @param filePath 文件路径
     * @return 成功则发送订阅信号
     */
    void openByDocument(QString action, QString mimetype, QString filePath);

private:

    /**
     * @brief openUrl 唤起应用,打开页面
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

    /**
     * @brief openDocument 唤起应用,打开页面,处理文档
     * @param callBackID 唤起应用的任务Id
     * @param action 应用可以执行的操作，值：openPage
     * @param path 跳转的页面路径
     * @param params 参数
     * @return 成功则发送成功信号。
     *      成功则发送成功信号。
     */
    void openDocument(long callBackID, QString sopId, QString uiappId,
                      QString action, QString path, QVariantMap params);

    /**
     * @brief convertParamToUrl 将参数拼接到url中
     * @param url  地址
     * @param params 参数
     * @return
     */
    QString convertParamToUrl(QString url, QVariantMap paramMap);

    /**
     * @brief parseUrlToParam 解析url问号后的参数到params里
     * @param url 地址
     * @param params 参数
     * @return 返回map
     */
    QVariantMap parseUrlToParam(QString url, QVariantMap paramMap);

};

#endif // PACKAGE_H
