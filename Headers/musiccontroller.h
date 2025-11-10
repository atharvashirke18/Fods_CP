#ifndef MUSICCONTROLLER_H
#define MUSICCONTROLLER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVector>
#include "../include/MusicLibrary.h"
#include "../include/Song.h"
#include "../include/PlaylistGenerator.h"

class MusicController : public QObject
{
    Q_OBJECT
private:
    MusicLibrary* library;
    bool isLoaded;
    std::vector<Song> currentResults;
public:
    explicit MusicController(QObject *parent = nullptr);
    ~MusicController();
    bool loadFromCSV(const QString& path);
    QVector<QStringList> searchSongs(const QString& query);
    QVector<QStringList> getSongsByMood(const QString& mood);
    QVector<QStringList> getAllSongs();
    QVector<QStringList> findDuplicates();
    QStringList getTopGenres();
    QStringList getTopArtists();
signals:
    void libraryLoaded(int count);
private:
    QStringList songToRow(const Song& s);
};
#endif