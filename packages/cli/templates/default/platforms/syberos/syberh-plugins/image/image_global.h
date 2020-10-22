#ifndef IMAGE_GLOBAL_H
#define IMAGE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(IMAGE_LIBRARY)
#  define IMAGESHARED_EXPORT Q_DECL_EXPORT
#else
#  define IMAGESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // IMAGE_GLOBAL_H
