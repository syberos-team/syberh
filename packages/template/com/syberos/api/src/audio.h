#ifndef AUDIO_H
#define AUDIO_H

#include <QObject>
#include <QtMultimedia>
#include <QMediaPlayer>
#include <QMediaContent>

#include "historydata.h"
#include "framework/nativesdkhandlerbase.h"

class Audio : public NativeSdkHandlerBase
{
    Q_OBJECT
public:
    Q_INVOKABLE Audio();
    ~Audio();

    void request(QString callBackID,QString actionName,QVariantMap params);
    void submit(QString typeID,QString callBackID,QString actionName,QVariant dataRowList, QVariant attachementes);

    /**
     * @brief startPlay 播放音频
     * @param params 参数
     * @return 成功则无返回
     *         失败则返回错误码
     */
    void startPlay(QVariantMap params);

    /**
     * @brief pausePlay 暂停音频
     * @param params 参数
     * @return 成功则无返回
     *         失败则返回错误码
     */
    void pausePlay(QVariantMap params);

    /**
     * @brief continuePlay 继续音频
     * @param params 参数
     * @return 成功则无返回
     *         失败则返回错误码
     */
    void continuePlay(QVariantMap params);

    /**
     * @brief stopPlay 结束播放音频
     * @param params 参数
     * @return 成功则无返回
     *         失败则返回错误码
     */
    void stopPlay(QVariantMap params);

private :
    QMediaPlayer *player;

    static int typeId;
    QString currPath;
};

#endif
