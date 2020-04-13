#ifndef ERRORINFO_H
#define ERRORINFO_H
#include <QString>
#include<QObject>
#include <QMap>
class ErrorInfo :public QObject{
    Q_OBJECT
public:
    //错误码
    enum ErrorCode {
        //不合法的媒体文件类型
        IllegalMediaTypeError = 4004,
        //不合法的文件类型
        IllegalFileType = 4005,
        //不合法的文件大小
        IllegalFileSize = 4006,
        //不合法的媒体文件 id
        IllegalMediaId = 4007,
        //不合法的图片文件大小
        IllegalImageSize = 4009,
        //不合法的语音文件大小
        IllegalVoiceSize  = 4010,
        //不合法的视频文件大小
        IllegalVideoSize = 4011,
        //不合法的缩略图文件大小
        IllegalThumbnailSize = 4012,
        //类型错误
        InvalidType = 4019,
        //不支持的图片格式
        UnsupportedImage = 4020,
        //不合法的请求格式
        IllegalRequestFormat = 4038,
        //不合法的 URL 长度
        IllegalUrlSize = 4039,
        //文件不存在
        FileNotExists = 4040,
        //无效的url
        InvalidURLError = 4048,
        //上传文件缺失
        UploadFileMissing = 6001,
        //上传素材的文件类型不合法
        IllegalUploadFileType = 6002,
        //上传素材的文件尺寸不合法
        IllegalUploadFileSize = 6003,
        //上传失败
        UploadFileFailed = 6004,
        //取消失败
        CannelFailed = 6005,

        // 存储空间不足
        NotEnoughSpace = 7000,


        //文件无操作权限
        InvalidFilePermission = 9000,
        //参数错误
        InvalidParameter = 9001,
        //系统错误
        SystemError = 9002,
        //网络错误
        NetworkError = 9003,
        //权限错误(os)
        InvalidPermission = 9004,
        //无效的调用
        InvalidCall = 9005,
        //数据库错误
        databaseError = 9006,
        //未知的错误
        UnknowError = 9999
    };
    /**
     * @brief init 初始化错误码
     */
    static void init();

    static QString message(ErrorInfo::ErrorCode code);

    static QString message(ErrorInfo::ErrorCode code, const QString &msg);

    ~ErrorInfo();
private:
    explicit ErrorInfo(QObject *parent = 0);
    ErrorInfo(const ErrorInfo &) Q_DECL_EQ_DELETE;
    ErrorInfo& operator=(ErrorInfo errorInfo) Q_DECL_EQ_DELETE;
};

#endif // ERRORINFO_H
