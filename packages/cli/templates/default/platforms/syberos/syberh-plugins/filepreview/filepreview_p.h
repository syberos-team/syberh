#ifndef FILEPREVIEW_P_H
#define FILEPREVIEW_P_H

#include <QObject>
#include <QMap>

#include "iplugin/iplugin.h"
#include "qmlmanager.h"
#include "framework/common/errorinfo.h"

using namespace NativeSdk;

class FilePreviewPrivate : public QObject
{
    Q_OBJECT
public:
    FilePreviewPrivate(QObject *parent = 0);
    virtual ~FilePreviewPrivate();

    void reset();
    void previewTxt(QString &callbackID, QVariantMap &params);
    void previewVideo(QString &callbackID, QVariantMap &params);

    bool hasError() {return m_hasError;}
    ErrorInfo::ErrorCode error() {return m_errorCode;}
    QString errorString() {return m_errorString;}

public slots:
    void slotPreviewTxt();
    void slotPreviewVideo();

private:
    bool m_retried = false;
    QString m_callbackID;
    QVariantMap m_params;

    bool m_hasError = false;
    ErrorInfo::ErrorCode m_errorCode;
    QString m_errorString;

    void setError(ErrorInfo::ErrorCode errCode, const QString &errString);
    void cleanError();
};

#endif // FILEPREVIEW_P_H
