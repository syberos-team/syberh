#ifndef NATIVESDK_UTIL_H
#define NATIVESDK_UTIL_H

#include <QString>
#include <QMap>
#include <QVariant>

namespace NativeSdk {

    namespace Util {
        
        /**
         * 比对两个字符串是否相等。caseInsensitive参数控制是否忽略大小写，默认区分大小写
         */
        inline bool Equals(const QString &a, const QString &b, bool caseInsensitive = false)
        {
            return (!a.isNull()) && a.compare(b, (caseInsensitive ? Qt::CaseInsensitive : Qt::CaseSensitive)) == 0;
        }

        inline bool CheckParam(const QVariantMap &params, const QString &paramName)
        {
            QVariant var = params.value(paramName);
            if(var.isNull() || !var.isValid()){
                return false;
            }
            return true;
        }

    }

}

#endif  //NATIVESDK_UTIL_H