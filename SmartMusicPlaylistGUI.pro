QT += core gui widgets

CONFIG += c++17

# Include paths - CRITICAL for finding headers
INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/Headers

SOURCES += \
    Sources/main.cpp \
    Sources/mainwindow.cpp \
    Sources/musiccontroller.cpp \
    Sources/playlistgenerator.cpp \
    Sources/sidebar.cpp \
    Sources/songlibrary.cpp \
    Sources/nowplayingbar.cpp \
    Sources/duplicatefinder.cpp \
    Sources/useranalytics.cpp \
    Sources/settings.cpp

HEADERS += \
    Headers/mainwindow.h \
    Headers/musiccontroller.h \
    Headers/playlistgenerator.h \
    Headers/sidebar.h \
    Headers/songlibrary.h \
    Headers/nowplayingbar.h \
    Headers/duplicatefinder.h \
    Headers/useranalytics.h \
    Headers/settings.h

# Windows specific settings
win32 {
    QMAKE_CXXFLAGS += -Wa,-mbig-obj
}

TARGET = SmartMusicPlaylistGUI
TEMPLATE = app

DISTFILES += \
    data/songs.csv
