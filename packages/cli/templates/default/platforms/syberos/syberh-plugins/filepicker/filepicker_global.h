#ifndef FILEPICKER_GLOBAL_H
#define FILEPICKER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FILEPICKER_LIBRARY)
#  define FILEPICKERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define FILEPICKERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // FILEPICKER_GLOBAL_H
