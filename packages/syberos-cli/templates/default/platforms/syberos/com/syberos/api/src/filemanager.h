#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "framework/nativesdkhandlerbase.h"

class FileManager : public NativeSdkHandlerBase
{
    Q_OBJECT

public:
    Q_INVOKABLE FileManager();

    ~FileManager();
    void request(QString callBackID,QString actionName,QVariantMap params);

    static int typeId;

private:
    /**
     * @brief move          移动
     * @param callBackID
     * @param srcPath       源路径
     * @param destPath      目标路径
     */
    void move(QString callBackID, QString srcPath, QString destPath);
    /**
     * @brief copy          复制
     * @param callBackID
     * @param srcPath       源路径
     * @param destPath      目标路径
     */
    void copy(QString callBackID, QString srcPath, QString destPath);
    /**
     * @brief fileList      获取文件列表
     * @param callBackID
     * @param srcPath       源路径
     */
    void fileList(QString callBackID, QString srcPath);

    /**
     * @brief getInfo       获取文件信息
     * @param callBackID
     * @param srcPath       源路径
     */
    void getInfo(QString callBackID, QString srcPath);

    /**
     * @brief remove        删除
     * @param callBackID
     * @param srcPath       源路径
     * @param recursive     递归删除 0：否，1：是
     */
    void remove(QString callBackID, QString srcPath, int recursive);

};

#endif // FILEMANAGER_H
