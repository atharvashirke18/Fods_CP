#ifndef MOODANALYZER_H
#define MOODANALYZER_H

#include "Song.h"
#include "LinkedList.h"
#include <vector>
#include <string>
#include <cmath>

class MoodAnalyzer {
public:
    std::vector<Song> getSongsByMood(const std::vector<Song>& library, 
                                     const std::string& targetMood) {
        std::vector<Song> result;
        for (const auto& song : library) {
            if (song.mood == targetMood) {
                result.push_back(song);
            }
        }
        return result;
    }
    
    Playlist* generateMoodPlaylist(const std::vector<Song>& library,
                                   const std::string& mood,
                                   int maxSongs = 30) {
        Playlist* playlist = new Playlist(mood + " Vibes");
        std::vector<Song> moodSongs = getSongsByMood(library, mood);
        
        // Score songs for variety
        std::vector<std::pair<Song, double>> scored;
        for (const auto& song : moodSongs) {
            double score = song.popularity / 100.0;
            scored.push_back({song, score});
        }
        
        // Sort by score
        std::sort(scored.begin(), scored.end(),
                 [](const auto& a, const auto& b) { return a.second > b.second; });
        
        // Add top songs to playlist
        for (int i = 0; i < std::min(maxSongs, (int)scored.size()); i++) {
            playlist->addSong(scored[i].first);
        }
        
        return playlist;
    }
    
    Playlist* generateSmartPlaylist(const std::vector<Song>& library,
                                    const std::string& mood,
                                    int duration = 30) {
        Playlist* playlist = new Playlist("Smart " + mood + " Mix");
        std::vector<Song> moodSongs = getSongsByMood(library, mood);
        
        if (moodSongs.empty()) return playlist;
        
        // Select seed song
        Song current = moodSongs[rand() % moodSongs.size()];
        playlist->addSong(current);
        
        int totalDuration = current.durationMs;
        int targetDuration = duration * 60 * 1000; // Convert to ms
        
        while (totalDuration < targetDuration && moodSongs.size() > 1) {
            Song next = findBestNextSong(current, moodSongs);
            playlist->addSong(next);
            totalDuration += next.durationMs;
            current = next;
            
            // Remove used song
            moodSongs.erase(std::remove_if(moodSongs.begin(), moodSongs.end(),
                [&next](const Song& s) { return s.trackId == next.trackId; }),
                moodSongs.end());
        }
        
        return playlist;
    }
    
private:
    Song findBestNextSong(const Song& current, const std::vector<Song>& candidates) {
        double bestScore = -1;
        Song bestSong;
        
        for (const auto& candidate : candidates) {
            if (candidate.trackId == current.trackId) continue;
            
            double score = calculateTransitionScore(current, candidate);
            if (score > bestScore) {
                bestScore = score;
                bestSong = candidate;
            }
        }
        
        return bestSong;
    }
    
    double calculateTransitionScore(const Song& from, const Song& to) {
        double score = 0;
        
        // Tempo similarity (closer is better)
        double tempoDiff = std::abs(from.tempo - to.tempo);
        score += std::max(0.0, 1.0 - tempoDiff / 100.0);
        
        // Energy flow (gradual changes preferred)
        double energyDiff = std::abs(from.energy - to.energy);
        score += std::max(0.0, 1.0 - energyDiff);
        
        // Key compatibility (same key bonus)
        if (from.key == to.key) score += 0.5;
        
        // Valence continuity
        double valenceDiff = std::abs(from.valence - to.valence);
        score += std::max(0.0, 1.0 - valenceDiff);
        
        return score;
    }
};

#endif