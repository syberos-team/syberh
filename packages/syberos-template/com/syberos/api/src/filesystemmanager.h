#ifndef FILESYSTEMMANAGER_H
#define FILESYSTEMMANAGER_H
#include <QObject>

class FileSystemManager : public QObject
{
    Q_OBJECT

public:

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
    qint32 fileType(QString srcPath);

    /**
     * @brief remove        移除
     * @param srcPath       源路径
     * @param fileType      0：文件，1：文件夹
     * @return
     */
    QString remove(QString srcPath, QString fileType);

};

#endif // FILESYSTEMMANAGER_H
