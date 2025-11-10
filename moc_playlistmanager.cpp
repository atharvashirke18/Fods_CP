/****************************************************************************
** Meta object code from reading C++ file 'playlistmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.17)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "Headers/playlistmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playlistmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.17. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PlaylistManager_t {
    QByteArrayData data[12];
    char stringdata0[204];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlaylistManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlaylistManager_t qt_meta_stringdata_PlaylistManager = {
    {
QT_MOC_LITERAL(0, 0, 15), // "PlaylistManager"
QT_MOC_LITERAL(1, 16, 16), // "playlistSelected"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 5), // "index"
QT_MOC_LITERAL(4, 40, 21), // "createPlaylistClicked"
QT_MOC_LITERAL(5, 62, 21), // "deletePlaylistClicked"
QT_MOC_LITERAL(6, 84, 19), // "generateMoodClicked"
QT_MOC_LITERAL(7, 104, 22), // "generateWorkoutClicked"
QT_MOC_LITERAL(8, 127, 25), // "generateRelaxationClicked"
QT_MOC_LITERAL(9, 153, 20), // "generatePartyClicked"
QT_MOC_LITERAL(10, 174, 15), // "addSongsClicked"
QT_MOC_LITERAL(11, 190, 13) // "playlistIndex"

    },
    "PlaylistManager\0playlistSelected\0\0"
    "index\0createPlaylistClicked\0"
    "deletePlaylistClicked\0generateMoodClicked\0"
    "generateWorkoutClicked\0generateRelaxationClicked\0"
    "generatePartyClicked\0addSongsClicked\0"
    "playlistIndex"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlaylistManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    0,   57,    2, 0x06 /* Public */,
       5,    1,   58,    2, 0x06 /* Public */,
       6,    0,   61,    2, 0x06 /* Public */,
       7,    0,   62,    2, 0x06 /* Public */,
       8,    0,   63,    2, 0x06 /* Public */,
       9,    0,   64,    2, 0x06 /* Public */,
      10,    1,   65,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,

       0        // eod
};

void PlaylistManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PlaylistManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->playlistSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->createPlaylistClicked(); break;
        case 2: _t->deletePlaylistClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->generateMoodClicked(); break;
        case 4: _t->generateWorkoutClicked(); break;
        case 5: _t->generateRelaxationClicked(); break;
        case 6: _t->generatePartyClicked(); break;
        case 7: _t->addSongsClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PlaylistManager::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlaylistManager::playlistSelected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PlaylistManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlaylistManager::createPlaylistClicked)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PlaylistManager::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlaylistManager::deletePlaylistClicked)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PlaylistManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlaylistManager::generateMoodClicked)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PlaylistManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlaylistManager::generateWorkoutClicked)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PlaylistManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlaylistManager::generateRelaxationClicked)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (PlaylistManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlaylistManager::generatePartyClicked)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (PlaylistManager::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlaylistManager::addSongsClicked)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PlaylistManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_PlaylistManager.data,
    qt_meta_data_PlaylistManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PlaylistManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlaylistManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PlaylistManager.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PlaylistManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void PlaylistManager::playlistSelected(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PlaylistManager::createPlaylistClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void PlaylistManager::deletePlaylistClicked(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PlaylistManager::generateMoodClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void PlaylistManager::generateWorkoutClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void PlaylistManager::generateRelaxationClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void PlaylistManager::generatePartyClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void PlaylistManager::addSongsClicked(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
