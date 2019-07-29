/****************************************************************************
** Meta object code from reading C++ file 'networkstatus.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../sybero-template/framework/common/networkstatus.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'networkstatus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NetworkStatus_t {
    QByteArrayData data[9];
    char stringdata0[137];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NetworkStatus_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NetworkStatus_t qt_meta_stringdata_NetworkStatus = {
    {
QT_MOC_LITERAL(0, 0, 13), // "NetworkStatus"
QT_MOC_LITERAL(1, 14, 21), // "networkConnectChanged"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 11), // "networkType"
QT_MOC_LITERAL(4, 49, 24), // "slotNetworkStatusChanged"
QT_MOC_LITERAL(5, 74, 4), // "flag"
QT_MOC_LITERAL(6, 79, 28), // "CNetworkManager::NetworkType"
QT_MOC_LITERAL(7, 108, 4), // "type"
QT_MOC_LITERAL(8, 113, 23) // "getNetworkConnectStatus"

    },
    "NetworkStatus\0networkConnectChanged\0"
    "\0networkType\0slotNetworkStatusChanged\0"
    "flag\0CNetworkManager::NetworkType\0"
    "type\0getNetworkConnectStatus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NetworkStatus[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    2,   32,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
       8,    0,   37,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 6,    5,    7,

 // methods: parameters
    QMetaType::QString,

       0        // eod
};

void NetworkStatus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NetworkStatus *_t = static_cast<NetworkStatus *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->networkConnectChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->slotNetworkStatusChanged((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< CNetworkManager::NetworkType(*)>(_a[2]))); break;
        case 2: { QString _r = _t->getNetworkConnectStatus();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (NetworkStatus::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NetworkStatus::networkConnectChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject NetworkStatus::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_NetworkStatus.data,
      qt_meta_data_NetworkStatus,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NetworkStatus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetworkStatus::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NetworkStatus.stringdata0))
        return static_cast<void*>(const_cast< NetworkStatus*>(this));
    return QObject::qt_metacast(_clname);
}

int NetworkStatus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void NetworkStatus::networkConnectChanged(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
