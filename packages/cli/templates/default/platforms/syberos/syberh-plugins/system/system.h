#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>
#include <QtPlugin>

#include "iplugin/iplugin.h"
#include "system_global.h"

class SYSTEMSHARED_EXPORT System : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.syberos.syberh.SyberhPlugin" FILE "plugin.json")

public:
    System();

    void invoke(QString callbackID, QString actionName, QVariantMap params);

private :
    // signal manager
    ExtensionSystem::SignalManager *s;

    /**
     * @brief aboutPhone 获取手机信息
     * @param callBackID 获取手机信息的任务Id
     * @param params 参数
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void  aboutPhone(QString callbackID,QVariantMap params);

     /**
     * @brief setDate 设置系统时间
     * @param callBackID 任务Id
     * @param params 参数
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void  setDate(QString callbackID,QVariantMap params);

     /**
     * @brief setVirtualPanel 设置虚拟按键显示隐藏
     * @param callBackID 任务Id
     * @param params 参数
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void  setVirtualPanel(QString callbackID,QVariantMap params);

    /**
     * @brief getResolution 获取手机分辨率
     * @param callBackID 获取手机分辨率的任务Id
     * @param params 参数
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void  getResolution(QString callbackID,QVariantMap params);

   /**
    * @brief getCoreVersion 获取内核版本号
    * @param callBackID 获取内核版本号的任务Id
    * @param params 参数
    * @return 成功则无返回。
    *      失败则返回错误码。
    */
   void  getCoreVersion(QString callbackID,QVariantMap params);

   /**
    * @brief getSysVersionID 获取系统版本号
    * @param callBackID 获取内核版本号的任务Id
    * @param params 参数
    * @return 成功则无返回。
    *      失败则返回错误码。
    */
   void  getSysVersionID(QString callbackID,QVariantMap params);

};

#endif // SYSTEM_H
