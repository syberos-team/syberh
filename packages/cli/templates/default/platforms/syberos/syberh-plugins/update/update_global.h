#ifndef UPDATE_GLOBAL_H
#define UPDATE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(UPDATE_LIBRARY)
#  define UPDATESHARED_EXPORT Q_DECL_EXPORT
#else
#  define UPDATESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // UPDATE_GLOBAL_H
