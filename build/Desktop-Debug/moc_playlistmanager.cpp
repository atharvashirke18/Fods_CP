/****************************************************************************
** Meta object code from reading C++ file 'playlistmanager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Headers/playlistmanager.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playlistmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN15PlaylistManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto PlaylistManager::qt_create_metaobjectdata<qt_meta_tag_ZN15PlaylistManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PlaylistManager",
        "playlistSelected",
        "",
        "index",
        "createPlaylistClicked",
        "deletePlaylistClicked",
        "addSongsClicked",
        "playlistIndex",
        "generateMoodClicked",
        "generateWorkoutClicked",
        "generateRelaxationClicked",
        "generatePartyClicked",
        "generatePlaylistRequested",
        "mood",
        "duration",
        "handleGenerateMood",
        "handleGenerateWorkout",
        "handleGenerateRelaxation",
        "handleGenerateParty",
        "updateAudioStatus"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'playlistSelected'
        QtMocHelpers::SignalData<void(int)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Signal 'createPlaylistClicked'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'deletePlaylistClicked'
        QtMocHelpers::SignalData<void(int)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Signal 'addSongsClicked'
        QtMocHelpers::SignalData<void(int)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 7 },
        }}),
        // Signal 'generateMoodClicked'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'generateWorkoutClicked'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'generateRelaxationClicked'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'generatePartyClicked'
        QtMocHelpers::SignalData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'generatePlaylistRequested'
        QtMocHelpers::SignalData<void(const QString &, int)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 13 }, { QMetaType::Int, 14 },
        }}),
        // Slot 'handleGenerateMood'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'handleGenerateWorkout'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'handleGenerateRelaxation'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'handleGenerateParty'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'updateAudioStatus'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PlaylistManager, qt_meta_tag_ZN15PlaylistManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PlaylistManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15PlaylistManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15PlaylistManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15PlaylistManagerE_t>.metaTypes,
    nullptr
} };

void PlaylistManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PlaylistManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->playlistSelected((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->createPlaylistClicked(); break;
        case 2: _t->deletePlaylistClicked((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->addSongsClicked((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->generateMoodClicked(); break;
        case 5: _t->generateWorkoutClicked(); break;
        case 6: _t->generateRelaxationClicked(); break;
        case 7: _t->generatePartyClicked(); break;
        case 8: _t->generatePlaylistRequested((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 9: _t->handleGenerateMood(); break;
        case 10: _t->handleGenerateWorkout(); break;
        case 11: _t->handleGenerateRelaxation(); break;
        case 12: _t->handleGenerateParty(); break;
        case 13: _t->updateAudioStatus(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (PlaylistManager::*)(int )>(_a, &PlaylistManager::playlistSelected, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlaylistManager::*)()>(_a, &PlaylistManager::createPlaylistClicked, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlaylistManager::*)(int )>(_a, &PlaylistManager::deletePlaylistClicked, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlaylistManager::*)(int )>(_a, &PlaylistManager::addSongsClicked, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlaylistManager::*)()>(_a, &PlaylistManager::generateMoodClicked, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlaylistManager::*)()>(_a, &PlaylistManager::generateWorkoutClicked, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlaylistManager::*)()>(_a, &PlaylistManager::generateRelaxationClicked, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlaylistManager::*)()>(_a, &PlaylistManager::generatePartyClicked, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlaylistManager::*)(const QString & , int )>(_a, &PlaylistManager::generatePlaylistRequested, 8))
            return;
    }
}

const QMetaObject *PlaylistManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlaylistManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15PlaylistManagerE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PlaylistManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void PlaylistManager::playlistSelected(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void PlaylistManager::createPlaylistClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void PlaylistManager::deletePlaylistClicked(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void PlaylistManager::addSongsClicked(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void PlaylistManager::generateMoodClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void PlaylistManager::generateWorkoutClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void PlaylistManager::generateRelaxationClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void PlaylistManager::generatePartyClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void PlaylistManager::generatePlaylistRequested(const QString & _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 8, nullptr, _t1, _t2);
}
QT_WARNING_POP
