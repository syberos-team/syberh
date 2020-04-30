#ifndef UPLOAD_GLOBAL_H
#define UPLOAD_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(UPLOAD_LIBRARY)
#  define UPLOADSHARED_EXPORT Q_DECL_EXPORT
#else
#  define UPLOADSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // UPLOAD_GLOBAL_H
