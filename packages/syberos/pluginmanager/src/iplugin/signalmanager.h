#ifndef SIGNALMANAGER_H
#define SIGNALMANAGER_H

#include <QObject>
#include <QVariant>

namespace ExtensionSystem {

class SignalManager : public QObject {
    Q_OBJECT
public:
    ~SignalManager();

    static SignalManager *instance();

signals:
    void success(QString callbackID, QVariant result);
    void failed(QString callbackID, QString errorCode,QString errorMsg);
    void progress(QString callbackID, const int totalLength, const int progress, const int status);
    void subscribe(QString handleName, QVariant result);

private:
    SignalManager();
};



}
#endif // SIGNALMANAGER_H
