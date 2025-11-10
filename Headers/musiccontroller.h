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

    // Playlist methods
    bool createPlaylist(const QString& name);
    QStringList getAllPlaylistNames();
    QVector<QStringList> getPlaylistSongs(int playlistIndex);
    bool addSongToPlaylist(int playlistIndex, int songIndex);
    bool addSongToPlaylist(int playlistIndex, const QStringList &songData);
    bool deletePlaylist(int playlistIndex);
    QVector<QStringList> generateMoodPlaylist(const QString& mood, int duration);
    QVector<QStringList> generateWorkoutPlaylist(int duration);
    QVector<QStringList> generateRelaxationPlaylist(int duration);
    QVector<QStringList> generatePartyPlaylist();
    int getCurrentSongIndex() { return -1; } // For future use



signals:
    void libraryLoaded(int count);
    void playlistCreated(QString name);
    void playlistDeleted(int index);

private:
    QStringList songToRow(const Song& s);
};
#endif
