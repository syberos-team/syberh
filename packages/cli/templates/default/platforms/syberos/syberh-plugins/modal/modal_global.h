#ifndef MODAL_GLOBAL_H
#define MODAL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MODAL_LIBRARY)
#  define MODALSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MODALSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MODAL_GLOBAL_H
