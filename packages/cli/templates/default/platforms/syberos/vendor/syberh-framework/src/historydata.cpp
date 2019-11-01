#include "historydata.h"
#include "helper.h"

#include <QtSql>
#include <QDebug>

int HistoryData::typeId = qRegisterMetaType<HistoryData *>();

HistoryData::HistoryData(){}

HistoryData::~HistoryData(){}

void HistoryData::request(QString callBackID, QString actionName, QVariantMap params){
    qDebug() << "callBackID" << callBackID << "actionName" << actionName << "params" << params << endl;
}

void HistoryData::submit(QString typeID, QString callBackID, QString actionName, QVariant dataRowList, QVariant attachementes){
    Q_UNUSED(typeID)
    Q_UNUSED(callBackID)
    Q_UNUSED(actionName)
    Q_UNUSED(dataRowList)
    Q_UNUSED(attachementes)
}

bool HistoryData::createConnection() {
    qDebug() << Q_FUNC_INFO << "createConnection" << endl;
    myConnection = QSqlDatabase::addDatabase("QSQLITE");

    QString dataDir = Helper::instance()->getDataRootPath();
    QDir d(dataDir);
    if (!d.exists()) {
        qDebug() << Q_FUNC_INFO << "数据库不存在" << endl;
        checkOrCreateDir(dataDir);
    }

    QString dbPath = dataDir + "/" + "syberos-aduiorecorder.sqlite";
    qDebug() << Q_FUNC_INFO << "数据库路径 = " << dbPath << endl;
    myConnection.setDatabaseName(dbPath);

    bool isOK = myConnection.open();
    if (!isOK) {
        qDebug() << Q_FUNC_INFO << "打开数据库失败" << endl;
        return false;
    }

    QSqlQuery query(myConnection);
    QStringList queries;
    queries << "CREATE TABLE IF NOT EXISTS files ("
               "  id INTEGER PRIMARY KEY autoincrement," // Set id to NULL and it will be increased autoly.
               "  filename   TEXT,"
               "  path       TEXT,"
               "  size       INT,"
               "  duration   INT,"
               "  created   TEXT"
               ")";

    queries << "CREATE INDEX IF NOT EXISTS idx_files_filename "
               "ON files(filename)";

    queries << "CREATE INDEX IF NOT EXISTS idx_files_path "
               "ON files(path)";

    queries << "CREATE INDEX IF NOT EXISTS idx_files_size "
               "ON files(size)";

    queries << "CREATE INDEX IF NOT EXISTS idx_files_duration "
               "ON files(duration)";

    queries << "CREATE INDEX IF NOT EXISTS idx_files_created "
               "ON files(created)";

    foreach (QString q, queries) {
        if (! query.exec(q)) {
            qDebug() << Q_FUNC_INFO << "执行sql失败:" << query.lastError();
            break;
        }
    }
    return true;
}

bool HistoryData::checkOrCreateDir(QString path){
    qDebug() << Q_FUNC_INFO << "checkOrCreateDir" << endl;
    QDir __dir;
    bool m_overwritePermission = true;
    if (!__dir.exists(path)) {
        qDebug()  << Q_FUNC_INFO << "指定目录: " << path << "不存在，则尝试创建";
        if (!__dir.mkpath(path)) {
            return false;
        } else {
            qDebug()  << Q_FUNC_INFO << "创建指定目录成功: " << path ;
            if (m_overwritePermission) {
                QFile file(path);
                if (!file.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::ExeOwner
                                         | QFileDevice::ReadGroup | QFileDevice::WriteGroup | QFileDevice::ExeGroup
                                         | QFileDevice::ReadOther | QFileDevice::WriteOther | QFileDevice::ExeOther)) {
                }
            }
            return true;
        }
    }

    QFileInfo fi(path);
    if (!fi.isWritable()) {
        return false;
    }
    return true;
}

