#include "qtcamerascan.h"
#include <QCameraImageCapture>
#include <QDir>
#include <QDateTime>
#include "multimediautils.h"
#define CAPTURE_FILE "capture"
QtCameraScan *QtCameraScan::m_camera = NULL;
QtCameraScan *QtCameraScan::getInstance()
{
    if(m_camera == NULL)
        m_camera = new QtCameraScan();
    return m_camera;
}

QtCameraScan::QtCameraScan():m_imageCapture(NULL)
{
    m_isImageCaptured = false;
    m_digitalZoomHasSet = false;
}

QtCameraScan::~QtCameraScan()
{
    qDebug() << "QtCameraScan::~QtCameraScan()  " << m_imageCapture;
    if(m_imageCapture){
        disconnect(m_imageCapture, SIGNAL(imageSaved(int,QString)), this, SIGNAL(savedImage(int ,QString)));
        disconnect(this, SIGNAL(lockStatusChanged(QCamera::LockStatus,QCamera::LockChangeReason)),
                this, SLOT(changeLockStatus(QCamera::LockStatus,QCamera::LockChangeReason)));
        delete m_imageCapture;
        m_imageCapture = NULL;
    }
    qDebug() << "QtCameraScan::~QtCameraScan() ok";
}

void QtCameraScan::setImageCapture(){
    if(m_imageCapture == NULL){
        m_imageCapture = new QCameraImageCapture(this);
        connect(m_imageCapture, SIGNAL(imageSaved(int,QString)), this, SIGNAL(savedImage(int , QString)));
        connect(this, SIGNAL(lockStatusChanged(QCamera::LockStatus,QCamera::LockChangeReason)),
                this, SLOT(changeLockStatus(QCamera::LockStatus,QCamera::LockChangeReason)));
    }
    qDebug() << "imageCapture->capture()111111111111111111";
    m_isImageCaptured = true;
    this->searchAndLock();
}

void QtCameraScan::removeImageCapture(){
    if(m_imageCapture != NULL){
        disconnect(m_imageCapture,SIGNAL(imageSaved(int,QString)),this, SIGNAL(savedImage(int ,QString)));
    }
}

void QtCameraScan::startCameraAndSetZoom(){
    this->start();
    QCameraFocus *focus = this->focus();
    qDebug() << "QtCameraScan::startCameraAndSetZoom()   ---------   get focus  ok";
    focus->setFocusPointMode(QCameraFocus::FocusPointCenter);
    focus->zoomTo(focus->opticalZoom(), 6.0);
    m_digitalZoomHasSet = true;
}

void QtCameraScan::stopCamera(){
    if(m_digitalZoomHasSet == true){
        QCameraFocus *focus = this->focus();
        focus->zoomTo(focus->opticalZoom(), 1.0);
        m_digitalZoomHasSet = false;
    }
    qDebug() << "stopCamera  this->lockStatus()  " << this->lockStatus();
    this->unlock();
    qDebug() << "stopCamera QtCameraScan::unlock ok  status is  " << this->status();
    this->stop();
}

void QtCameraScan::setCameraFlashMode(const QString &mode)
{
    //bool setCameraStatus = false;
    if(mode == getCameraFlashMode()){
        qDebug() << "mode == getCameraFlashMode()  return";
        return;
    }
//    if(this->status() == QtCameraScan::ActiveStatus){
//        qDebug() << "setCameraFlashMode  QtCameraScan::ActiveStatus--------------- stopCamera ";
//        this->stopCamera();
//        setCameraStatus = true;
//    }
    //set Camera flash mode
    QCameraExposure *cameraExposure = this->exposure();
    qDebug() << "cameraExposure->setFlashMode(mode)  " << mode;
    if(mode == "flashOn")
        cameraExposure->setFlashMode(QCameraExposure::FlashOn);
    else if(mode == "flashAuto")
        cameraExposure->setFlashMode(QCameraExposure::FlashAuto);
    else if(mode == "flashOff")
        cameraExposure->setFlashMode(QCameraExposure::FlashOff);

//    if(setCameraStatus == true)
//        this->start();
}

QString QtCameraScan::getCameraFlashMode() const
{
    QCameraExposure *cameraExposure = this->exposure();
    switch (cameraExposure->flashMode()) {
    case QCameraExposure::FlashOn:
        return "flashOn";
    case QCameraExposure::FlashAuto:
        return "flashAuto";
    case QCameraExposure::FlashOff:
        return "flashOff";
    }
    return "unknown";
}

void QtCameraScan::changeStatus(QCamera::Status status){
    qDebug() << "QtCameraScan::changeStatus00000000000000000000     " << status;
}

void QtCameraScan::changeLockStatus(QCamera::LockStatus status, QCamera::LockChangeReason reason)
{
    qDebug() << "QtCameraScan::changeLockStatus   isImageCaptured is  " << m_isImageCaptured <<
                "  status  is  " << status << "   reson is  " << reason;
    if(m_isImageCaptured == true && (status == QCamera::Unlocked || status == QCamera::Locked)){
        m_isImageCaptured = false;
        qDebug() << "QtCameraScan::changeLockStatus  m_imageCapture->capture()";
        QString multimediaSavepath = MultimediaUtils::getInstance()->getMultimediaSavePath();
        QString fileName = QDateTime::currentDateTime().toString("yyyy-MM-dd_hhmmss") + ".jpg";
        m_nImageSavePath = multimediaSavepath + "JPG_" + fileName;
        qDebug() << "image save path is   " << m_nImageSavePath;
        m_imageCapture->capture(m_nImageSavePath);
        qDebug() << "QtCameraScan::changeLockStatus   m_imageCapture->capture()  ok";
    }
}
