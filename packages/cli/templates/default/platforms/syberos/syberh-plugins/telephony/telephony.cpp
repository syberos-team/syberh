#include "telephony.h"
#include <cgui_application.h>
#include "framework/common/errorinfo.h"

// 必须用这个命令空间下的qApp才可以
using namespace SYBEROS;
using namespace NativeSdk;


Telephony::Telephony()
{
}


void Telephony::invoke(QString callbackID, QString actionName, QVariantMap params)
{
    qDebug() << Q_FUNC_INFO << "  callbackID:" << callbackID << "actionName:" << actionName << "params:" << params;

    Q_UNUSED(actionName);
    
    if (actionName == "dial") {
        QString tel = params.value("tel").toString();
        qApp->openUrl("dial://showdialpage?" + tel);
        signalManager()->success(callbackID.toLong(), "");
    } else {
        signalManager()->failed(callbackID.toLong(), ErrorInfo::InvalidCall, ErrorInfo::message(ErrorInfo::InvalidCall, "方法不存在"));
    }
}
