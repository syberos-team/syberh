#ifndef RECORD_H
#define RECORD_H

#include <QObject>
#include <QtPlugin>
#include <QtMultimedia>
#include <QMediaPlayer>
#include <QMediaContent>

#include "iplugin/iplugin.h"
#include "record_global.h"
#include "historydata.h"
#include "audioinput.h"

class RECORDSHARED_EXPORT Record: public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.syberos.syberh.SyberhPlugin" FILE "plugin.json")

public:
    Record();
    ~Record();

    void invoke(QString callbackID, QString actionName, QVariantMap params);

    /**
     * @brief list 录音列表
     * @param params 参数
     * @return 成功则返回录音文件列表
     *         失败则返回错误码
     */
    void list(QString callbackID, QVariantMap params);

    /**
     * @brief delRecorder 删除录音
     * @param params 参数
     * @return 成功则无返回
     *         失败则返回错误码
     */
    void remove(QString callbackID,QVariantMap params);

    /**
     * @brief start 开始录音
     * @param params 参数
     * @return 成功则返回录音文件路径
     *         失败则返回错误码
     */
    void start(QString callbackID, QVariantMap params);

    /**
     * @brief pause 暂停录音
     * @param params 参数
     * @return 成功则无返回
     *         失败则返回错误码
     */
    void pause(QString callbackID,QVariantMap params);

    /**
     * @brief resume 继续录音
     * @param params 参数
     * @return 成功则无返回
     *         失败则返回错误码
     */
    void resume(QString callbackID,QVariantMap params);

    /**
     * @brief stop 结束录音
     * @param params 参数
     * @return 成功则无返回
     *         失败则返回错误码
     */
    void stop(QString callbackID,QVariantMap params);

private :
    HistoryData *historydata;
    AudioInput *audioInput = nullptr;

    QString currPath;
};

#endif // RECORD_H
