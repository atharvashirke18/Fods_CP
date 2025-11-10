/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.17)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "Headers/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.17. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[24];
    char stringdata0[381];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 15), // "onLibraryLoaded"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 5), // "count"
QT_MOC_LITERAL(4, 34, 13), // "onHomeClicked"
QT_MOC_LITERAL(5, 48, 16), // "onLibraryClicked"
QT_MOC_LITERAL(6, 65, 18), // "onPlaylistsClicked"
QT_MOC_LITERAL(7, 84, 19), // "onDuplicatesClicked"
QT_MOC_LITERAL(8, 104, 16), // "onHistoryClicked"
QT_MOC_LITERAL(9, 121, 19), // "onSearchTextChanged"
QT_MOC_LITERAL(10, 141, 4), // "text"
QT_MOC_LITERAL(11, 146, 17), // "onTableRowClicked"
QT_MOC_LITERAL(12, 164, 3), // "row"
QT_MOC_LITERAL(13, 168, 16), // "onCreatePlaylist"
QT_MOC_LITERAL(14, 185, 16), // "onDeletePlaylist"
QT_MOC_LITERAL(15, 202, 5), // "index"
QT_MOC_LITERAL(16, 208, 18), // "onPlaylistSelected"
QT_MOC_LITERAL(17, 227, 22), // "onGenerateMoodPlaylist"
QT_MOC_LITERAL(18, 250, 25), // "onGenerateWorkoutPlaylist"
QT_MOC_LITERAL(19, 276, 28), // "onGenerateRelaxationPlaylist"
QT_MOC_LITERAL(20, 305, 23), // "onGeneratePartyPlaylist"
QT_MOC_LITERAL(21, 329, 20), // "onAddSongsToPlaylist"
QT_MOC_LITERAL(22, 350, 13), // "playlistIndex"
QT_MOC_LITERAL(23, 364, 16) // "refreshPlaylists"

    },
    "MainWindow\0onLibraryLoaded\0\0count\0"
    "onHomeClicked\0onLibraryClicked\0"
    "onPlaylistsClicked\0onDuplicatesClicked\0"
    "onHistoryClicked\0onSearchTextChanged\0"
    "text\0onTableRowClicked\0row\0onCreatePlaylist\0"
    "onDeletePlaylist\0index\0onPlaylistSelected\0"
    "onGenerateMoodPlaylist\0onGenerateWorkoutPlaylist\0"
    "onGenerateRelaxationPlaylist\0"
    "onGeneratePartyPlaylist\0onAddSongsToPlaylist\0"
    "playlistIndex\0refreshPlaylists"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x08 /* Private */,
       4,    0,  102,    2, 0x08 /* Private */,
       5,    0,  103,    2, 0x08 /* Private */,
       6,    0,  104,    2, 0x08 /* Private */,
       7,    0,  105,    2, 0x08 /* Private */,
       8,    0,  106,    2, 0x08 /* Private */,
       9,    1,  107,    2, 0x08 /* Private */,
      11,    1,  110,    2, 0x08 /* Private */,
      13,    0,  113,    2, 0x08 /* Private */,
      14,    1,  114,    2, 0x08 /* Private */,
      16,    1,  117,    2, 0x08 /* Private */,
      17,    0,  120,    2, 0x08 /* Private */,
      18,    0,  121,    2, 0x08 /* Private */,
      19,    0,  122,    2, 0x08 /* Private */,
      20,    0,  123,    2, 0x08 /* Private */,
      21,    1,  124,    2, 0x08 /* Private */,
      23,    0,  127,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   22,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onLibraryLoaded((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->onHomeClicked(); break;
        case 2: _t->onLibraryClicked(); break;
        case 3: _t->onPlaylistsClicked(); break;
        case 4: _t->onDuplicatesClicked(); break;
        case 5: _t->onHistoryClicked(); break;
        case 6: _t->onSearchTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->onTableRowClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->onCreatePlaylist(); break;
        case 9: _t->onDeletePlaylist((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->onPlaylistSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->onGenerateMoodPlaylist(); break;
        case 12: _t->onGenerateWorkoutPlaylist(); break;
        case 13: _t->onGenerateRelaxationPlaylist(); break;
        case 14: _t->onGeneratePartyPlaylist(); break;
        case 15: _t->onAddSongsToPlaylist((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->refreshPlaylists(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
