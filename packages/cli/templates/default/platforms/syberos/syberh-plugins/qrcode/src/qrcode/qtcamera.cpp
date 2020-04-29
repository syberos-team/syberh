#include "qtcamera.h"
#include <QCameraImageCapture>
#include <QDir>
#include <QDateTime>
#include "multimediautils.h"
#define CAPTURE_FILE "capture"
QtCamera *QtCamera::m_camera = NULL;
QtCamera *QtCamera::getInstance()
{
    if(m_camera == NULL)
        m_camera = new QtCamera();
    return m_camera;
}

QtCamera::QtCamera():m_imageCapture(NULL)
{
    m_isImageCaptured = false;
    m_digitalZoomHasSet = false;
}

QtCamera::~QtCamera()
{
    qDebug() << "QtCamera::~QtCamera()  " << m_imageCapture;
    if(m_imageCapture){
        disconnect(m_imageCapture, SIGNAL(imageSaved(int,QString)), this, SIGNAL(savedImage(int ,QString)));
        disconnect(this, SIGNAL(lockStatusChanged(QCamera::LockStatus,QCamera::LockChangeReason)),
                this, SLOT(changeLockStatus(QCamera::LockStatus,QCamera::LockChangeReason)));
        delete m_imageCapture;
        m_imageCapture = NULL;
    }
    qDebug() << "QtCamera::~QtCamera() ok";
}

void QtCamera::setImageCapture(){
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

void QtCamera::removeImageCapture(){
    if(m_imageCapture != NULL){
        disconnect(m_imageCapture,SIGNAL(imageSaved(int,QString)),this, SIGNAL(savedImage(int ,QString)));
    }
}

void QtCamera::startCameraAndSetZoom(){
    this->start();
    QCameraFocus *focus = this->focus();
    qDebug() << "QtCamera::startCameraAndSetZoom()   ---------   get focus  ok";
    focus->setFocusPointMode(QCameraFocus::FocusPointCenter);
    focus->zoomTo(focus->opticalZoom(), 6.0);
    m_digitalZoomHasSet = true;
}

void QtCamera::stopCamera(){
    if(m_digitalZoomHasSet == true){
        QCameraFocus *focus = this->focus();
        focus->zoomTo(focus->opticalZoom(), 1.0);
        m_digitalZoomHasSet = false;
    }
    qDebug() << "stopCamera  this->lockStatus()  " << this->lockStatus();
    this->unlock();
    qDebug() << "stopCamera QtCamera::unlock ok  status is  " << this->status();
    this->stop();
}

void QtCamera::setCameraFlashMode(const QString &mode)
{
    //bool setCameraStatus = false;
    if(mode == getCameraFlashMode()){
        qDebug() << "mode == getCameraFlashMode()  return";
        return;
    }
//    if(this->status() == QtCamera::ActiveStatus){
//        qDebug() << "setCameraFlashMode  QtCamera::ActiveStatus--------------- stopCamera ";
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

QString QtCamera::getCameraFlashMode() const
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

void QtCamera::changeStatus(QCamera::Status status){
    qDebug() << "QtCamera::changeStatus00000000000000000000     " << status;
}

void QtCamera::changeLockStatus(QCamera::LockStatus status, QCamera::LockChangeReason reason)
{
    qDebug() << "QtCamera::changeLockStatus   isImageCaptured is  " << m_isImageCaptured <<
                "  status  is  " << status << "   reson is  " << reason;
    if(m_isImageCaptured == true && (status == QCamera::Unlocked || status == QCamera::Locked)){
        m_isImageCaptured = false;
        qDebug() << "QtCamera::changeLockStatus  m_imageCapture->capture()";
        QString multimediaSavepath = MultimediaUtils::getInstance()->getMultimediaSavePath();
        QString fileName = QDateTime::currentDateTime().toString("yyyy-MM-dd_hhmmss") + ".jpg";
        m_nImageSavePath = multimediaSavepath + "JPG_" + fileName;
        qDebug() << "image save path is   " << m_nImageSavePath;
        m_imageCapture->capture(m_nImageSavePath);
        qDebug() << "QtCamera::changeLockStatus   m_imageCapture->capture()  ok";
    }
}
