#ifndef FILESYSTEMMANAGER_H
#define FILESYSTEMMANAGER_H
#include <QObject>
#include <QJsonObject>
#include <QDir>


struct FileInfo
{
    QString path;
    qint64 size;
    QString created;
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
    static bool move(QString srcPath, QString destPath);
    /**
     * @brief copy          复制
     * @param srcPath       源路径
     * @param destPath      目标路径
     * @return              成功返回：sucess，失败返回：失败原因
     */
    static bool copy(QString srcPath, QString destPath);
    /**
     * @brief fileList      获取文件列表
     * @param srcPath       源路径
     * @return              成功返回：sucess，失败返回：失败原因
     */
   static QFileInfoList fileList(QString srcPath);

    /**
     * @brief fileType      文件类型
     * @param srcPath       源路径
     * @return              0：文件，1：文件夹，2：其他
     */
    static FileUtil::FileType fileType(QString srcPath);

    /**
     * @brief remove        移除
     * @param srcPath       源路径
     * @param recursive    是否递归删除 0：否，1：是
     * @return
     */
    static bool remove(QString srcPath, int recursive);

    /**
     * @brief getInfo       获取文件信息
     * @param srcPath       源路径
     * @return
     */
   static FileInfo getInfo(QString srcPath);

    /**
     * @brief exists        判断文件是否存在
     * @param srcPath       源路径
     * @return
     */
    static bool exists(QString srcPath);

    /**
     * @brief chmodr        赋予权限
     * @param path       源路径
     * @return
     */
    static bool chmodr(QString path);

};

#endif // FILESYSTEMMANAGER_H
