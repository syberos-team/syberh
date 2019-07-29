/****************************************************************************
** Meta object code from reading C++ file 'nativesdkmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../sybero-template/framework/nativesdkmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nativesdkmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NativeSdkManager_t {
    QByteArrayData data[21];
    char stringdata0[196];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NativeSdkManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NativeSdkManager_t qt_meta_stringdata_NativeSdkManager = {
    {
QT_MOC_LITERAL(0, 0, 16), // "NativeSdkManager"
QT_MOC_LITERAL(1, 17, 6), // "sucess"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 10), // "responseID"
QT_MOC_LITERAL(4, 36, 6), // "result"
QT_MOC_LITERAL(5, 43, 6), // "failed"
QT_MOC_LITERAL(6, 50, 9), // "errorCode"
QT_MOC_LITERAL(7, 60, 8), // "errorMsg"
QT_MOC_LITERAL(8, 69, 8), // "progress"
QT_MOC_LITERAL(9, 78, 11), // "totalLength"
QT_MOC_LITERAL(10, 90, 6), // "status"
QT_MOC_LITERAL(11, 97, 7), // "request"
QT_MOC_LITERAL(12, 105, 6), // "typeID"
QT_MOC_LITERAL(13, 112, 10), // "callBackID"
QT_MOC_LITERAL(14, 123, 10), // "actionName"
QT_MOC_LITERAL(15, 134, 6), // "params"
QT_MOC_LITERAL(16, 141, 6), // "submit"
QT_MOC_LITERAL(17, 148, 11), // "dataRowList"
QT_MOC_LITERAL(18, 160, 13), // "attachementes"
QT_MOC_LITERAL(19, 174, 11), // "getUiSource"
QT_MOC_LITERAL(20, 186, 9) // "className"

    },
    "NativeSdkManager\0sucess\0\0responseID\0"
    "result\0failed\0errorCode\0errorMsg\0"
    "progress\0totalLength\0status\0request\0"
    "typeID\0callBackID\0actionName\0params\0"
    "submit\0dataRowList\0attachementes\0"
    "getUiSource\0className"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NativeSdkManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,
       5,    3,   49,    2, 0x06 /* Public */,
       8,    4,   56,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
      11,    4,   65,    2, 0x02 /* Public */,
      16,    5,   74,    2, 0x02 /* Public */,
      19,    2,   85,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Long, QMetaType::QVariant,    3,    4,
    QMetaType::Void, QMetaType::Long, QMetaType::Long, QMetaType::QString,    3,    6,    7,
    QMetaType::Void, QMetaType::Long, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    9,    8,   10,

 // methods: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QVariantMap,   12,   13,   14,   15,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QVariant, QMetaType::QVariant,   12,   13,   14,   17,   18,
    QMetaType::QObjectStar, QMetaType::QString, QMetaType::QString,   20,   14,

       0        // eod
};

void NativeSdkManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NativeSdkManager *_t = static_cast<NativeSdkManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sucess((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 1: _t->failed((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 2: _t->progress((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4]))); break;
        case 3: _t->request((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QVariantMap(*)>(_a[4]))); break;
        case 4: _t->submit((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QVariant(*)>(_a[4])),(*reinterpret_cast< QVariant(*)>(_a[5]))); break;
        case 5: { QObject* _r = _t->getUiSource((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QObject**>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (NativeSdkManager::*_t)(long , QVariant );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NativeSdkManager::sucess)) {
                *result = 0;
            }
        }
        {
            typedef void (NativeSdkManager::*_t)(long , long , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NativeSdkManager::failed)) {
                *result = 1;
            }
        }
        {
            typedef void (NativeSdkManager::*_t)(long , const int , const int , const int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NativeSdkManager::progress)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject NativeSdkManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_NativeSdkManager.data,
      qt_meta_data_NativeSdkManager,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NativeSdkManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NativeSdkManager::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NativeSdkManager.stringdata0))
        return static_cast<void*>(const_cast< NativeSdkManager*>(this));
    return QObject::qt_metacast(_clname);
}

int NativeSdkManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void NativeSdkManager::sucess(long _t1, QVariant _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NativeSdkManager::failed(long _t1, long _t2, QString _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void NativeSdkManager::progress(long _t1, const int _t2, const int _t3, const int _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
