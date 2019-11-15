#include "record.h"
#include "helper.h"

#include <QDebug>
#include <QUrlQuery>
#include <QException>
#include <QQuickView>
#include <QMetaObject>
#include <QGuiApplication>
#include "util/fileutil.h"
#include "framework/common/errorinfo.h"

int Record::typeId = qRegisterMetaType<Record *>();

Record::Record(){
    recoder = new QAudioRecorder();
    historydata = new HistoryData();
}

Record::~Record(){
    delete recoder;
    delete historydata;
}

void Record::request(QString callBackID, QString actionName, QVariantMap params)
{
    if (actionName == "list"){
        list(callBackID.toLong(), params);
    }else if (actionName == "start"){
        start(callBackID.toLong(), params);
    }else if (actionName == "pause"){
        pause(callBackID.toLong(),params);
    }else if (actionName == "resume"){
        resume(callBackID.toLong(),params);
    }else if(actionName == "stop"){
        stop(callBackID.toLong(),params);
    }else if(actionName == "remove"){
        remove(callBackID.toLong(),params);
    }
}

void Record::submit(QString typeID, QString callBackID, QString actionName, QVariant dataRowList, QVariant attachementes)
{
    Q_UNUSED(typeID)
    Q_UNUSED(callBackID)
    Q_UNUSED(actionName)
    Q_UNUSED(dataRowList)
    Q_UNUSED(attachementes)
}

void Record::list(long callBackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "list" << params << endl;

    //从数据库中获取录音列表
    try  {
        QJsonArray jsonArr = historydata->selectMetadata();
        emit success(callBackID, jsonArr);
    } catch (QException e) {
        qDebug() << Q_FUNC_INFO << "查询录音列表失败" << endl;
        emit failed(callBackID, ErrorInfo::SystemError, "系统错误:查询录音列表失败");
    }
}

void Record::start(long callBackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "start" << params << endl;

    //通过QAudioEncoderSettings类进行音频设置
    QAudioEncoderSettings audioSettings;
    // OS4.1.1版本(QT版本大于5.6)， 音频保存格式变了
    #if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    audioSettings.setCodec("audio/mpeg, mpegversion=(int)4");
    #else
    audioSettings.setCodec("audio/AAC");
    #endif
    audioSettings.setQuality(QMultimedia::HighQuality);
    recoder->setAudioSettings(audioSettings);

    //获取用户文件存储地址
    QString path = Helper::instance()->getInnerStorageRootPath() + "/record";
    QDir dir(path);
    if(!dir.exists()){
        dir.mkpath(path);
    }

    //配置保存的路径及文件名
    QDateTime time = QDateTime::currentDateTime();   //获取当前时间
    int timeT = time.toTime_t();                     //将当前时间转为时间戳
    QString timeStr = time.toString("yyyyMMdd");

    QString newFile = path + "/" +  timeStr + "_" + QString::number(timeT) + ".aac"; 
    currPath = newFile;
    QFile file(newFile);

    if(file.open(QFile::WriteOnly)){
        //设置文件权限
        file.setPermissions(QFileDevice::ReadOwner|QFileDevice::WriteOwner|QFileDevice::ReadUser);
        file.close();
        //设置保存的路径及文件名
        recoder->setOutputLocation(QUrl(file.fileName()));
        recoder->record();
    }

    try  {
        //在数据库中添加录音记录，文件大小、总时长默认0
        historydata->insertMetadata(newFile,0,0,time.toString("yyyy-MM-dd hh:mm:ss"));
    } catch (QException e) {
        qDebug() << Q_FUNC_INFO << "在数据库中添加录音记录失败" << endl;
        emit failed(callBackID, ErrorInfo::SystemError, "系统错误:在数据库中添加录音记录失败");
        return;
    }

    QJsonObject jsonObject;
    jsonObject.insert("path", newFile);
    QJsonValue jsonObjectValue = QJsonValue::fromVariant(jsonObject);
    qDebug() << Q_FUNC_INFO << "result" << jsonObjectValue.toString() << endl;

    emit success(callBackID, QVariant(jsonObject));
}

void Record::pause(long callBackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "pause" << params << endl;

    recoder->pause();
    emit success(callBackID, true);
}

void Record::resume(long callBackID,QVariantMap params){
    qDebug() << Q_FUNC_INFO << "resume" << params << endl;

    recoder->record();
    emit success(callBackID, true);
}

void Record::stop(long callBackID, QVariantMap params){
    qDebug() << Q_FUNC_INFO << "stop" << params << endl;

    recoder->stop();

    try  {
        //在数据库中修改录音记录，增加文件大小、总时长
        FileInfo fileInfo = FileUtil::getInfo(currPath);
        historydata->updateMetadata(currPath,fileInfo.size,recoder->duration());
    } catch (QException e) {
         qDebug() << Q_FUNC_INFO << "在数据库中修改录音记录失败"  << endl;
         emit failed(callBackID, ErrorInfo::SystemError, "系统错误:在数据库中修改录音记录失败");
         return;
    }
    emit success(callBackID, true);
}

void Record::remove(long callBackID, QVariantMap params){
    qDebug() << Q_FUNC_INFO << "remove" << params << endl;
    QString filePath = params.value("path").toString();

    try  {
        //删除本机记录
        FileUtil::remove(filePath,0);
        //删除数据库中记录
        historydata->removeMetadata(filePath);
    } catch (QException e) {
        qDebug() << Q_FUNC_INFO << "删除录音失败" << endl;
        emit failed(callBackID, ErrorInfo::SystemError, "系统错误:删除录音失败");
        return;
    }

    emit success(callBackID, true);
}
