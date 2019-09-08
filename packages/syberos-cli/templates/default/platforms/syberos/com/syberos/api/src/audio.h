#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>
#include <QtMultimedia>
#include <QMediaPlayer>
#include <QAudioRecorder>

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
     * @brief startAudioRecorder 开始录音
     * @param params 参数
     * @return 成功则返回录音文件路径
     *         失败则返回错误码
     */
    void startAudioRecorder(long callBackID, QVariantMap params);

    /**
     * @brief stopAudioRecorder 结束录音
     * @param params 参数
     * @return 成功则无返回
     *         失败则返回错误码
     */
    void stopAudioRecorder(QVariantMap params);

    /**
     * @brief startAudioPlay 播放录音
     * @param params 参数
     * @return 成功则无返回
     *         失败则返回错误码
     */
    void startAudioPlay(QVariantMap params);

    /**
     * @brief stopAudioPlay 结束播放录音
     * @param params 参数
     * @return 成功则无返回
     *         失败则返回错误码
     */
    void stopAudioPlay(QVariantMap params);

private :
    QMediaPlayer *player;
    QAudioRecorder *recoder;
    QMediaPlaylist *playlist;

    static int typeId;
};

#endif // SYSTEMINFO_H
