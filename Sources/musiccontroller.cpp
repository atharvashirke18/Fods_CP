#include "Headers/musiccontroller.h"

MusicController::MusicController(QObject *parent) : QObject(parent), library(new MusicLibrary()), isLoaded(false) {}
MusicController::~MusicController() { delete library; }

bool MusicController::loadFromCSV(const QString& path) {
    bool success = library->loadFromCSV(path.toStdString());
    if (success) { isLoaded = true; emit libraryLoaded(library->getAllSongs().size()); }
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
    // Simplified: just show first 10 songs as demo
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

QStringList MusicController::songToRow(const Song& s) {
    return {QString::fromStdString(s.trackName), QString::fromStdString(s.artistName),
            QString::number(2020), QString::number(s.tempo, 'f', 0), QString::fromStdString(s.mood)};
}
