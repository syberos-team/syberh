#ifndef QRCODE_GLOBAL_H
#define QRCODE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QRCODE_LIBRARY)
#  define QRCODESHARED_EXPORT Q_DECL_EXPORT
#else
#  define QRCODESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QRCODE_GLOBAL_H
