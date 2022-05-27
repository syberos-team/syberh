#ifndef FILESYSTEMMANAGER_H
#define FILESYSTEMMANAGER_H
#include <QObject>
#include <QJsonObject>
#include <QDir>

#include "../nativesdk_global.h"
#include "../framework/common/errorinfo.h"

namespace NativeSdk {

struct NATIVESDK_EXPORT FileInfo
{
    QString path;
    qint64 size;
    QString created;
};

struct NATIVESDK_EXPORT RespResult
{
    bool flag;

    // flag 为false msg为错误描述,code 错误编码
    int code;
    QString msg;
};



class NATIVESDK_EXPORT FileUtil : public QObject
{
    Q_OBJECT

public:

    enum FileType {
        File,
        Folder,
        Unknown
    };

    FileUtil();

    /**
     * @brief move          移动
     * @param srcPath       源路径
     * @param destPath      目标路径
     * @return              成功返回：sucess，失败返回：失败原因
     */
    Q_INVOKABLE static RespResult move(const QString &srcPath, const QString &destPath);
    /**
     * @brief copy          复制
     * @param srcPath       源路径
     * @param destPath      目标路径
     * @return              成功返回：sucess，失败返回：失败原因
     */
    Q_INVOKABLE static RespResult copy(const QString &srcPath, const QString &destPath);
    /**
     * @brief fileList      获取文件列表
     * @param srcPath       源路径
     * @return              成功返回：sucess，失败返回：失败原因
     */
    Q_INVOKABLE static QFileInfoList fileList(const QString &srcPath);

    /**
     * @brief fileType      文件类型
     * @param srcPath       源路径
     * @return              0：文件，1：文件夹，2：其他
     */
    Q_INVOKABLE static FileUtil::FileType fileType(const QString &srcPath);

    /**
     * @brief remove        移除
     * @param srcPath       源路径
     * @param recursive    是否递归删除 0：否，1：是
     * @return
     */
    Q_INVOKABLE static RespResult remove(const QString &srcPath, int recursive);

    /**
     * @brief getInfo       获取文件信息
     * @param srcPath       源路径
     * @return
     */
    Q_INVOKABLE static FileInfo getInfo(const QString &srcPath);

    /**
     * @brief getInfo       获取文件信息
     * @param srcPath       源路径
     * @return
     */
    Q_INVOKABLE static qint64 getInfoSize(const QString &srcPath);

    /**
     * @brief exists        判断文件是否存在
     * @param srcPath       源路径
     * @return
     */
    Q_INVOKABLE static bool exists(const QString &srcPath);

    /**
     * @brief chmodr        赋予权限
     * @param path       源路径
     * @return
     */
    Q_INVOKABLE static bool chmodr(const QString &path);

    /**
     * @brief rename        重命名
     * @param srcPath       源路径
     * @param newName       新名称
     * @return
     */
    Q_INVOKABLE static RespResult rename(const QString &srcPath, const QString &newName);

    /**
     * @brief mkdir         创建文件夹
     * @param destPath      目标路径
     * @return
     */
    Q_INVOKABLE static RespResult mkdir(const QString &destPath);

    /**
     * @brief mkdir         创建文件
     * @param destPath      目标路径
     * @return
     */
    Q_INVOKABLE static RespResult mkfile(const QString &destPath);

    /**
     * @brief compress      压缩文件
     * @param destName      压缩文件的名字
     * @param destPath      目标路径
     * @return
     */
    Q_INVOKABLE static RespResult compress(const QString &destName, const QString &destPath);

    /**
     * @brief decompress    解压文件
     * @param destPath      目标路径
     * @return
     */
    Q_INVOKABLE static RespResult decompress(const QString &destPath);
};

}
#endif // FILESYSTEMMANAGER_H
