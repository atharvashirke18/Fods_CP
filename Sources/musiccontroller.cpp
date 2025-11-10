#include "Headers/musiccontroller.h"
#include <QDebug>

MusicController::MusicController(QObject *parent)
    : QObject(parent), library(new MusicLibrary()), isLoaded(false) {}

MusicController::~MusicController() { delete library; }

bool MusicController::loadFromCSV(const QString& path) {
    qDebug() << "Starting CSV load from:" << path;
    bool success = library->loadFromCSV(path.toStdString());
    qDebug() << "CSV load completed. Success:" << success;
    if (success) {
        isLoaded = true;
        int count = library->getAllSongs().size();
        qDebug() << "Emitting libraryLoaded signal with count:" << count;
        emit libraryLoaded(count);
    }
    return success;
}

QVector<QStringList> MusicController::searchSongs(const QString& query) {
    QVector<QStringList> results;
    if (!isLoaded) return results;
    currentResults = library->searchByName(query.toStdString());
    for (const auto& s : currentResults) results.append(songToRow(s));
    return results;
}

QVector<QStringList> MusicController::getSongsByMood(const QString& mood) {
    QVector<QStringList> results;
    if (!isLoaded) return results;
    for (const auto& s : library->getAllSongs()) {
        if (QString::fromStdString(s.mood) == mood) {
            results.append(songToRow(s));
            if (results.size() >= 50) break;
        }
    }
    return results;
}

QVector<QStringList> MusicController::getAllSongs() {
    QVector<QStringList> results;
    if (!isLoaded) return results;
    auto& songs = library->getAllSongs();
    for (size_t i = 0; i < std::min(songs.size(), size_t(100)); ++i)
        results.append(songToRow(songs[i]));
    return results;
}

QVector<QStringList> MusicController::findDuplicates() {
    QVector<QStringList> results;
    if (!isLoaded) return results;
    auto& songs = library->getAllSongs();
    for (size_t i = 0; i < std::min(songs.size(), size_t(10)); ++i)
        results.append(songToRow(songs[i]));
    return results;
}

QStringList MusicController::getTopGenres() {
    QStringList results;
    if (!isLoaded) return results;
    auto top = library->getRecommendationEngine().getTopGenres(5);
    for (const auto& p : top) results << QString::fromStdString(p.first);
    return results;
}

QStringList MusicController::getTopArtists() {
    QStringList results;
    if (!isLoaded) return results;
    auto top = library->getRecommendationEngine().getTopArtists(5);
    for (const auto& p : top) results << QString::fromStdString(p.first);
    return results;
}

// Playlist Methods
bool MusicController::createPlaylist(const QString& name) {
    if (!isLoaded) return false;
    library->createPlaylist(name.toStdString());
    emit playlistCreated(name);
    return true;
}

QStringList MusicController::getAllPlaylistNames() {
    QStringList names;
    if (!isLoaded) return names;
    auto& playlists = library->getPlaylists();
    for (const auto* playlist : playlists) {
        names << QString::fromStdString(playlist->getName());
    }
    return names;
}

QVector<QStringList> MusicController::getPlaylistSongs(int playlistIndex) {
    QVector<QStringList> results;
    if (!isLoaded) return results;
    auto& playlists = library->getPlaylists();
    if (playlistIndex < 0 || playlistIndex >= playlists.size()) return results;

    auto songs = playlists[playlistIndex]->toVector();
    for (const auto& song : songs) {
        results.append(songToRow(song));
    }
    return results;
}

bool MusicController::addSongToPlaylist(int playlistIndex, int songIndex) {
    if (!isLoaded) return false;
    if (songIndex < 0 || songIndex >= currentResults.size()) return false;
    auto& playlists = library->getPlaylists();
    if (playlistIndex < 0 || playlistIndex >= playlists.size()) return false;

    playlists[playlistIndex]->addSong(currentResults[songIndex]);
    return true;
}
bool MusicController::addSongToPlaylist(int playlistIndex, const QStringList &songData) {
    if (!isLoaded) return false;

    auto& playlists = library->getPlaylists();  // ✓ Get playlists first
    if (playlistIndex < 0 || playlistIndex >= playlists.size()) {
        return false;
    }

    // Convert QStringList back to Song object
    Song song;
    if (songData.size() >= 5) {
        song.trackName = songData[0].toStdString();
        song.artistName = songData[1].toStdString();
        // songData[2] is year - not stored in Song struct
        song.tempo = songData[3].toDouble();
        song.mood = songData[4].toStdString();
    }

    // Add the song to the playlist
    playlists[playlistIndex]->addSong(song);  // ✓ Correct variable name
    return true;
}
bool MusicController::deletePlaylist(int playlistIndex) {
    if (!isLoaded) return false;
    library->deletePlaylist(playlistIndex);
    emit playlistDeleted(playlistIndex);
    return true;
}

QVector<QStringList> MusicController::generateMoodPlaylist(const QString& mood, int duration) {
    QVector<QStringList> results;
    if (!isLoaded) return results;

    Playlist* playlist = library->generateMoodPlaylist(mood.toStdString(), duration);
    auto songs = playlist->toVector();

    for (const auto& song : songs) {
        results.append(songToRow(song));
    }

    emit playlistCreated(mood + " Vibes");
    return results;
}

QVector<QStringList> MusicController::generateWorkoutPlaylist(int duration) {
    QVector<QStringList> results;
    if (!isLoaded) return results;

    Playlist* playlist = PlaylistGenerator::generateWorkout(library->getAllSongs(), duration);
    library->getPlaylists().push_back(playlist);

    auto songs = playlist->toVector();
    for (const auto& song : songs) {
        results.append(songToRow(song));
    }

    emit playlistCreated("Workout Mix");
    return results;
}

QVector<QStringList> MusicController::generateRelaxationPlaylist(int duration) {
    QVector<QStringList> results;
    if (!isLoaded) return results;

    Playlist* playlist = PlaylistGenerator::generateRelaxation(library->getAllSongs(), duration);
    library->getPlaylists().push_back(playlist);

    auto songs = playlist->toVector();
    for (const auto& song : songs) {
        results.append(songToRow(song));
    }

    emit playlistCreated("Relaxation Mix");
    return results;
}

QVector<QStringList> MusicController::generatePartyPlaylist() {
    QVector<QStringList> results;
    if (!isLoaded) return results;

    Playlist* playlist = PlaylistGenerator::generateParty(library->getAllSongs(), 40);
    library->getPlaylists().push_back(playlist);

    auto songs = playlist->toVector();
    for (const auto& song : songs) {
        results.append(songToRow(song));
    }

    emit playlistCreated("Party Mix");
    return results;
}


QStringList MusicController::songToRow(const Song& s) {
    return {QString::fromStdString(s.trackName),
            QString::fromStdString(s.artistName),
            QString::number(2020),
            QString::number(s.tempo, 'f', 0),
            QString::fromStdString(s.mood)};
}
