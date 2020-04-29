#ifndef UTILS_GLOBAL_H
#define UTILS_GLOBAL_H

#include <qglobal.h>

#if defined(UTILS_LIBRARY)
#  define QTCREATOR_UTILS_EXPORT Q_DECL_EXPORT
#elif  defined(QTCREATOR_UTILS_STATIC_LIB) // Abuse single files for manual tests
#  define QTCREATOR_UTILS_EXPORT
#else
#  define QTCREATOR_UTILS_EXPORT Q_DECL_IMPORT
#endif

#endif // UTILS_GLOBAL_H
