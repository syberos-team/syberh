#include "hostosinfo.h"

#include <QCoreApplication>

#if !defined(QT_NO_OPENGL) && defined(QT_GUI_LIB)
#include <QOpenGLContext>
#endif

#ifdef Q_OS_WIN
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0501 /* WinXP, needed for GetNativeSystemInfo() */
#include <qt_windows.h>
#endif

using namespace Utils;

Qt::CaseSensitivity HostOsInfo::m_overrideFileNameCaseSensitivity = Qt::CaseSensitive;
bool HostOsInfo::m_useOverrideFileNameCaseSensitivity = false;

#ifdef Q_OS_WIN
static WORD hostProcessorArchitecture()
{
    SYSTEM_INFO info;
    GetNativeSystemInfo(&info);
    return info.wProcessorArchitecture;
}
#endif

HostOsInfo::HostArchitecture HostOsInfo::hostArchitecture()
{
#ifdef Q_OS_WIN
    static const WORD processorArchitecture = hostProcessorArchitecture();
    switch (processorArchitecture) {
    case PROCESSOR_ARCHITECTURE_AMD64:
        return HostOsInfo::HostArchitectureAMD64;
    case PROCESSOR_ARCHITECTURE_INTEL:
        return HostOsInfo::HostArchitectureX86;
    case PROCESSOR_ARCHITECTURE_IA64:
        return HostOsInfo::HostArchitectureItanium;
    case PROCESSOR_ARCHITECTURE_ARM:
        return HostOsInfo::HostArchitectureArm;
    default:
        return HostOsInfo::HostArchitectureUnknown;
    }
#else
    return HostOsInfo::HostArchitectureUnknown;
#endif
}

void HostOsInfo::setOverrideFileNameCaseSensitivity(Qt::CaseSensitivity sensitivity)
{
    m_useOverrideFileNameCaseSensitivity = true;
    m_overrideFileNameCaseSensitivity = sensitivity;
}

void HostOsInfo::unsetOverrideFileNameCaseSensitivity()
{
    m_useOverrideFileNameCaseSensitivity = false;
}

bool HostOsInfo::canCreateOpenGLContext(QString *errorMessage)
{
#if defined(QT_NO_OPENGL) || !defined(QT_GUI_LIB)
    Q_UNUSED(errorMessage)
    return false;
#else
    static const bool canCreate = QOpenGLContext().create();
    if (!canCreate)
        *errorMessage = QCoreApplication::translate("Utils::HostOsInfo",
                                                    "Cannot create OpenGL context.");
    return canCreate;
#endif
}

