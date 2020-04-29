#include "qtcassert.h"

#include <QByteArray>

namespace Utils {

void writeAssertLocation(const char *msg)
{
    static bool goBoom = qEnvironmentVariableIsSet("QTC_FATAL_ASSERTS");
    if (goBoom)
        qFatal("SOFT ASSERT made fatal: %s", msg);
    else
        qDebug("SOFT ASSERT: %s", msg);
}

} // namespace Utils
