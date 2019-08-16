/*!
* \file qtcamerascan.h
* \brief 操作相机的类
*
*此类操作相机接口
*
*\author 桓乐乐 huanlele@syberos.com
*\version 1.0
*\date 2015/9/7
*/
#ifndef QTCAMERASCAN_H
#define QTCAMERASCAN_H

#include <QObject>
#include <QCamera>
#include <QCameraExposure>
/*!
  \class QtCameraScan
  \inModule 操作相机的类
  \brief 操作相机接口 相机的开关
  \ingroup generateForm
  QtCameraScan 操作相机的类
*/
class QCameraImageCapture;
class QtCameraScan : public QCamera
{
    Q_OBJECT
    Q_PROPERTY(QObject *mediaObject READ mediaObject NOTIFY mediaObjectChanged SCRIPTABLE false DESIGNABLE false)
public:
    static QtCameraScan* getInstance();
    ~QtCameraScan();

    /**
     * @brief setImageCapture： 准备拍照并且保存图片
     */
    Q_INVOKABLE void setImageCapture();

    /**
     * @brief removeImageCapture： 断开保存图片的信号
     */
    Q_INVOKABLE void removeImageCapture();

    /**
     * @brief startCameraAndSetZoom 启动相机并且设置zoom
     */
    Q_INVOKABLE void startCameraAndSetZoom();

    /**
     * @brief stopCamera： 停止相机
     */
    Q_INVOKABLE void stopCamera();

    /**
     * @brief setCameraFlashMode： 设置相机拍照模式
     * @param mode： 相机拍照模式
     */
    Q_INVOKABLE void setCameraFlashMode(const QString & mode);

    /**
     * @brief getCameraFlashMode： 获取相机拍照模式
     * @return ： 相机拍照模式
     */
    Q_INVOKABLE QString getCameraFlashMode() const;

    /**
     * @brief mediaObject： 返回当前对象
     * @return： 当前对象
     */
    QObject *mediaObject() { return this; }

signals:

    /**
    * @brief mediaObjectChanged： mediaObject变化信号
    */
   void mediaObjectChanged();

   /**
    * @brief savedImage： 接受拍照后图片已经保存的信号
    * @param id  ： 操作id
    * @param fileName ： 保存图片的路径
    */
   void savedImage(int id, QString fileName);
private slots:

   /**
    * @brief changeLockStatus ： 接受相机聚焦状态变化的槽
    * @param status ：相机聚焦状态
    * @param reason ：变化原因
    */
   void changeLockStatus(QCamera::LockStatus status, QCamera::LockChangeReason reason);

   void changeStatus(QCamera::Status status);
private:
   QtCameraScan();
   QCameraImageCapture *m_imageCapture;  ///< 拍照类的指针
   bool m_isImageCaptured;              ///< 是否正在拍照
   static QtCameraScan *m_camera;           ///< 相机的静态对象
   bool m_digitalZoomHasSet;            ///< 调整了相机的zoom
   QString m_nImageSavePath;           ///<拍照图片保存路径
};

#endif // QTCAMERASCAN_H
