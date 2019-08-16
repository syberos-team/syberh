#include "multimediautils.h"
#define MULTIMEDIA_FILE "inspectionMultimedia/"
#include <QDir>
#include <QImage>
#include <QDebug>
MultimediaUtils* MultimediaUtils::m_pMultimediaUtils = NULL;
MultimediaUtils::MultimediaUtils(QObject *parent):QObject(parent)
{
    m_nMultiMediaPath =  QString("/home/user/") + MULTIMEDIA_FILE;
    QDir dir;
    if(!dir.exists(m_nMultiMediaPath))
        dir.mkdir(m_nMultiMediaPath);
    qDebug() << "multimediaUtils  m_nMultiMediaPath  " << m_nMultiMediaPath;
}

MultimediaUtils *MultimediaUtils::getInstance()
{
    if(m_pMultimediaUtils == NULL)
        m_pMultimediaUtils = new MultimediaUtils();
    return m_pMultimediaUtils;
}

MultimediaUtils::~MultimediaUtils()
{
}

QString MultimediaUtils::getMultimediaSavePath() const {
    return m_nMultiMediaPath;
}

void MultimediaUtils::removeMultimediaFile(const QStringList &multimediaFlieList, const bool all){
    if(all == true){
        QDir dir(m_nMultiMediaPath);
        QFileInfoList fileList = dir.entryInfoList();
        for(int i = 0; i < fileList.length(); i++){
            qDebug() << "SystemParam::removeMultimediaFile absoluteFilePath  " << fileList.at(i).absoluteFilePath()
                     <<"  filename is " << fileList.at(i).fileName();
            if(fileList.at(i).fileName() == "." || fileList.at(i).fileName() == "..")
                continue;
            QFile::remove(fileList.at(i).absoluteFilePath());
        }
    } else {
        for(int i = 0; i < multimediaFlieList.length(); i++){
            QString path = multimediaFlieList.at(i);
            qDebug() << "SystemParam::removeMultimediaFile  "<< path;
            QFile fl(path);
            fl.remove();
        }
    }
}

QString MultimediaUtils::scaledImage(const QString &imgPath){
    QImage img(imgPath);
    //img = img.scaled(720, 960);
    //img.save(imgPath, 0, 50);
    img.save(imgPath);
    return imgPath;
}

void MultimediaUtils::imgTransformed(const QString &imgPath)
{
    QImage img(imgPath);
    qDebug() << Q_FUNC_INFO << "111 width " << img.width() << "  height " << img.height();
    QMatrix matrix;
    matrix.rotate(90);
    img = img.transformed(matrix);
    qDebug() << Q_FUNC_INFO << "222 width " << img.width() << "  height " << img.height();
    img = img.scaled(720, 960);
    img.save(imgPath, 0, 50);
    qDebug() << Q_FUNC_INFO << "333 width " << img.width() << "  height " << img.height();
}
