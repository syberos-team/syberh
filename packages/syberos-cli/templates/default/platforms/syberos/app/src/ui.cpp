#include "ui.h"
#include <QDebug>
//#include <cenvironment.h>
#include <qcompilerdetection.h>

Ui::Ui(QObject *parent) : QObject(parent) {

}

void Ui::button(){
    qDebug() << Q_FUNC_INFO << endl;

}

