#ifndef NATIVESDKMANAGER_H
#define NATIVESDKMANAGER_H

#include <QObject>
#include <QMutex>
#include <QMap>
#include <QVariant>

#include "../nativesdk_global.h"

namespace NativeSdk {

namespace Internal {class NativeSdkManagerPrivate;}
/**
 * @brief The NativeSdkManager class
 * 单例模式，提供上层应用接口
 */
class NATIVESDK_EXPORT NativeSdkManager :public  QObject{
    Q_OBJECT
public:
    ~NativeSdkManager();
    static NativeSdkManager * getInstance();

    /**
     * @brief request 上层应用请求接口
     * @param typeID 业务类的typeID,通过反射进行业务类实例化
     * @param callbackID 请求的唯一标志,用于应用判断是否为自己发送的请求
     * @param actionName 请求名称，用于区分是哪个请求
     * @params 请求传递的参数
     */
    Q_INVOKABLE void request(QString typeID,QString callbackID,QString actionName,QVariantMap params);
    /**
      *@brief 唤起应用方法
      *@url 请求信息
      */
    Q_INVOKABLE void openByUrl(const QUrl& url);

    /**
      *@brief 唤起应用方法
      *@action 要执行的操作
      *@mimetype 文件类型信息
      *@filePath 文件路径
      */
    Q_INVOKABLE void openByDocument(const QString& action, const QString& mimetype, const QString& filePath);
signals:
    /**
      *@brief signal 请求成功信号
      *@responseID 请求传入的唯一标志，用于应用判断是否为自己发送的请求
      *@result 请求结果
      */
    void success(long responseID,QVariant result);
    /**
      *@brief signal 请求失败信号
      *@responseID 请求传入的唯一标志，用于应用判断是否为自己发送的请求
      *@errorCode 错误码
      *@errorMsg 错误信息
      */
    void failed(long responseID,long errorCode,QString errorMsg);
    /**
      *@brief signal 请求进度信号
      *@responseID 请求传入的唯一标志，用于应用判断是否为自己发送的请求
      *@totalLength 上传/下载文件总长度
      *@progress  当前上传/下载的进度
      *@status 上传/下载状态  开始下载 下载中 下载完成
      */
    void progress(long responseID,const int totalLength,const int progress,const int status);

    /**
      *@brief signal 订阅方法
      *@handleName 调用的方法
      *@data 回调数据
      */
    void subscribe(QString handleName,QVariant data);

signals:
    void error(int errorCode, QString errorMessage);

private:
    NativeSdkManager();
    static NativeSdkManager *m_pNativeSdkManager;

    Internal::NativeSdkManagerPrivate *d = nullptr;
    /**
     * @brief 连接所有的handler 信号
     * @param typeID 业务类的typeID,通过反射进行业务类实例化
     */
    void initHandlerConnect(QString typeID);
};
}
#endif // NATIVESDKMANAGER_H
