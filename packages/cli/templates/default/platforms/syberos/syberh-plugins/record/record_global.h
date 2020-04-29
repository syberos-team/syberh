#ifndef RECORD_GLOBAL_H
#define RECORD_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(RECORD_LIBRARY)
#  define RECORDSHARED_EXPORT Q_DECL_EXPORT
#else
#  define RECORDSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // RECORD_GLOBAL_H
