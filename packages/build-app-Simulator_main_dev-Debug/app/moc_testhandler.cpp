/****************************************************************************
** Meta object code from reading C++ file 'testhandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../sybero-template/com/syberos/download/src/testhandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testhandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TestHandler_t {
    QByteArrayData data[7];
    char stringdata0[71];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TestHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TestHandler_t qt_meta_stringdata_TestHandler = {
    {
QT_MOC_LITERAL(0, 0, 11), // "TestHandler"
QT_MOC_LITERAL(1, 12, 14), // "downLoadFailed"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 10), // "downloadID"
QT_MOC_LITERAL(4, 39, 6), // "result"
QT_MOC_LITERAL(5, 46, 9), // "errorCode"
QT_MOC_LITERAL(6, 56, 14) // "downLoadSucess"

    },
    "TestHandler\0downLoadFailed\0\0downloadID\0"
    "result\0errorCode\0downLoadSucess"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TestHandler[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   37, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x0a /* Public */,
       6,    2,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Long, QMetaType::QString, QMetaType::Long,    3,    4,    5,
    QMetaType::Void, QMetaType::Long, QMetaType::QString,    3,    4,

 // constructors: parameters
    0x80000000 | 2,

 // constructors: name, argc, parameters, tag, flags
       0,    0,   36,    2, 0x0e /* Public */,

       0        // eod
};

void TestHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { TestHandler *_r = new TestHandler();
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        default: break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        TestHandler *_t = static_cast<TestHandler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->downLoadFailed((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< long(*)>(_a[3]))); break;
        case 1: _t->downLoadSucess((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject TestHandler::staticMetaObject = {
    { &NativeSdkHandlerBase::staticMetaObject, qt_meta_stringdata_TestHandler.data,
      qt_meta_data_TestHandler,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TestHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TestHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TestHandler.stringdata0))
        return static_cast<void*>(const_cast< TestHandler*>(this));
    return NativeSdkHandlerBase::qt_metacast(_clname);
}

int TestHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = NativeSdkHandlerBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
