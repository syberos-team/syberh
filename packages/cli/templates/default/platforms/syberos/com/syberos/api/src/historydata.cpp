#include "historydata.h"

#include <QtSql>
#include <QDebug>

#define APP_DATADIR QDir::homePath()
int HistoryData::typeId = qRegisterMetaType<HistoryData *>();

HistoryData::HistoryData(){
    if (!createConnection())
        qDebug() << "create connection failed";
}

HistoryData::~HistoryData(){

}

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

    QString dataDir = APP_DATADIR;
    QDir d(dataDir);
    if (!d.exists()) {
        qDebug() << "dataDir is not exist." << endl;
        checkOrCreateDir(dataDir);
    }

    QString dbPath = dataDir + "/" + "syberos-aduiorecorder.sqlite";
    qDebug() << "dbPath = " << dbPath << endl;
    myConnection.setDatabaseName(dbPath);

    bool isOK = myConnection.open();
    if (!isOK) {
        qDebug() << "open DB failed." << endl;
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
        qDebug() << "executing statement:" << q;
        if (! query.exec(q)) {
            qDebug() << "failed to execute query:" << query.lastError();
            break;
        } else {
            qDebug() << "exectuing successfully." << endl;
        }
    }

    return true;
}

bool HistoryData::checkOrCreateDir(QString path){
    qDebug() << Q_FUNC_INFO << "checkOrCreateDir" << endl;
    QDir __dir;
    bool m_overwritePermission = true;
    if (!__dir.exists(path)) {
        qDebug() << "[FolderChecker] dir: " << path << " does not exsit, tring to create it.";
        if (!__dir.mkpath(path)) {
            qDebug() << "[FolderChecker] Fialed to create dir: " << path;
            return false;
        } else {
            qDebug() << "[FolderChecker] successfully created dir: " << path ;
            if (m_overwritePermission) {
                QFile file(path);
                if (!file.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::ExeOwner
                                         | QFileDevice::ReadGroup | QFileDevice::WriteGroup | QFileDevice::ExeGroup
                                         | QFileDevice::ReadOther | QFileDevice::WriteOther | QFileDevice::ExeOther)) {
                    qDebug() << "[FolderChecker] WARNING , can not change permissions " << path ;
                }
            }
            return true;
        }
    }
    qDebug() << "[FolderChecker] dir: " << path << "exsits, checking if it is writable.";

    QFileInfo fi(path);
    if (!fi.isWritable()) {
        qDebug() << "[FolderChecker]  INFO: folder %1 is not writeable" << path ;
        return false;
    }
    qDebug() << "[FolderChecker] INFO: folder %1 is writeable" << path ;
    return true;
}

void HistoryData::insertMetadata(QString path,int size,int duration,QString created){
    qDebug() << Q_FUNC_INFO << "insertMetadata" << endl;
    QSqlQuery query(myConnection);
    QString q = "insert into files(id, path, size, duration, created)"
            "values(NULL, '%1', '%2', %3, '%4')";

    if (!query.exec(q.arg(path).arg(size).arg(duration).arg(created))) {
        qDebug() << Q_FUNC_INFO << "新增录音记录失败,error:" << query.lastError();
    }
}

void HistoryData::removeMetadata(QString path) {
    qDebug() << Q_FUNC_INFO << "removeMetadata" << endl;

    QSqlQuery query(myConnection);
    QString q = "delete from files where path = '%1'";

    if (!query.exec(q.arg(path))) {
        qDebug() << Q_FUNC_INFO << "删除录音记录失败,error:" << query.lastError();
    }
}

void HistoryData::updateMetadata(QString path,int size,int duration){
    qDebug() << Q_FUNC_INFO << "updateDuration" << endl;

    QSqlQuery query(myConnection);
    query.prepare("update files set duration = ?,size = ? where path = ?");
    query.addBindValue(ceil(duration/1000));
    query.addBindValue(size);
    query.addBindValue(path);
    query.exec();
}

QJsonArray HistoryData::selectMetadata() {
    qDebug() << Q_FUNC_INFO << "selectMetadata" << endl;

    QJsonArray jsonArr;
    QSqlQuery query(myConnection);
    QString q = "select * from files order by created desc";

    QString path = "";
    if (!query.exec(q)) {//查询所有录音文件失败处理
        qDebug() << "查询录音列表失败" << query.lastError();
//        emit failed(callBackID, 500, "查询录音列表失败");
    }

    while (query.next()) {//循环录音列表
        path = query.value("path").toString();

        if(!path.isEmpty() && !QFile::exists(path)) {//删除数据库中不存在录音记录
            qDebug() << "删除数据库中不存在录音记录,path:" << path  << endl;
            removeMetadata(path);
        }else{
            QJsonObject jsonObj;
            jsonObj.insert("id", query.value("id").toString());

            QStringList list = query.value("path").toString().split("/");
            QString fileName = list.at(list.count()-1);

            qDebug() << "-----fileName:" << fileName  << endl;
            jsonObj.insert("fileName", fileName);
            jsonObj.insert("path", query.value("path").toString());
            jsonObj.insert("size", query.value("size").toInt());
            jsonObj.insert("duration", formatTime(1000*query.value("duration").toInt()));
            jsonObj.insert("created", query.value("created").toString());
            jsonArr.append(jsonObj);
        }
    }

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

    qDebug() << Q_FUNC_INFO << "hours" << hours << "mins" << mins << "secs" << secs << endl;
    qDebug() << Q_FUNC_INFO << "hoursStr" << hoursStr << "minsStr" << minsStr << "secsStr" << secsStr << endl;
    return hoursStr + ":" + minsStr + ":" + secsStr;
}
