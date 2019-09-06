#ifndef FILESYSTEMMANAGER_H
#define FILESYSTEMMANAGER_H
#include <QObject>
#include <QJsonObject>


struct FileInfo
{
    QString path;
    qint64 size;
    QString created;
};

class FileSystemManager : public QObject
{
    Q_OBJECT

public:

    enum FileType {
        File,
        Folder,
        Unknown
    };

    FileSystemManager();

    /**
     * @brief move          移动
     * @param srcPath       源路径
     * @param destPath      目标路径
     * @return              成功返回：sucess，失败返回：失败原因
     */
    QString move(QString srcPath, QString destPath);
    /**
     * @brief copy          复制
     * @param srcPath       源路径
     * @param destPath      目标路径
     * @return              成功返回：sucess，失败返回：失败原因
     */
    QString copy(QString srcPath, QString destPath);
    /**
     * @brief fileList      获取文件列表
     * @param srcPath       源路径
     * @return              成功返回：sucess，失败返回：失败原因
     */
    QString fileList(QString srcPath);

    /**
     * @brief fileType      文件类型
     * @param srcPath       源路径
     * @return              0：文件，1：文件夹，2：其他
     */
    FileSystemManager::FileType fileType(QString srcPath);

    /**
     * @brief remove        移除
     * @param srcPath       源路径
     * @param fileType      0：文件，1：文件夹
     * @param recursive     当fileType为1时有效。0：否，1：是
     * @return
     */
    QString remove(QString srcPath, FileSystemManager::FileType fileType, QString recursive);

    /**
     * @brief getInfo       获取文件信息
     * @param srcPath       源路径
     * @return
     */
    FileInfo getInfo(QString srcPath);

    /**
     * @brief exists        判断文件是否存在
     * @param srcPath       源路径
     * @return
     */
    bool exists(QString srcPath);

};

#endif // FILESYSTEMMANAGER_H
