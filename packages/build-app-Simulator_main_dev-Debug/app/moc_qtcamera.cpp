/****************************************************************************
** Meta object code from reading C++ file 'qtcamera.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../sybero-template/com/syberos/download/src/qtcamera.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtcamera.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QtCamera_t {
    QByteArrayData data[21];
    char stringdata0[281];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtCamera_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtCamera_t qt_meta_stringdata_QtCamera = {
    {
QT_MOC_LITERAL(0, 0, 8), // "QtCamera"
QT_MOC_LITERAL(1, 9, 18), // "mediaObjectChanged"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 10), // "savedImage"
QT_MOC_LITERAL(4, 40, 2), // "id"
QT_MOC_LITERAL(5, 43, 8), // "fileName"
QT_MOC_LITERAL(6, 52, 16), // "changeLockStatus"
QT_MOC_LITERAL(7, 69, 19), // "QCamera::LockStatus"
QT_MOC_LITERAL(8, 89, 6), // "status"
QT_MOC_LITERAL(9, 96, 25), // "QCamera::LockChangeReason"
QT_MOC_LITERAL(10, 122, 6), // "reason"
QT_MOC_LITERAL(11, 129, 12), // "changeStatus"
QT_MOC_LITERAL(12, 142, 15), // "QCamera::Status"
QT_MOC_LITERAL(13, 158, 15), // "setImageCapture"
QT_MOC_LITERAL(14, 174, 18), // "removeImageCapture"
QT_MOC_LITERAL(15, 193, 21), // "startCameraAndSetZoom"
QT_MOC_LITERAL(16, 215, 10), // "stopCamera"
QT_MOC_LITERAL(17, 226, 18), // "setCameraFlashMode"
QT_MOC_LITERAL(18, 245, 4), // "mode"
QT_MOC_LITERAL(19, 250, 18), // "getCameraFlashMode"
QT_MOC_LITERAL(20, 269, 11) // "mediaObject"

    },
    "QtCamera\0mediaObjectChanged\0\0savedImage\0"
    "id\0fileName\0changeLockStatus\0"
    "QCamera::LockStatus\0status\0"
    "QCamera::LockChangeReason\0reason\0"
    "changeStatus\0QCamera::Status\0"
    "setImageCapture\0removeImageCapture\0"
    "startCameraAndSetZoom\0stopCamera\0"
    "setCameraFlashMode\0mode\0getCameraFlashMode\0"
    "mediaObject"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtCamera[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       1,   86, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    2,   65,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   70,    2, 0x08 /* Private */,
      11,    1,   75,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      13,    0,   78,    2, 0x02 /* Public */,
      14,    0,   79,    2, 0x02 /* Public */,
      15,    0,   80,    2, 0x02 /* Public */,
      16,    0,   81,    2, 0x02 /* Public */,
      17,    1,   82,    2, 0x02 /* Public */,
      19,    0,   85,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    4,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 9,    8,   10,
    QMetaType::Void, 0x80000000 | 12,    8,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::QString,

 // properties: name, type, flags
      20, QMetaType::QObjectStar, 0x00490001,

 // properties: notify_signal_id
       0,

       0        // eod
};

void QtCamera::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QtCamera *_t = static_cast<QtCamera *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mediaObjectChanged(); break;
        case 1: _t->savedImage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->changeLockStatus((*reinterpret_cast< QCamera::LockStatus(*)>(_a[1])),(*reinterpret_cast< QCamera::LockChangeReason(*)>(_a[2]))); break;
        case 3: _t->changeStatus((*reinterpret_cast< QCamera::Status(*)>(_a[1]))); break;
        case 4: _t->setImageCapture(); break;
        case 5: _t->removeImageCapture(); break;
        case 6: _t->startCameraAndSetZoom(); break;
        case 7: _t->stopCamera(); break;
        case 8: _t->setCameraFlashMode((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: { QString _r = _t->getCameraFlashMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCamera::LockChangeReason >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCamera::LockStatus >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCamera::Status >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QtCamera::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QtCamera::mediaObjectChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (QtCamera::*_t)(int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QtCamera::savedImage)) {
                *result = 1;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        QtCamera *_t = static_cast<QtCamera *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QObject**>(_v) = _t->mediaObject(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject QtCamera::staticMetaObject = {
    { &QCamera::staticMetaObject, qt_meta_stringdata_QtCamera.data,
      qt_meta_data_QtCamera,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QtCamera::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtCamera::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QtCamera.stringdata0))
        return static_cast<void*>(const_cast< QtCamera*>(this));
    return QCamera::qt_metacast(_clname);
}

int QtCamera::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCamera::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QtCamera::mediaObjectChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void QtCamera::savedImage(int _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
