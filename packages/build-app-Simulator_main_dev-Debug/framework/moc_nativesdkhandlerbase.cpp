/****************************************************************************
** Meta object code from reading C++ file 'nativesdkhandlerbase.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../sybero-template/framework/nativesdkhandlerbase.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nativesdkhandlerbase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NativeSdkHandlerBase_t {
    QByteArrayData data[11];
    char stringdata0[101];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NativeSdkHandlerBase_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NativeSdkHandlerBase_t qt_meta_stringdata_NativeSdkHandlerBase = {
    {
QT_MOC_LITERAL(0, 0, 20), // "NativeSdkHandlerBase"
QT_MOC_LITERAL(1, 21, 6), // "sucess"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 10), // "responseID"
QT_MOC_LITERAL(4, 40, 6), // "result"
QT_MOC_LITERAL(5, 47, 6), // "failed"
QT_MOC_LITERAL(6, 54, 9), // "errorCode"
QT_MOC_LITERAL(7, 64, 8), // "errorMsg"
QT_MOC_LITERAL(8, 73, 8), // "progress"
QT_MOC_LITERAL(9, 82, 11), // "totalLength"
QT_MOC_LITERAL(10, 94, 6) // "status"

    },
    "NativeSdkHandlerBase\0sucess\0\0responseID\0"
    "result\0failed\0errorCode\0errorMsg\0"
    "progress\0totalLength\0status"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NativeSdkHandlerBase[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,
       5,    3,   34,    2, 0x06 /* Public */,
       8,    4,   41,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Long, QMetaType::QVariant,    3,    4,
    QMetaType::Void, QMetaType::Long, QMetaType::Long, QMetaType::QString,    3,    6,    7,
    QMetaType::Void, QMetaType::Long, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    9,    8,   10,

       0        // eod
};

void NativeSdkHandlerBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NativeSdkHandlerBase *_t = static_cast<NativeSdkHandlerBase *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sucess((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 1: _t->failed((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 2: _t->progress((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (NativeSdkHandlerBase::*_t)(long , QVariant );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NativeSdkHandlerBase::sucess)) {
                *result = 0;
            }
        }
        {
            typedef void (NativeSdkHandlerBase::*_t)(long , long , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NativeSdkHandlerBase::failed)) {
                *result = 1;
            }
        }
        {
            typedef void (NativeSdkHandlerBase::*_t)(long , const int , const int , const int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NativeSdkHandlerBase::progress)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject NativeSdkHandlerBase::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_NativeSdkHandlerBase.data,
      qt_meta_data_NativeSdkHandlerBase,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NativeSdkHandlerBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NativeSdkHandlerBase::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NativeSdkHandlerBase.stringdata0))
        return static_cast<void*>(const_cast< NativeSdkHandlerBase*>(this));
    return QObject::qt_metacast(_clname);
}

int NativeSdkHandlerBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void NativeSdkHandlerBase::sucess(long _t1, QVariant _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NativeSdkHandlerBase::failed(long _t1, long _t2, QString _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void NativeSdkHandlerBase::progress(long _t1, const int _t2, const int _t3, const int _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
