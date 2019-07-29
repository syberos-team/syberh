#ifndef GLOBALOBJECT_H
#define GLOBALOBJECT_H

#include "helper.h"
#include "ui.h"
#include <QObject>


class GlobalObject : public QObject
{
    Q_OBJECT

public:
    explicit GlobalObject(QObject *parent = 0);
    static GlobalObject* instance();

    Q_INVOKABLE QObject* getHelper();

    Q_INVOKABLE QObject* getUi();

signals:
    void success(QString id, QString json);

public slots:
    void invokeSuccess(QString id, QString json);

private:
    Helper *helper;
    Ui *ui;
};

#endif // GLOBALOBJECT_H
