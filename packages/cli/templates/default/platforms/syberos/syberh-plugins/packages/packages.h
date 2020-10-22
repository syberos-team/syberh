#ifndef PACKAGES_H
#define PACKAGES_H

#include <QObject>
#include <QtPlugin>

#include "iplugin/iplugin.h"
#include "packages_global.h"

class PACKAGESSHARED_EXPORT Packages: public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.syberos.syberh.SyberhPlugin" FILE "plugin.json")

public:
    Packages();

    void invoke(QString callbackID, QString actionName, QVariantMap params);

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

private :

    /**
     * @brief openUrl 唤起应用,打开页面
     * @param callBackID 唤起应用的任务Id
     * @param scheme 协议
     * @param path 路径
     * @param params 参数
     * @return 成功则发送成功信号。
     *      成功则发送成功信号。
     */
    void openUrl(QString callbackID, QString scheme, QString path, QVariantMap params);

    /**
     * @brief openPage 根据路径打开页面
     * @param callBackID 唤起应用的任务Id
     * @param scheme 协议
     * @param path 路径
     * @param params 参数
     * @return 成功则发送成功信号。
     *      成功则发送成功信号。
     */
    void openPage(QString callbackID, QString scheme, QString path, QVariantMap params);

    /**
     * @brief openDocument 唤起应用,打开页面,处理文档
     * @param callBackID 唤起应用的任务Id
     * @param action 应用可以执行的操作，值：openPage
     * @param path 跳转的页面路径
     * @param params 参数
     * @return 成功则发送成功信号。
     *      成功则发送成功信号。
     */
    void openDocument(QString callbackID, QString sopId, QString uiappId,
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

#endif // PACKAGES_H
