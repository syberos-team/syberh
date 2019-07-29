#ifndef UI_H
#define UI_H

#include <QObject>

class Ui : public QObject {
    Q_OBJECT
public:
    explicit Ui(QObject *parent = 0);

    Q_INVOKABLE void button();
signals:

public slots:
};

#endif // UI_H
