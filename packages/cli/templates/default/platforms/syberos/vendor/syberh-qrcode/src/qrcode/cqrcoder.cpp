#include "cqrcoder.h"
//#include "qqrencode.h"
#include "zxing.h"
#define SYBEROS_QRCODER_MAX_LENGTH 512

/*!
    \class CQRCoder
    \inmodule syberos-qt
    \brief CQRCoder 提供生成二维码, 解析二维码
    \ingroup systeminformation-system
    \ingroup systeminformation
*/


/*!
    \brief 构造函数
 */
CQRCoder::CQRCoder()
{
    //pEncoder = new QQREncode(0);
}

/*!
    \brief 析构函数
 */
CQRCoder::~CQRCoder()
{
//    if(pEncoder){
//        delete pEncoder;
//        pEncoder = NULL;
//    }
}

//bool CQRCoder::encodeQR(const QString& input, const QString& output, bool micro)
//{
//    return ((QQREncode*)pEncoder)->encode(input, output, micro);
//}

bool CQRCoder::decodeQRFunc(const QString& imgPath, QString& output, int& type)
{
    int tmpType;
    char tmpOutput[512] = {0};
    QByteArray tmpImg = imgPath.toLocal8Bit();
    int ret = decodeQR(tmpImg.data(),
                         &tmpType,
                         tmpOutput,
                         SYBEROS_QRCODER_MAX_LENGTH);
    if(ret != 0){
        return false;
    }
    output = tmpOutput;
    type = tmpType;
    return true;
}
