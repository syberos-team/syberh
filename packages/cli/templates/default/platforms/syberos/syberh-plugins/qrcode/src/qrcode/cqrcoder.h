#ifndef CQRCODER_H
#define CQRCODER_H
#include <QString>
#include <QObject>


class CQRCoder
{
public:
    explicit CQRCoder();
    virtual ~CQRCoder();

    /*!
       \brief 生成二维码．将输入内容生成二维码，并将二维码图片保存到指定输出路径
       \a input , 输入内容
       \a output , 二维码图片输出路径
       \a micro , 生成二维码类型，true为微型，false为普通，默认为false
       \sa   decodeQR()
       \return 返回值：加密成功返回true；否则返回false
     */
    //bool encodeQR(const QString& input, const QString& output, bool micro = false);
    /*!
       \brief 解析二维码，将指定二维码图片解码为输出内容
       \a imgPath , 二维码图片路径
       \a output , 输出内容
       \a type , 二维码类型
       \sa   encodeQR()
       \return 返回值：解码成功返回true；否则返回false
     */
    bool decodeQRFunc(const QString& imgPath, QString& output, int& type);

private:
    QObject* pEncoder;

};

#endif // CQRCODER_H
