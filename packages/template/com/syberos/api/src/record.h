#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>
#include <QtMultimedia>
#include <QMediaPlayer>
#include <QAudioRecorder>
#include <QMediaContent>

#include "historydata.h"
#include "framework/nativesdkhandlerbase.h"

class Record : public NativeSdkHandlerBase
{
    Q_OBJECT
public:
    Q_INVOKABLE Record();
    ~Record();

    void request(QString callBackID,QString actionName,QVariantMap params);
    void submit(QString typeID,QString callBackID,QString actionName,QVariant dataRowList, QVariant attachementes);

    /**
     * @brief list 录音列表
     * @param params 参数
     * @return 成功则返回录音文件列表
     *         失败则返回错误码
     */
    void list(long callBackID, QVariantMap params);

    /**
     * @brief delRecorder 删除录音
     * @param params 参数
     * @return 成功则无返回
     *         失败则返回错误码
     */
    void remove(long callBackID,QVariantMap params);

    /**
     * @brief start 开始录音
     * @param params 参数
     * @return 成功则返回录音文件路径
     *         失败则返回错误码
     */
    void start(long callBackID, QVariantMap params);

    /**
     * @brief pause 暂停录音
     * @param params 参数
     * @return 成功则无返回
     *         失败则返回错误码
     */
    void pause(long callBackID,QVariantMap params);

    /**
     * @brief resume 继续录音
     * @param params 参数
     * @return 成功则无返回
     *         失败则返回错误码
     */
    void resume(long callBackID,QVariantMap params);

    /**
     * @brief stop 结束录音
     * @param params 参数
     * @return 成功则无返回
     *         失败则返回错误码
     */
    void stop(long callBackID,QVariantMap params);

private :
    QAudioRecorder *recoder;
    HistoryData *historydata;

    static int typeId;
    QString currPath;
};

#endif // SYSTEMINFO_H
