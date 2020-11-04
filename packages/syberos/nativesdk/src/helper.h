#ifndef HELPER_H
#define HELPER_H

#include "nativesdk_global.h"

#include <QtGlobal>
#include <QObject>
#include <QJsonObject>

namespace NativeSdk {

namespace Internal {class HelperPrivate;}

class NATIVESDK_EXPORT Helper : public QObject
{
    Q_OBJECT
public:
    ~Helper();

    static Helper *instance();

    //获取应用www目录位置，该目录受debug模式影响。
    //非debug模式：/data/apps/[sopid]/www，
    //debug模式：/data/data/[sopid]/www
    Q_INVOKABLE QString getWebRootPath();
    //获取应用默认的www目录位置。/data/apps/[sopid]/www
    Q_INVOKABLE QString getDefaultWebRootPath();
    //获取应用程序或者服务的私有数据目录。/data/data/[sopid]
    Q_INVOKABLE QString getDataRootPath();
    //获取外置存储的目录，如记忆卡等设备。/mnt/sdcard
    Q_INVOKABLE QString getExternStorageRootPath();
    //获取内置存储的目录。 /home/user
    Q_INVOKABLE QString getInnerStorageRootPath();
    //获取日志级别
    Q_INVOKABLE QString logLevelName();

    //获取应用私有数据中的www目录。/data/data/[sopid]/www
    Q_INVOKABLE QString getDataWebRootPath();
    //文件是否存在
    Q_INVOKABLE bool exists(QString filePath);

    Q_INVOKABLE QString sopid();

    Q_INVOKABLE QJsonObject aboutPhone();

    // 获取Qt版本号，示例：0x050900
    // 注意，由于返回的是16进制数，如需与qt5.12.0版本比较，需使用 0x050c00 比较，示例：helper.getQtVersion() >= 0x050c00
    Q_INVOKABLE qint32 getQtVersion();
    // 获取Qt版本号，示例：5.9.0
    Q_INVOKABLE QString getQtVersionName();

    // 获取Qt版本号是否大于5.6.0
    Q_INVOKABLE bool isGtQt56();

    /**
     * @brief emptyDir 清空文件夹
     * @param path
     */
    Q_INVOKABLE bool emptyDir(const QString &path);
    /**
      * @brief isPicture 判断是否是图片
      * @param filepath
      */
    Q_INVOKABLE bool isPicture(QString filepath);

    /**
      * @brief isAudio 判断是否是音频
      * @param filepath
      */
    Q_INVOKABLE bool isAudio(QString filepath);

    /**
     * 获取首页，首先尝试从扩展参数中获取，若为空，则调用getWebRootPath()获取
     */
    Q_INVOKABLE QString getHomePage();

private:
    explicit Helper(QObject *parent = 0);
    Helper(const Helper &) Q_DECL_EQ_DELETE;
    Helper &operator=(Helper client) Q_DECL_EQ_DELETE;

    Internal::HelperPrivate *d;
    static Helper *helper;
};

}
#endif // HELPER_H
