#ifndef LOADQMLHANDLER_H
#define LOADQMLHANDLER_H

#include <QObject>
#include "framework/nativesdkhandlerbase.h"
class LoadQmlHandler : public NativeSdkHandlerBase{
    Q_OBJECT
public:
    Q_INVOKABLE LoadQmlHandler();
    ~LoadQmlHandler();
    void loadQml(QString parentPageName, QString parentName, QString type);
    static int typeId;
};

#endif // LOADQMLHANDLER_H
