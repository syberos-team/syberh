#ifndef NATIVESDKHANDLERBASE_H
#define NATIVESDKHANDLERBASE_H

#include <QObject>
#include <QVariantMap>

#include "../nativesdk_global.h"

namespace NativeSdk {
/**
 * @brief The NativeSdkHandlerBase class
 * 业务处理模块基类
 */
class NATIVESDK_EXPORT NativeSdkHandlerBase : public QObject{
    Q_OBJECT
public:
    NativeSdkHandlerBase();
    virtual ~NativeSdkHandlerBase();
    /**
     * @brief request 上层应用发送的请求
     * @param callbackID 请求的唯一标志,用于应用判断是否为自己发送的请求
     * @param actionName 请求名称，用于区分是哪个请求
     * @params 请求传递的参数
     */
    virtual void request(const QString &callbackID, const QString &actionName, const QVariantMap &params);

signals:
    void success(long responseID, const QVariant &result);
    void failed(long responseID, long errorCode, const QString &errorMsg);
    void progress(long responseID, const int totalLength, const int progress, const int status);
    void subscribe(const QString &handleName, const QVariant &result);
};
}
#endif // NATIVESDKHANDLERBASE_H
