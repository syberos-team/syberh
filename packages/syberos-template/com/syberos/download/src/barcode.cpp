#include "barcode.h"
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include "helper.h"
#include "../app/src/zxing.h"

#define SYBEROS_QRCODER_MAX_LENGTH 512

int Barcode::typeId = qRegisterMetaType<Barcode *>();

Barcode::Barcode()
{

}


Barcode::~Barcode(){

}

void Barcode::request(QString callbackId,QString actionName,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "actionName:" << actionName << "params:" << params << endl;
    if(actionName=="scan"){
        scan(callbackId, params.value("path").toString());
    }
}

void Barcode::submit(QString typeID,QString callBackID,QString actionName,QVariant dataRowList, QVariant attachementes){
    Q_UNUSED(typeID);
    Q_UNUSED(callBackID);
    Q_UNUSED(actionName);
    Q_UNUSED(dataRowList);
    Q_UNUSED(attachementes);
}

QString Barcode::scan(QString callbackId, QString filePath){
    QFile file(filePath);
    if(!file.exists()){
        qDebug() << Q_FUNC_INFO << "file not exists" << filePath << endl;
        return "";
    }
//    QString path = Helper::instance()->getInnerStorageRootPath() + "/tmp";
//    QDir dir(path);
//    if(!dir.exists()){
//        dir.mkpath(path);
//    }
//    QFileInfo fileInfo(file);
//    QString filename = fileInfo.fileName();

//    QString newFile = path + "/" + filename;
//    qDebug() << Q_FUNC_INFO << "copy" << filePath << newFile << endl;

//    bool rs = QFile::copy(filePath, newFile);
//    qDebug() << Q_FUNC_INFO << "copy result" << rs << endl;

//    bool removeRs = file.remove();
//    qDebug() << Q_FUNC_INFO << "remove result" << removeRs << endl;


//    QImage imageToDecode(filePath);
//    QZXing decoder;
//    decoder.setDecoder( QZXing::DecoderFormat_QR_CODE );
//    QString result = decoder.decodeImage(imageToDecode);

    QString output;
    int tmpType;
    char tmpOutput[512] = {0};
    QByteArray tmpImg = filePath.toLocal8Bit();
    int ret = decodeQR(tmpImg.data(),
                         &tmpType,
                         tmpOutput,
                         SYBEROS_QRCODER_MAX_LENGTH);
    file.remove();

    if(ret != 0){
        return "";
    }

    output = tmpOutput;
    return "";
}
