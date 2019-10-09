#ifndef FILESYSTEMMANAGER_H
#define FILESYSTEMMANAGER_H
#include <QObject>
#include <QJsonObject>
#include <QDir>
#include "../framework/common/errorinfo.h"


struct FileInfo
{
    QString path;
    qint64 size;
    QString created;
};

struct RespResult
{
    bool flag;

    // flag 为false msg为错误描述,code 错误编码
    int code;
    QString msg;
};



class FileUtil : public QObject
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
    Q_INVOKABLE static RespResult move(QString srcPath, QString destPath);
    /**
     * @brief copy          复制
     * @param srcPath       源路径
     * @param destPath      目标路径
     * @return              成功返回：sucess，失败返回：失败原因
     */
    Q_INVOKABLE static RespResult copy(QString srcPath, QString destPath);
    /**
     * @brief fileList      获取文件列表
     * @param srcPath       源路径
     * @return              成功返回：sucess，失败返回：失败原因
     */
    Q_INVOKABLE static QFileInfoList fileList(QString srcPath);

    /**
     * @brief fileType      文件类型
     * @param srcPath       源路径
     * @return              0：文件，1：文件夹，2：其他
     */
    Q_INVOKABLE static FileUtil::FileType fileType(QString srcPath);

    /**
     * @brief remove        移除
     * @param srcPath       源路径
     * @param recursive    是否递归删除 0：否，1：是
     * @return
     */
    Q_INVOKABLE static RespResult remove(QString srcPath, int recursive);

    /**
     * @brief getInfo       获取文件信息
     * @param srcPath       源路径
     * @return
     */
    Q_INVOKABLE static FileInfo getInfo(QString srcPath);

    /**
     * @brief getInfo       获取文件信息
     * @param srcPath       源路径
     * @return
     */
    Q_INVOKABLE static qint64 getInfoSize(QString srcPath);

    /**
     * @brief exists        判断文件是否存在
     * @param srcPath       源路径
     * @return
     */
    Q_INVOKABLE static bool exists(QString srcPath);

    /**
     * @brief chmodr        赋予权限
     * @param path       源路径
     * @return
     */
    Q_INVOKABLE static bool chmodr(QString path);

    /**
     * @brief rename        重命名
     * @param srcPath       源路径
     * @param newName       新名称
     * @return
     */
    Q_INVOKABLE static RespResult rename(QString srcPath, QString newName);

};

#endif // FILESYSTEMMANAGER_H
