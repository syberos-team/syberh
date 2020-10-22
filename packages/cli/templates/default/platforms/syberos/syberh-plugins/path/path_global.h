#ifndef PATH_GLOBAL_H
#define PATH_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PATH_LIBRARY)
#  define PATHSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PATHSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PATH_GLOBAL_H
