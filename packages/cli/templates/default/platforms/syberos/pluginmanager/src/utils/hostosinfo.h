#ifndef HOSTOSINFO_H
#define HOSTOSINFO_H

#include "osspecificaspects.h"

#include <QString>

#ifdef Q_OS_WIN
#define QTC_HOST_EXE_SUFFIX QTC_WIN_EXE_SUFFIX
#else
#define QTC_HOST_EXE_SUFFIX ""
#endif // Q_OS_WIN

namespace Utils {

class HostOsInfo
{
public:
    static constexpr OsType hostOs()
    {
#if defined(Q_OS_WIN)
        return OsTypeWindows;
#elif defined(Q_OS_LINUX)
        return OsTypeLinux;
#elif defined(Q_OS_MAC)
        return OsTypeMac;
#elif defined(Q_OS_UNIX)
        return OsTypeOtherUnix;
#else
        return OsTypeOther;
#endif
    }

    enum HostArchitecture { HostArchitectureX86, HostArchitectureAMD64, HostArchitectureItanium,
                            HostArchitectureArm, HostArchitectureUnknown };
    static HostArchitecture hostArchitecture();

    static constexpr bool isWindowsHost() { return hostOs() == OsTypeWindows; }
    static constexpr bool isLinuxHost() { return hostOs() == OsTypeLinux; }
    static constexpr bool isMacHost() { return hostOs() == OsTypeMac; }
    static constexpr bool isAnyUnixHost()
    {
#ifdef Q_OS_UNIX
        return true;
#else
        return false;
#endif
    }

    static QString withExecutableSuffix(const QString &executable)
    {
        return OsSpecificAspects::withExecutableSuffix(hostOs(), executable);
    }

    static void setOverrideFileNameCaseSensitivity(Qt::CaseSensitivity sensitivity);
    static void unsetOverrideFileNameCaseSensitivity();

    static Qt::CaseSensitivity fileNameCaseSensitivity()
    {
        return m_useOverrideFileNameCaseSensitivity
                ? m_overrideFileNameCaseSensitivity
                : OsSpecificAspects::fileNameCaseSensitivity(hostOs());
    }

    static QChar pathListSeparator()
    {
        return OsSpecificAspects::pathListSeparator(hostOs());
    }

    static Qt::KeyboardModifier controlModifier()
    {
        return OsSpecificAspects::controlModifier(hostOs());
    }

    static bool canCreateOpenGLContext(QString *errorMessage);

private:
    static Qt::CaseSensitivity m_overrideFileNameCaseSensitivity;
    static bool m_useOverrideFileNameCaseSensitivity;
};

} // namespace Utils

#endif // HOSTOSINFO_H
