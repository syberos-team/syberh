#ifndef AUDIO_H
#define AUDIO_H

#include <QObject>
#include <QtPlugin>
#include <QtMultimedia>
#include <QMediaPlayer>
#include <QMediaContent>

#include "iplugin/iplugin.h"
#include "audio_global.h"

class AUDIOSHARED_EXPORT Audio : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.syberos.syberh.SyberhPlugin" FILE "plugin.json")

public:
    Audio();
    ~Audio();

    void invoke(QString callbackID, QString actionName, QVariantMap params);

    /**
     * @brief start 播放音频
     * @param params 参数
     * @return 成功则返回
     *         失败则返回错误码
     */
    void start(QString callbackID, QVariantMap params);

    /**
     * @brief pause 暂停音频
     * @param params 参数
     * @return 成功则无返回
     *         失败则返回错误码
     */
    void pause(QString callbackID, QVariantMap params);

    /**
     * @brief resume 继续音频
     * @param params 参数
     * @return 成功则无返回
     *         失败则返回错误码
     */
    void resume(QString callbackID, QVariantMap params);

    /**
     * @brief stop 结束播放音频
     * @param params 参数
     * @return 成功则无返回
     *         失败则返回错误码
     */
    void stop(QString callbackID, QVariantMap params);

private :
    QMediaPlayer *player;
};

#endif // AUDIO_H
