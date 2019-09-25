#ifndef IMAGE_H
#define IMAGE_H

#include "framework/nativesdkhandlerbase.h"
class Image : public NativeSdkHandlerBase
{
    Q_OBJECT
public:
    Q_INVOKABLE Image();
    ~Image();

    void request(QString callBackID, QString actionName, QVariantMap params);

    void submit(QString typeID, QString callBackID, QString actionName,QVariant dataRowList, QVariant attachementes);

    static int typeId;

private:

    /**
     * @brief openUrl 唤起应用,打开页面
     * @param callBackID 唤起应用的任务Id
     * @param filePath 文件路径
     * @return 成功则发送成功信号。
     *      失败则发送失败信号。
     */
    void saveImageToPhotosAlbum(long callBackID, QString filePath);


    /**
     * @brief getImageInfo 获取图片的详细
     * @param callBackID 任务Id
     * @return 成功则发送成功信号。
     *      失败则发送失败信号。
     */
    void getImageInfo(long callBackID, QVariantMap params);
};

#endif // IMAGE_H
