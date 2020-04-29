#ifndef BATTERY_GLOBAL_H
#define BATTERY_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BATTERY_LIBRARY)
#  define BATTERYSHARED_EXPORT Q_DECL_EXPORT
#else
#  define BATTERYSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // BATTERY_GLOBAL_H
