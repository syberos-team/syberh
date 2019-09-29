#ifndef VIBRATOR_H
#define VIBRATOR_H

#include "framework/nativesdkhandlerbase.h"
#include "cngfmanager.h"
#include "csystemprofilemanager.h"



class Vibrator : public NativeSdkHandlerBase
{
    Q_OBJECT
public:
    Q_INVOKABLE Vibrator();
    ~Vibrator();

    void request(QString callBackID,QString actionName,QVariantMap params);
    void submit(QString typeID,QString callBackID,QString actionName,QVariant dataRowList, QVariant attachementes);

    static int typeId;

private :

    /**
     * @brief changeCameraImagePath 触发震动
     * @param params 参数
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void vibrate(long callBackID, QVariantMap params);

    /**
     * @brief changeCameraImagePath 查询震动设置
     * @param params 参数
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void vibrateInfo(long callBackID, QVariantMap params);

    /**
     * @brief changeCameraImagePath 设置物理按键是否震动。
     * @param params 参数
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void setTouchVibrationSoundEnabled(long callBackID, QVariantMap params);

    /**
     * @brief changeCameraImagePath 设置键盘按键震动是否开启。
     * @param params 参数
     * @return 成功则无返回。
     *      失败则返回错误码。
     */
    void setVibratingEnabled(long callBackID, QVariantMap params);

    CNgfManager *client;
    CSystemProfileManager *profile;

public slots:
    void eventFailed(quint32 eventId);
    void eventCompleted(quint32 eventId);
    void eventPlaying(quint32 eventId);
};

#endif // VIBRATOR_H
