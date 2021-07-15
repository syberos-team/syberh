#ifndef ERRORINFO_H
#define ERRORINFO_H
#include <QString>
#include <QObject>
#include <QMap>

#include "../../nativesdk_global.h"

namespace NativeSdk {

class NATIVESDK_EXPORT ErrorInfo :public QObject{
    Q_OBJECT
public:
    //错误码
    enum ErrorCode {
        //插件错误
        PluginError = 1008,
        //模块不存在
        UndefinedModule = 1009,
        //不合法的媒体文件类型
        IllegalMediaTypeError = 4004,
        //不合法的文件类型
        IllegalFileType = 4005,
        //文件不存在
        FileNotExists = 4040,
        //无效的url
        InvalidURLError = 4048,
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

}
#endif // ERRORINFO_H
