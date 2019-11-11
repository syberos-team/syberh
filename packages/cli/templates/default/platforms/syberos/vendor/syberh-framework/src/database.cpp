#include "database.h"
#include "helper.h"

#include <QtSql>
#include <QObject>
#include <QDebug>
#include <QException>
#include "framework/common/errorinfo.h"

int Database::typeId = qRegisterMetaType<Database *>();

Database::Database(){}
Database::~Database(){}

void Database::request(QString callBackID, QString actionName, QVariantMap params){
  if (actionName == "createTable"){
      createTable(callBackID.toLong(), params);
  }else if (actionName == "query"){
      query(callBackID.toLong(), params);
  }else if (actionName == "execute"){
      execute(callBackID.toLong(), params);
  }else if (actionName == "isDatabaseExists"){
      isDatabaseExists(callBackID.toLong(), params);
  }else if (actionName == "isTableExists"){
      isTableExists(callBackID.toLong(), params);
  }
}

void Database::submit(QString typeID, QString callBackID, QString actionName, QVariant dataRowList, QVariant attachementes){
    Q_UNUSED(typeID)
    Q_UNUSED(callBackID)
    Q_UNUSED(actionName)
    Q_UNUSED(dataRowList)
    Q_UNUSED(attachementes)
}

void Database::createTable(long callBackID, QVariantMap params){
    qDebug() << Q_FUNC_INFO << "createTable" << params << endl;
    QString databaseName = params.value("databaseName").toString();//数据库名
    QString sql = params.value("sql").toString();//创建表sql
    QString sqlindex = params.value("sqlindex").toString();//创建索引sql

    if(databaseName.isEmpty()){
        qDebug() << Q_FUNC_INFO << "数据库名不能为空" << endl;
        emit failed(callBackID, ErrorInfo::InvalidParameter, "不合法的参数:数据库名不能为空");
        return;
    }
    if(sql.isEmpty()){
        qDebug() << Q_FUNC_INFO << "sql不能为空" << endl;
        emit failed(callBackID, ErrorInfo::InvalidParameter, "不合法的参数:sql不能为空");
        return;
    }

    //连接数据库
    myConnection = QSqlDatabase::addDatabase("QSQLITE");
    QString dataDir = Helper::instance()->getDataRootPath();
    QDir d(dataDir);
    if (!d.exists()) {
        qDebug() << Q_FUNC_INFO << "目录不存在" << endl;
        checkOrCreateDir(dataDir);
    }
    QString dbPath = dataDir + "/" + databaseName+".sqlite";
    qDebug() << Q_FUNC_INFO << "数据库路径 = " << dbPath << endl;

    myConnection.setDatabaseName(dbPath);

    //打开数据库
    bool isOK = myConnection.open();
    if (!isOK) {
        qDebug() << Q_FUNC_INFO << "打开数据库失败" << endl;
        emit failed(callBackID, ErrorInfo::databaseError, "数据库错误:打开数据库失败");
        return;
    }

    //执行创建表sql
    QSqlQuery query(myConnection);
    if (! query.exec(sql)) {
        qDebug() << Q_FUNC_INFO << "执行sql失败:" << query.lastError();
        emit failed(callBackID, ErrorInfo::databaseError, "数据库错误:创建表失败");
        myConnection.close();
        return;
     }

     if(!databaseName.isEmpty()){
        //执行创建索引sql
        if (! query.exec(sqlindex)) {
            qDebug() << Q_FUNC_INFO << "执行sql失败:" << query.lastError();
            emit failed(callBackID, ErrorInfo::databaseError, "数据库错误:创建索引失败");
            myConnection.close();
            return;
        }
    }
    //关闭数据库
    myConnection.close();
    qDebug() << Q_FUNC_INFO << "createTable:result" << true << endl;
    emit success(callBackID, true);
}

void Database::query(long callBackID, QVariantMap params){
    qDebug() << Q_FUNC_INFO << "selectOperate" << params << endl;
    QString databaseName = params.value("databaseName").toString();//数据库名
    QString sqlQuery = params.value("sql").toString();

    if(databaseName.isEmpty()){
        qDebug() << Q_FUNC_INFO << "数据库名不能为空" << endl;
        emit failed(callBackID, ErrorInfo::InvalidParameter, "不合法的参数:数据库名不能为空");
        return;
    }
    if(sqlQuery.isEmpty()){
        qDebug() << Q_FUNC_INFO << "sql不能为空" << endl;
        emit failed(callBackID, ErrorInfo::InvalidParameter, "不合法的参数:sql不能为空");
        return;
    }

    myConnection = QSqlDatabase::addDatabase("QSQLITE");
    QString dataDir = Helper::instance()->getDataRootPath();
    QString dbPath = dataDir + "/" + databaseName+".sqlite";
    myConnection.setDatabaseName(dbPath);
    bool isOK = myConnection.open();
    if (!isOK) {
        qDebug() << Q_FUNC_INFO << "打开数据库失败" << endl;
        emit failed(callBackID, ErrorInfo::databaseError, "数据库错误:打开数据库失败");
        return;
    }

    QSqlQuery query(myConnection);
    if (!query.exec(sqlQuery)) {
        qDebug() << Q_FUNC_INFO << "查询数据失败,error:" << query.lastError();
        emit failed(callBackID, ErrorInfo::databaseError, "数据库错误:查询数据失败");
        myConnection.close();
        return;
    }

    QJsonArray jsonArr;
    QSqlRecord rec;
    while(query.next()) {
        QJsonObject jsonObj;
        rec = query.record();
        for(int i = 0 ; i<rec.count(); ++i){
            jsonObj.insert(rec.fieldName(i), QJsonValue::fromVariant(rec.value(i)));
        }
        jsonArr.append(jsonObj);
    }

    myConnection.close();
    qDebug() << Q_FUNC_INFO << "selectOperate:jsonArr" << jsonArr << endl;
    emit success(callBackID, QVariant(jsonArr));
}



