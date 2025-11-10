#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H

#include "Song.h"
#include "BST.h"
#include "HashMap.h"
#include "HashSet.h"
#include "Trie.h"
#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include "DuplicateDetector.h"
#include "MoodAnalyzer.h"
#include "RecommendationEngine.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm> // needed for std::transform

class MusicLibrary {
private:
    std::vector<Song> allSongs;
    HashMap<std::string, Song> songById;
    BST<Song>* bstByName;
    BST<Song>* bstByTempo;
    BST<Song>* bstByPopularity;
    Trie* artistTrie;
    Trie* trackTrie;
    HashSet<std::string> uniqueArtists;
    HashSet<std::string> uniqueGenres;

    Stack<Song> recentlyPlayed;
    Queue playQueue;
    std::vector<Playlist*> userPlaylists;

    DuplicateDetector duplicateDetector;
    MoodAnalyzer moodAnalyzer;
    RecommendationEngine recommendationEngine;

    Song* currentSong;

public:
    MusicLibrary() : currentSong(nullptr) {
        bstByName = new BST<Song>([](const Song& a, const Song& b) {
            return a.trackName < b.trackName;
        });

        bstByTempo = new BST<Song>([](const Song& a, const Song& b) {
            return a.tempo < b.tempo;
        });

        bstByPopularity = new BST<Song>([](const Song& a, const Song& b) {
            return a.popularity < b.popularity;
        });

        artistTrie = new Trie();
        trackTrie = new Trie();
    }

    ~MusicLibrary() {
        delete bstByName;
        delete bstByTempo;
        delete bstByPopularity;
        delete artistTrie;
        delete trackTrie;

        for (auto playlist : userPlaylists) {
            delete playlist;
        }
    }

    bool loadFromCSV(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Cannot open file " << filename << "\n";
            return false;
        }

        std::string line;
        std::getline(file, line); // Skip header

        int count = 0;
        while (std::getline(file, line)) {
            Song song = parseCSVLine(line);
            if (!song.trackId.empty()) {
                addSong(song);
                count++;

                if (count % 10000 == 0) {
                    std::cout << "Loaded " << count << " songs...\r" << std::flush;
                }
            }
        }

        std::cout << "\nSuccessfully loaded " << count << " songs!\n";
        file.close();
        return true;
    }

    void addSong(const Song& song) {
        Song s = song;
        s.calculateMood();

        allSongs.push_back(s);
        songById.insert(s.trackId, s);
        bstByName->insert(s);
        bstByTempo->insert(s);
        bstByPopularity->insert(s);

        artistTrie->insert(s.artistName);
        trackTrie->insert(s.trackName);
        uniqueArtists.insert(s.artistName);
        uniqueGenres.insert(s.genre);
    }

    std::vector<Song> searchByName(const std::string& query) {
        std::vector<Song> results;
        std::string lower = query;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

        for (const auto& song : allSongs) {
            std::string trackLower = song.trackName;
            std::transform(trackLower.begin(), trackLower.end(), trackLower.begin(), ::tolower);

            if (trackLower.find(lower) != std::string::npos) {
                results.push_back(song);
                if (results.size() >= 20) break;
            }
        }
        return results;
    }

    std::vector<Song> searchByArtist(const std::string& artist) {
        std::vector<Song> results;
        std::string lower = artist;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

        for (const auto& song : allSongs) {
            std::string artistLower = song.artistName;
            std::transform(artistLower.begin(), artistLower.end(), artistLower.begin(), ::tolower);

            if (artistLower.find(lower) != std::string::npos) {
                results.push_back(song);
            }
        }
        return results;
    }

    std::vector<std::string> autocompleteTrack(const std::string& prefix) {
        return trackTrie->autocomplete(prefix, 10);
    }

    std::vector<std::string> autocompleteArtist(const std::string& prefix) {
        return artistTrie->autocomplete(prefix, 10);
    }

    void playSong(const Song& song) {
        if (currentSong) {
            recentlyPlayed.push(*currentSong);
        }
        currentSong = new Song(song);
        recommendationEngine.recordPlay(song);

        std::cout << "\n🎵 Now Playing: " << song.trackName 
                  << " - " << song.artistName << "\n";
    }

    void playNext() {
        Song nextSong;
        if (playQueue.dequeue(nextSong)) {
            playSong(nextSong);
        } else {
            std::cout << "Queue is empty!\n";
        }
    }

    void addToQueue(const Song& song) {
        playQueue.enqueue(song);
        std::cout << "Added to queue: " << song.trackName << "\n";
    }

    void showRecentlyPlayed() {
        auto recent = recentlyPlayed.getAll();
        std::cout << "\n=== Recently Played ===\n";
        for (int i = recent.size() - 1; i >= 0; i--) {
            std::cout << (recent.size() - i) << ". " << recent[i].trackName 
                      << " - " << recent[i].artistName << "\n";
        }
    }

    Playlist* createPlaylist(const std::string& name) {
        Playlist* playlist = new Playlist(name);
        userPlaylists.push_back(playlist);
        return playlist;
    }

    void deletePlaylist(int index) {
        if (index >= 0 && index < userPlaylists.size()) {
            delete userPlaylists[index];
            userPlaylists.erase(userPlaylists.begin() + index);
        }
    }

    std::vector<Song> getRecommendations(int limit = 20) {
        return recommendationEngine.getRecommendations(allSongs, limit);
    }

    std::vector<Song> getSimilarSongs(const Song& song, int limit = 10) {
        return duplicateDetector.findSimilarSongs(song, allSongs, limit);
    }

    Playlist* generateMoodPlaylist(const std::string& mood, int maxSongs = 30) {
        return moodAnalyzer.generateSmartPlaylist(allSongs, mood, maxSongs);
    }

    std::vector<Song>& getAllSongs() { return allSongs; }
    std::vector<Playlist*>& getPlaylists() { return userPlaylists; }
    Queue& getQueue() { return playQueue; }
    RecommendationEngine& getRecommendationEngine() { return recommendationEngine; }

private:
    Song parseCSVLine(const std::string& line) {
        Song song;
        std::stringstream ss(line);
        std::string field;
        int fieldIndex = 0;

        while (std::getline(ss, field, ',')) {
            try {
                switch(fieldIndex) {
                    case 0: song.genre = field; break;
                    case 1: song.artistName = field; break;
                    case 2: song.trackName = field; break;
                    case 3: song.trackId = field; break;
                    case 4: song.popularity = std::stoi(field); break;
                    case 5: song.acousticness = std::stod(field); break;
                    case 6: song.danceability = std::stod(field); break;
                    case 7: song.durationMs = std::stoi(field); break;
                    case 8: song.energy = std::stod(field); break;
                    case 9: song.instrumentalness = std::stod(field); break;
                    case 10: song.key = field; break;
                    case 11: song.liveness = std::stod(field); break;
                    case 12: song.loudness = std::stod(field); break;
                    case 13: song.mode = field; break;
                    case 14: song.speechiness = std::stod(field); break;
                    case 15: song.tempo = std::stod(field); break;
                    case 16: song.timeSignature = field; break;
                    case 17: song.valence = std::stod(field); break;
                }
            } catch (...) {
                // Ignore bad fields
            }
            fieldIndex++;
        }

        return song;
    }
};

#endif
