#ifndef NATIVESDKHANDLERBASE_H
#define NATIVESDKHANDLERBASE_H

#include <QObject>
#include <QVariantMap>
#include "./common/networkstatus.h"
#include "./common/errorinfo.h"
/**
 * @brief The NativeSdkHandlerBase class
 * 业务处理模块基类
 */
class NativeSdkHandlerBase : public QObject{
    Q_OBJECT
public:
    NativeSdkHandlerBase();
    virtual ~NativeSdkHandlerBase();
    /**
     * @brief request 上层应用发送的请求
     * @param callBackID 请求的唯一标志,用于应用判断是否为自己发送的请求
     * @param actionName 请求名称，用于区分是哪个请求
     * @params 请求传递的参数
     */
    virtual void request(QString callBackID,QString actionName,QVariantMap params);
    virtual void submit(QString typeID,QString callBackID,QString actionName,QVariant dataRowList, QVariant attachementes);
    virtual QObject * getUiSource(QString actionName);
    virtual void  loadQml(QString parentPageName, QString parentName, QString type);

protected:
    QString getNetworkConnectStatus();
    bool netWorkConnected();
signals:
    void success(long responseID, QVariant result);
    void failed(long responseID,long errorCode,QString errorMsg);
    void progress(long responseID,const int totalLength,const int progress,const int status);
    void subscribe(QString handleName,QVariant result);
};

#endif // NATIVESDKHANDLERBASE_H
