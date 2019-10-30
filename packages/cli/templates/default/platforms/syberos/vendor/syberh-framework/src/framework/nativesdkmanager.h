#ifndef NATIVESDKMANAGER_H
#define NATIVESDKMANAGER_H

#include <QObject>
#include "nativesdkfactory.h"
#include <QMutex>
#include <QMap>
#include<QVariant>
#include "./common/extendedconfig.h"
#include "./devtools/devtools.h"


/**
 * @brief The NativeSdkManager class
 * 单例模式，提供上层应用接口
 */
class NativeSdkManager :public  QObject{
    Q_OBJECT
private:
    NativeSdkManager();
    static NativeSdkManager *m_pNativeSdkManager;
    NativeSdkFactory m_NativeSdkFactory;
    //拓展配置
    ExtendedConfig *extendConfig;
    //开发工具
    DevTools *devTools;
    /**
     * @brief 连接所有的handler 信号
     * @param typeID 业务类的typeID,通过反射进行业务类实例化
     */
    void initHandlerConnect(QString typeID);
public:
    ~NativeSdkManager();
    static NativeSdkManager * getInstance();

    /**
     * @brief request 上层应用请求接口
     * @param typeID 业务类的typeID,通过反射进行业务类实例化
     * @param callBackID 请求的唯一标志,用于应用判断是否为自己发送的请求
     * @param actionName 请求名称，用于区分是哪个请求
     * @params 请求传递的参数
     */
    Q_INVOKABLE void request(QString typeID,QString callBackID,QString actionName,QVariantMap params);
    /**
      *@brief submit 上层应用提交接口
      * @param typeID 业务类的typeID,通过反射进行业务类实例化
      * @param callBackID 请求的唯一标志,用于应用判断是否为自己发送的请求
      * @param actionName 请求名称，用于区分是哪个请求
      * @param dataRowList 需要提交的数据
      * @param attachementes 需要提交的多媒体数据
      */
    Q_INVOKABLE void submit(QString typeID,QString callBackID,QString actionName,QVariant dataRowList, QVariant attachementes);
    /**
      *@brief 用于获取需要导出给qml使用的Object
      *@param typeID 业务类的typeID,通过反射进行业务类的实例化
      *@param actionName 请求名称，用于区分是哪个请求
      */
    Q_INVOKABLE QObject * getUiSource(QString typeID,QString actionName);
    /**
      *@brief 用于上层应用使用c++中加载qml的情况
      *@param parentName 需要加载的qml的父page对象名
      *@param colNam   需要加载的qml的父对象名称
      *@param type     需要加载的qml类型，用于区分加载哪个qml文件
      */
    Q_INVOKABLE void loadQml(QString typeID,QString parentPageName,QString parentName,QString type);

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
};

#endif // NATIVESDKMANAGER_H
