#ifndef SYSTEM_GLOBAL_H
#define SYSTEM_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SYSTEM_LIBRARY)
#  define SYSTEMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SYSTEMSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SYSTEM_GLOBAL_H
