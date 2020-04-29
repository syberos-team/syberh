#ifndef STORAGE_GLOBAL_H
#define STORAGE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(STORAGE_LIBRARY)
#  define STORAGESHARED_EXPORT Q_DECL_EXPORT
#else
#  define STORAGESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // STORAGE_GLOBAL_H
