#include "decodeworkspace.h"
#include <QDebug>
#include <QBitmap>
#include <QPixmap>
#include "qtcamera.h"
#include <QVideoProbe>
#include <errno.h>
DecodeWorkSpace::DecodeWorkSpace(QObject *parent):QObject(parent)
{
    m_pDThread = new DecodeThread();
    connect(m_pDThread, SIGNAL(decodeFinished(QString,QString,bool)), this, SLOT(finishedDecode(QString,QString,bool)));
    m_nImageProcessing = false;
    m_pCamera = QtCamera::getInstance();
    qDebug() << "DecodeWorkSpace::DecodeWorkSpace QtCamera::getInstance" << m_pCamera;
    m_pProbe = new QVideoProbe();
    connect(m_pProbe, SIGNAL(videoFrameProbed(QVideoFrame)), this, SLOT(processFrame(QVideoFrame)));
    connect(m_pCamera,SIGNAL(statusChanged(QCamera::Status)),this, SLOT(cameraStatusChanged(QCamera::Status)));
    m_pProbe->setSource(m_pCamera);
    QCameraExposure *cameraExposure = m_pCamera->exposure();
    cameraExposure->setFlashMode(QCameraExposure::FlashOff);
}

DecodeWorkSpace::~DecodeWorkSpace(){
    qDebug() << Q_FUNC_INFO;
    disconnect(m_pDThread, SIGNAL(decodeFinished(QString,QString,bool)), this, SLOT(finishedDecode(QString,QString,bool)));
    disconnect(m_pProbe, SIGNAL(videoFrameProbed(QVideoFrame)), this, SLOT(processFrame(QVideoFrame)));
    disconnect(m_pCamera,SIGNAL(statusChanged(QCamera::Status)),this, SLOT(cameraStatusChanged(QCamera::Status)));

    if(m_pCamera->status() == QtCamera::ActiveStatus){
        qDebug() << "m_pCamera->status() == QtCamera::ActiveStatus--------------- stopCamera ";
        m_pCamera->stopCamera();
    }
    delete m_pDThread;
    delete m_pProbe;
    m_pProbe = NULL;
    m_pDThread = NULL;
}

void DecodeWorkSpace::finishedDecode(const QString &decodeImagePath, const QString &decodeContent, const bool &success){
    qDebug() << "finishedDecode decodeImagePath "<< decodeImagePath << " decodeContent "<< decodeContent
             << "  success " << success << " thread Id " << QThread::currentThreadId();
    if(success == false){
        m_nImageProcessing = false;
    }else{
         m_nImageProcessing = false;
        emit decodeFinished(decodeImagePath, decodeContent, success);
    }
}

void DecodeWorkSpace::cameraStatusChanged(QCamera::Status status){
    qDebug() << Q_FUNC_INFO << status;
    emit changedCameraStatus((int)status);
}

void DecodeWorkSpace::processFrame(const QVideoFrame &frame)
{

    if(m_nImageProcessing == true){
        //qDebug() << Q_FUNC_INFO <<"  m_nImageProcessing == true return";
        return;
    }

    if (!frame.isValid()) {
        qWarning() << Q_FUNC_INFO << "This frame is not valid.";
        return;
    }
    m_nImageProcessing = true;
    m_pDThread->decodeBegin(frame);
     qDebug()<<Q_FUNC_INFO<<"m_pDThread->decodeBegin";
}




