/*!
* \file decodethread.h
* \brief 一二维码解析，生成的工作线程
*
*此类是一二维码解析，生成的工作线程
*
*\author 桓乐乐 huanlele@syberos.com
*\version 1.0
*\date 2015/9/7
*/
#ifndef DECODETHREAD_H
#define DECODETHREAD_H
#include <QThread>
#include <QVideoFrame>
/*!
  \class DecodeThread
  \inModule 一二维码解析，生成的工作线程
  \brief 根据传入的进行一二维码解析，并且可以根据文字内容生成一二维码
  \ingroup generateForm
  DecodeThread 一二维码解析，生成的工作线程
*/
class QImage;
class QVideoFrame;
class DecodeThread: public QObject
{
    Q_OBJECT
public:
    DecodeThread(QObject *parent = 0);
    ~DecodeThread();
    void decodeBegin(const QVideoFrame &frame);
signals:

    void decodeBeginSignal(QVideoFrame frame);
    /**
     * @brief decodeFinished: 解码完成信号
     * @param decodeImagePath: 被解析的一二维码图片的路径
     * @param decodeContent: 解析一二维码图片获取的内容
     * @param success: true，成功； false，失败
     */
    void decodeFinished(const QString &decodeImagePath, const QString &decodeContent, const bool &success);
public slots:
    /**
     * @brief setFrame: 设置要解析的图片的帧
     * @param frame: 帧
     */
    void beginDecode(QVideoFrame frame);
private:
    volatile bool m_nDecode; ///< true, 解析一二维码图片；false，生成二维码图片
    QVideoFrame m_nFrame;///< 要解析的帧
    QString m_nEncodeContent; ///< 用来生成二维码图片的内容
    QString m_nEncodeImagePath; ///< 要生成二维码图片的保存路径
    QThread workThread;
};

#endif // DECODETHREAD_H
