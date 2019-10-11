#ifndef CHALK_H
#define CHALK_H
#include <QString>
#include <QObject>

class Chalk: public QObject
{
    Q_OBJECT
public:
    /**
     *绿色打印输入结果
     *@param str 打印内容
     *@param className类名 默认为空
     *@param method 方法名 默认为空
     */
    static void green(QString &str,QString className="",QString method="");
private:
    Chalk(QObject *parent = 0);
};

#endif // CHALK_H