void Database::execute(long callBackID, QVariantMap params){
    qDebug() << Q_FUNC_INFO << "selectOperate" << params << endl;
    QString databaseName = params.value("databaseName").toString();//数据库名
    QString sqlQuery = params.value("sql").toString();

    if(databaseName.isEmpty()){
        qDebug() << Q_FUNC_INFO << "数据库名不能为空" << endl;
        emit failed(callBackID, ErrorInfo::InvalidParameter, "不合法的参数:数据库名不能为空");
        return;
    }
    if(sqlQuery.isEmpty()){
        qDebug() << Q_FUNC_INFO << "sql不能为空" << endl;
        emit failed(callBackID, ErrorInfo::InvalidParameter, "不合法的参数:sql不能为空");
        return;
    }

    myConnection = QSqlDatabase::addDatabase("QSQLITE");
    QString dataDir = Helper::instance()->getDataRootPath();
    QString dbPath = dataDir + "/" + databaseName+".sqlite";
    myConnection.setDatabaseName(dbPath);

    bool isOK = myConnection.open();
    if (!isOK) {
        qDebug() << Q_FUNC_INFO << "打开数据库失败" << endl;
        emit failed(callBackID, ErrorInfo::databaseError, "数据库错误:打开数据库失败");
        return;
    }

    QSqlQuery query(myConnection);
    if (!query.exec(sqlQuery)) {
        qDebug() << Q_FUNC_INFO << "操作失败,error:" << query.lastError();
        emit failed(callBackID, ErrorInfo::databaseError, "数据库错误:操作失败");
        myConnection.close();
        return;
    }

    myConnection.close();
    qDebug() << Q_FUNC_INFO << "execOperate:result" << true << endl;
    emit success(callBackID, true);
}

void Database::isDatabaseExists(long callBackID, QVariantMap params){
    qDebug() << Q_FUNC_INFO << "isDataExists" << params << endl;
    QString databaseName = params.value("databaseName").toString();//数据库名

    if(databaseName.isEmpty()){
        qDebug() << Q_FUNC_INFO << "数据库名不能为空" << endl;
        emit failed(callBackID, ErrorInfo::InvalidParameter, "不合法的参数:数据库名不能为空");
        return;
    }
    QString dataDir = Helper::instance()->getDataRootPath();
    QString dbPath = dataDir + "/" + databaseName+".sqlite";
    qDebug() << Q_FUNC_INFO << "dbPath" << dbPath << endl;

    //判断数据库是否存在
    QFile file(dbPath);
    if(!file.exists()){
        qDebug() << Q_FUNC_INFO << "数据库不存在" << endl;
        emit failed(callBackID, ErrorInfo::databaseError, "数据库错误:数据库不存在");
        return;
    }

    qDebug() << Q_FUNC_INFO << "isDataExists:result" << true << endl;
    emit success(callBackID, true);
}

void Database::isTableExists(long callBackID, QVariantMap params){
    qDebug() << Q_FUNC_INFO << "isTableExists" << params << endl;
    QString tableName = params.value("tableName").toString();
    QString databaseName = params.value("databaseName").toString();//数据库名

    if(databaseName.isEmpty()){
        qDebug() << Q_FUNC_INFO << "数据库名不能为空" << endl;
        emit failed(callBackID, ErrorInfo::InvalidParameter, "不合法的参数:数据库名不能为空");
        return;
    }
    if(tableName.isEmpty()){
        qDebug() << Q_FUNC_INFO << "表名不能为空" << endl;
        emit failed(callBackID, ErrorInfo::InvalidParameter, "不合法的参数:表名不能为空");
        return;
    }

    myConnection = QSqlDatabase::addDatabase("QSQLITE");
    QString dataDir = Helper::instance()->getDataRootPath();
    QString dbPath = dataDir + "/" + databaseName+".sqlite";
    myConnection.setDatabaseName(dbPath);

    bool isOK = myConnection.open();
    if (!isOK) {
        qDebug() << Q_FUNC_INFO << "打开数据库失败" << endl;
        emit failed(callBackID, ErrorInfo::databaseError, "数据库错误:打开数据库失败");
        return;
    }

    QSqlQuery query(myConnection);
    //判断表是否存在
    QString sqlQuery = "select * from datas order by created desc";
    if (!query.exec(sqlQuery)) {
        qDebug() << Q_FUNC_INFO << "表不存在,error:" << query.lastError();
        emit failed(callBackID, ErrorInfo::databaseError, "数据库错误:表不存在");
        myConnection.close();
        return;
    }

    myConnection.close();
    qDebug() << Q_FUNC_INFO << "isTableExists:result" << true << endl;
    emit success(callBackID, true);
}

bool Database::checkOrCreateDir(QString path){
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

