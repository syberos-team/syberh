#ifndef APP_GLOBAL_H
#define APP_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(APP_LIBRARY)
#  define APPSHARED_EXPORT Q_DECL_EXPORT
#else
#  define APPSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // APP_GLOBAL_H
