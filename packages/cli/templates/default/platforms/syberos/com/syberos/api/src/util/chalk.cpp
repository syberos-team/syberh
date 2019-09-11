#include "chalk.h"
#include <QDebug>
Chalk::Chalk(QObject *parent):QObject(parent){}

Chalk* Chalk::green(QString &str, QString className, QString method){
     qDebug()<<"\033[35m"<<className<<method<<"\033[0m\033[32m" << str <<"\033[0m"<<endl;
}
