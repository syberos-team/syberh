/****************************************************************************
** Meta object code from reading C++ file 'helper.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../sybero-template/com/syberos/download/src/helper.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'helper.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Helper_t {
    QByteArrayData data[17];
    char stringdata0[214];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Helper_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Helper_t qt_meta_stringdata_Helper = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Helper"
QT_MOC_LITERAL(1, 7, 7), // "success"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 2), // "id"
QT_MOC_LITERAL(4, 19, 4), // "json"
QT_MOC_LITERAL(5, 24, 16), // "saveDownloadFile"
QT_MOC_LITERAL(6, 41, 3), // "url"
QT_MOC_LITERAL(7, 45, 5), // "bytes"
QT_MOC_LITERAL(8, 51, 18), // "downloadFileFailed"
QT_MOC_LITERAL(9, 70, 27), // "QNetworkReply::NetworkError"
QT_MOC_LITERAL(10, 98, 9), // "errorCode"
QT_MOC_LITERAL(11, 108, 12), // "errorMessage"
QT_MOC_LITERAL(12, 121, 14), // "getWebRootPath"
QT_MOC_LITERAL(13, 136, 15), // "getDataRootPath"
QT_MOC_LITERAL(14, 152, 24), // "getExternStorageRootPath"
QT_MOC_LITERAL(15, 177, 23), // "getInnerStorageRootPath"
QT_MOC_LITERAL(16, 201, 12) // "downloadFile"

    },
    "Helper\0success\0\0id\0json\0saveDownloadFile\0"
    "url\0bytes\0downloadFileFailed\0"
    "QNetworkReply::NetworkError\0errorCode\0"
    "errorMessage\0getWebRootPath\0getDataRootPath\0"
    "getExternStorageRootPath\0"
    "getInnerStorageRootPath\0downloadFile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Helper[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   59,    2, 0x0a /* Public */,
       8,    2,   64,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      12,    0,   69,    2, 0x02 /* Public */,
      13,    0,   70,    2, 0x02 /* Public */,
      14,    0,   71,    2, 0x02 /* Public */,
      15,    0,   72,    2, 0x02 /* Public */,
      16,    2,   73,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,    6,    7,
    QMetaType::Void, 0x80000000 | 9, QMetaType::QString,   10,   11,

 // methods: parameters
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    6,

       0        // eod
};

void Helper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Helper *_t = static_cast<Helper *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->success((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->saveDownloadFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 2: _t->downloadFileFailed((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: { QString _r = _t->getWebRootPath();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 4: { QString _r = _t->getDataRootPath();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 5: { QString _r = _t->getExternStorageRootPath();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 6: { QString _r = _t->getInnerStorageRootPath();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 7: _t->downloadFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply::NetworkError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Helper::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Helper::success)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Helper::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Helper.data,
      qt_meta_data_Helper,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Helper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Helper::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Helper.stringdata0))
        return static_cast<void*>(const_cast< Helper*>(this));
    return QObject::qt_metacast(_clname);
}

int Helper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Helper::success(QString _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
