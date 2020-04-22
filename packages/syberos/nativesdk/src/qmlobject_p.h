#ifndef QMLOBJECT_P_H
#define QMLOBJECT_P_H

#include "qmlobject.h"
#include <QQuickItem>

namespace NativeSdk {

namespace Internal {

class QmlObjectPrivate : public QObject {
    Q_OBJECT
public:
    explicit QmlObjectPrivate(QObject *parent = 0);

    QQuickItem *qmlItem;
    QQuickItem *parentItem;

    QmlObject::Status status;
    QString errorMessage;
};

} // namespace Internal
} // namesapce NativeSdk
#endif // QMLOBJECT_P_H
