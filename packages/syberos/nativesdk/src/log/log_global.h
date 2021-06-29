#ifndef LOG_GLOBAL_H
#define LOG_GLOBAL_H

#include <QtGlobal>

#if defined(LOG_LIBRARY)
#  define LOG_EXPORT Q_DECL_EXPORT
#else
#  define LOG_EXPORT Q_DECL_IMPORT
#endif

#endif // LOG_GLOBAL_H
