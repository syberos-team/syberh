#ifndef PACKAGE_GLOBAL_H
#define PACKAGE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PACKAGE_LIBRARY)
#  define PACKAGESHARED_EXPORT Q_DECL_EXPORT
#else
#  define PACKAGESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PACKAGE_GLOBAL_H
