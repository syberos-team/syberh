#include "decodethread.h"
#include <QDebug>
#include <QImage>
#include <QFile>
#include "cqrcoder.h"
#include <errno.h>
#include "qandroidmultimediautils.h"
#define  BARCODE_IMAGE_WIDTH 450
#define  BARCODE_IMAGE_HEIGHT 450
#define  DECODE_TMP_IMAGE_PATH "/tmp/syberosDecodeImage.jpg"
DecodeThread::DecodeThread(QObject *parent):m_nDecode(true)
{
    this->moveToThread(&workThread);
    connect(this, SIGNAL(decodeBeginSignal(QVideoFrame)), this, SLOT(beginDecode(QVideoFrame)));
    workThread.start();
}

DecodeThread::~DecodeThread()
{
    workThread.quit();
    workThread.wait();
    qDebug() <<Q_FUNC_INFO<<" workThread quit";
}

void DecodeThread::decodeBegin(const QVideoFrame &frame)
{
   qDebug()<<Q_FUNC_INFO<<workThread.isRunning()<< workThread.isFinished();
    if(!workThread.isRunning()){
        this->moveToThread(&workThread);
        connect(this, SIGNAL(decodeBeginSignal(QVideoFrame)), this, SLOT(beginDecode(QVideoFrame)));
        workThread.start();
    }
    qDebug() << Q_FUNC_INFO << QThread::currentThreadId();
    emit decodeBeginSignal(frame);
}

void DecodeThread::beginDecode(QVideoFrame frame)
{

    if(frame.isValid()){
        QVideoFrame clonedFrame(frame);
        qDebug() << Q_FUNC_INFO << "*****************" <<frame.pixelFormat();
        clonedFrame.map(QAbstractVideoBuffer::ReadOnly);

        const uchar *bits = clonedFrame.bits();

        QImage orgImg = QImage(frame.size(), QImage::Format_ARGB32);
        qt_convert_NV21_to_ARGB32(bits,
                                  (quint32 *)orgImg.bits(),
                                  clonedFrame.width(),
                                  clonedFrame.height());
        QMatrix matrix;
        matrix.rotate(90);
        orgImg = orgImg.transformed(matrix);
        clonedFrame.unmap();
        frame = QVideoFrame();

        QFile::remove(DECODE_TMP_IMAGE_PATH);
        int decodeImgWidth = BARCODE_IMAGE_WIDTH;
        QImage img = orgImg.copy((orgImg.width() - decodeImgWidth)/2,
                                 (orgImg.height() - decodeImgWidth)/2,
                                 decodeImgWidth, decodeImgWidth);
        bool saveRv = img.save(DECODE_TMP_IMAGE_PATH);
        qDebug() <<"img.save   ready to sync " <<saveRv << strerror(errno);
        CQRCoder zxingInf;
        QString content;
        int type;
        qDebug() << "begine  zxingInf.decodeQRFunc   " << DECODE_TMP_IMAGE_PATH;
        int rv = zxingInf.decodeQRFunc(DECODE_TMP_IMAGE_PATH, content, type);
        qDebug() << "5555555555555  zxingInf.decodeQRFunc decodeFinished ok " << rv << " type is " << type;
        qDebug() << Q_FUNC_INFO << " thread Id " << QThread::currentThreadId();
        emit decodeFinished(DECODE_TMP_IMAGE_PATH, content, rv);
    } else {
        qDebug() << Q_FUNC_INFO << "frame.isValid() == false";
        emit decodeFinished(DECODE_TMP_IMAGE_PATH, "", false);
    }
}
