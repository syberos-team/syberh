/****************************************************************************
** Meta object code from reading C++ file 'download.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../sybero-template/com/syberos/download/src/download.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'download.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Download_t {
    QByteArrayData data[30];
    char stringdata0[325];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Download_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Download_t qt_meta_stringdata_Download = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Download"
QT_MOC_LITERAL(1, 9, 16), // "downloadCanceled"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 10), // "downloadID"
QT_MOC_LITERAL(4, 38, 17), // "downloadCompleted"
QT_MOC_LITERAL(5, 56, 4), // "path"
QT_MOC_LITERAL(6, 61, 14), // "downloadFailed"
QT_MOC_LITERAL(7, 76, 6), // "result"
QT_MOC_LITERAL(8, 83, 9), // "errorCode"
QT_MOC_LITERAL(9, 93, 14), // "downloadPaused"
QT_MOC_LITERAL(10, 108, 16), // "downloadProgress"
QT_MOC_LITERAL(11, 125, 4), // "name"
QT_MOC_LITERAL(12, 130, 12), // "receivedSize"
QT_MOC_LITERAL(13, 143, 9), // "totalSize"
QT_MOC_LITERAL(14, 153, 16), // "saveDownloadFile"
QT_MOC_LITERAL(15, 170, 3), // "url"
QT_MOC_LITERAL(16, 174, 14), // "QNetworkReply*"
QT_MOC_LITERAL(17, 189, 5), // "reply"
QT_MOC_LITERAL(18, 195, 18), // "downloadFileFailed"
QT_MOC_LITERAL(19, 214, 12), // "errorMessage"
QT_MOC_LITERAL(20, 227, 6), // "cancel"
QT_MOC_LITERAL(21, 234, 12), // "getFileInfos"
QT_MOC_LITERAL(22, 247, 15), // "QList<FileInfo>"
QT_MOC_LITERAL(23, 263, 5), // "pause"
QT_MOC_LITERAL(24, 269, 15), // "removeFileInfos"
QT_MOC_LITERAL(25, 285, 6), // "long[]"
QT_MOC_LITERAL(26, 292, 11), // "downloadIDs"
QT_MOC_LITERAL(27, 304, 7), // "restart"
QT_MOC_LITERAL(28, 312, 6), // "resume"
QT_MOC_LITERAL(29, 319, 5) // "start"

    },
    "Download\0downloadCanceled\0\0downloadID\0"
    "downloadCompleted\0path\0downloadFailed\0"
    "result\0errorCode\0downloadPaused\0"
    "downloadProgress\0name\0receivedSize\0"
    "totalSize\0saveDownloadFile\0url\0"
    "QNetworkReply*\0reply\0downloadFileFailed\0"
    "errorMessage\0cancel\0getFileInfos\0"
    "QList<FileInfo>\0pause\0removeFileInfos\0"
    "long[]\0downloadIDs\0restart\0resume\0"
    "start"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Download[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       4,    2,   87,    2, 0x06 /* Public */,
       6,    3,   92,    2, 0x06 /* Public */,
       9,    1,   99,    2, 0x06 /* Public */,
      10,    4,  102,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    2,  111,    2, 0x0a /* Public */,
      18,    3,  116,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      20,    1,  123,    2, 0x02 /* Public */,
      21,    0,  126,    2, 0x02 /* Public */,
      23,    1,  127,    2, 0x02 /* Public */,
      24,    1,  130,    2, 0x02 /* Public */,
      27,    1,  133,    2, 0x02 /* Public */,
      28,    1,  136,    2, 0x02 /* Public */,
      29,    3,  139,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Long,    3,
    QMetaType::Void, QMetaType::Long, QMetaType::QString,    3,    5,
    QMetaType::Void, QMetaType::Long, QMetaType::QString, QMetaType::Long,    3,    7,    8,
    QMetaType::Void, QMetaType::Long,    3,
    QMetaType::Void, QMetaType::Long, QMetaType::QString, QMetaType::Double, QMetaType::Double,    3,   11,   12,   13,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 16,   15,   17,
    QMetaType::Void, QMetaType::QString, QMetaType::Long, QMetaType::QString,   15,    8,   19,

 // methods: parameters
    QMetaType::Long, QMetaType::Long,    3,
    0x80000000 | 22,
    QMetaType::Long, QMetaType::Long,    3,
    QMetaType::Long, 0x80000000 | 25,   26,
    QMetaType::Long, QMetaType::Long,    3,
    QMetaType::Long, QMetaType::Long,    3,
    QMetaType::Long, QMetaType::Long, QMetaType::QString, QMetaType::QString,    3,   15,   11,

       0        // eod
};

void Download::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Download *_t = static_cast<Download *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->downloadCanceled((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 1: _t->downloadCompleted((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->downloadFailed((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< long(*)>(_a[3]))); break;
        case 3: _t->downloadPaused((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 4: _t->downloadProgress((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 5: _t->saveDownloadFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QNetworkReply*(*)>(_a[2]))); break;
        case 6: _t->downloadFileFailed((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 7: { long _r = _t->cancel((*reinterpret_cast< long(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< long*>(_a[0]) = _r; }  break;
        case 8: { QList<FileInfo> _r = _t->getFileInfos();
            if (_a[0]) *reinterpret_cast< QList<FileInfo>*>(_a[0]) = _r; }  break;
        case 9: { long _r = _t->pause((*reinterpret_cast< long(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< long*>(_a[0]) = _r; }  break;
        case 10: { long _r = _t->removeFileInfos((*reinterpret_cast< long(*)[]>(_a[1])));
            if (_a[0]) *reinterpret_cast< long*>(_a[0]) = _r; }  break;
        case 11: { long _r = _t->restart((*reinterpret_cast< long(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< long*>(_a[0]) = _r; }  break;
        case 12: { long _r = _t->resume((*reinterpret_cast< long(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< long*>(_a[0]) = _r; }  break;
        case 13: { long _r = _t->start((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< long*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Download::*_t)(long );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Download::downloadCanceled)) {
                *result = 0;
            }
        }
        {
            typedef void (Download::*_t)(long , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Download::downloadCompleted)) {
                *result = 1;
            }
        }
        {
            typedef void (Download::*_t)(long , QString , long );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Download::downloadFailed)) {
                *result = 2;
            }
        }
        {
            typedef void (Download::*_t)(long );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Download::downloadPaused)) {
                *result = 3;
            }
        }
        {
            typedef void (Download::*_t)(long , QString , double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Download::downloadProgress)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject Download::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Download.data,
      qt_meta_data_Download,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Download::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Download::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Download.stringdata0))
        return static_cast<void*>(const_cast< Download*>(this));
    return QObject::qt_metacast(_clname);
}

int Download::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void Download::downloadCanceled(long _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Download::downloadCompleted(long _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Download::downloadFailed(long _t1, QString _t2, long _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Download::downloadPaused(long _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Download::downloadProgress(long _t1, QString _t2, double _t3, double _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