void HistoryData::insertMetadata(QString path,int size,int duration,QString created){
    qDebug() << Q_FUNC_INFO << "insertMetadata" << endl;

    if (!createConnection()){
        qDebug() << Q_FUNC_INFO << "连接数据库失败" << endl;
    }

    QSqlQuery query(myConnection);
    QString q = "insert into files(id, path, size, duration, created)"
                "values(NULL, '%1', '%2', %3, '%4')";

    if (!query.exec(q.arg(path).arg(size).arg(duration).arg(created))) {
        qDebug() << Q_FUNC_INFO << "新增录音记录失败,error:" << query.lastError();
    }

    myConnection.close();

}

void HistoryData::removeMetadata(QString path) {
    qDebug() << Q_FUNC_INFO << "removeMetadata" << endl;

    if (!createConnection()){
        qDebug() << Q_FUNC_INFO << "连接数据库失败" << endl;
    }

    QSqlQuery query(myConnection);
    QString q = "delete from files where path = '%1'";

    if (!query.exec(q.arg(path))) {
        qDebug() << Q_FUNC_INFO << "删除录音记录失败,error:" << query.lastError();
    }

    myConnection.close();
}

void HistoryData::updateMetadata(QString path,int size,int duration){
    qDebug() << Q_FUNC_INFO << "updateDuration" << endl;

    if (!createConnection()){
        qDebug() << Q_FUNC_INFO << "连接数据库失败" << endl;
    }

    QSqlQuery query(myConnection);
    query.prepare("update files set duration = ?,size = ? where path = ?");
    query.addBindValue(ceil(duration/1000));
    query.addBindValue(size);
    query.addBindValue(path);

    if (!query.exec()) {
        qDebug() << Q_FUNC_INFO << "修改录音记录失败,error:" << query.lastError();
    }

    myConnection.close();
}

QJsonArray HistoryData::selectMetadata() {
    qDebug() << Q_FUNC_INFO << "selectMetadata" << endl;

    if (!createConnection()){
        qDebug() << Q_FUNC_INFO << "连接数据库失败" << endl;
    }

    QJsonArray jsonArr;
    QSqlQuery query(myConnection);
    QString q = "select * from files order by created desc";

    QString path = "";
    if (!query.exec(q)) {//查询所有录音文件失败处理
        qDebug() << Q_FUNC_INFO << "查询录音列表失败,error:" << query.lastError();
    }

    while (query.next()) {//循环录音列表
        path = query.value("path").toString();

        if(!path.isEmpty() && !QFile::exists(path)) {//删除数据库中不存在录音记录
            qDebug()  << Q_FUNC_INFO << "删除数据库中不存在录音记录,path:" << path  << endl;
            removeMetadata(path);
        }else{
            QJsonObject jsonObj;
            jsonObj.insert("id", query.value("id").toString());

            QStringList list = query.value("path").toString().split("/");
            QString fileName = list.at(list.count()-1);

            jsonObj.insert("fileName", fileName);
            jsonObj.insert("path", query.value("path").toString());
            jsonObj.insert("size", query.value("size").toInt());
            jsonObj.insert("duration", formatTime(1000*query.value("duration").toInt()));
            jsonObj.insert("created", query.value("created").toString());
            jsonArr.append(jsonObj);
        }
    }

    myConnection.close();

    qDebug() << Q_FUNC_INFO << "selectMetadata:jsonArr" << jsonArr << endl;
    return jsonArr;
}

QString HistoryData::formatTime(int duration) {
    qDebug() << Q_FUNC_INFO << "formatTime" << duration << endl;
    int secs = 0;
    int mins = 0;
    int hours = 0;

    duration = ceil(duration / 1000);
    secs = floor(duration % 60);

    duration = duration / 60;
    mins = floor(duration % 60);

    duration = duration / 60;
    hours = floor(duration);

    QString secsStr;
    QString minsStr;
    QString hoursStr;

    if (secs < 10){ if(secs == 0) secsStr = "01"; else secsStr = "0" + QString::number(secs); }else{ secsStr = QString::number(secs);}
    if (mins < 10){ if(mins == 0) minsStr = "00"; else minsStr = "0" + QString::number(mins); }else{ minsStr = QString::number(mins);}
    if (hours < 10){ if(hours == 0) hoursStr = "00"; else hoursStr = "0" + QString::number(hours); }else{ hoursStr = QString::number(hours); }

    return hoursStr + ":" + minsStr + ":" + secsStr;
}
