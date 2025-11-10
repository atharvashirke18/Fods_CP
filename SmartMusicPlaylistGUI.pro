QT += core gui widgets

CONFIG += c++17

INCLUDEPATH += $$PWD/include

# SFML Audio Library
LIBS += -lsfml-audio -lsfml-system

SOURCES += \
    Sources/main.cpp \
    Sources/mainwindow.cpp \
    Sources/musiccontroller.cpp \
    Sources/sidebar.cpp \
    Sources/songlibrary.cpp \
    Sources/nowplayingbar.cpp \
    Sources/playlistgenerator.cpp \
    Sources/duplicatefinder.cpp \
    Sources/useranalytics.cpp \
    Sources/settings.cpp \
    Sources/playlistmanager.cpp

HEADERS += \
    Headers/mainwindow.h \
    Headers/musiccontroller.h \
    Headers/sidebar.h \
    Headers/songlibrary.h \
    Headers/nowplayingbar.h \
    Headers/playlistgenerator.h \
    Headers/duplicatefinder.h \
    Headers/useranalytics.h \
    Headers/settings.h \
    Headers/playlistmanager.h

TARGET = SmartMusicPlaylistGUI
TEMPLATE = app
