#include "globalobject.h"
#include "helper.h"
#include <QObject>
#include <QDebug>
#include <QTextCodec>


GlobalObject::GlobalObject(QObject *parent) : QObject(parent) {
    helper = Helper::instance();
    ui = new Ui(this);

    connect(Helper::instance(), SIGNAL(success(QString,QString)), this, SLOT(invokeSuccess(QString,QString)));
}

GlobalObject* GlobalObject::instance(){
    static GlobalObject global;
    return &global;
}

QObject* GlobalObject::getHelper(){
    return helper;
}

QObject* GlobalObject::getUi(){
    return ui;
}


void GlobalObject::invokeSuccess(QString id, QString json){
    qDebug() << Q_FUNC_INFO << "id:" << id << "json: " << json << endl;
    emit success(id, json);
}
