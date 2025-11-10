#ifndef RECOMMENDATIONENGINE_H
#define RECOMMENDATIONENGINE_H

#include "Song.h"
#include "HashMap.h"
#include <vector>
#include <map>
#include <algorithm>

class RecommendationEngine {
private:
    HashMap<std::string, int> genrePreferences;
    HashMap<std::string, int> artistPreferences;
    HashMap<std::string, int> moodPreferences;
    HashMap<std::string, int> skippedSongs;
    int totalPlays;

public:
    RecommendationEngine() : totalPlays(0) {}
    
    void recordPlay(const Song& song) {
        totalPlays++;
        
        // Update genre preference
        int genreCount = 0;
        genrePreferences.find(song.genre, genreCount);
        genrePreferences.insert(song.genre, genreCount + 1);
        
        // Update artist preference
        int artistCount = 0;
        artistPreferences.find(song.artistName, artistCount);
        artistPreferences.insert(song.artistName, artistCount + 1);
        
        // Update mood preference
        int moodCount = 0;
        moodPreferences.find(song.mood, moodCount);
        moodPreferences.insert(song.mood, moodCount + 1);
    }
    
    void recordSkip(const Song& song) {
        int skipCount = 0;
        skippedSongs.find(song.trackId, skipCount);
        skippedSongs.insert(song.trackId, skipCount + 1);
    }
    
    std::vector<Song> getRecommendations(const std::vector<Song>& library, 
                                         int limit = 20) {
        std::vector<std::pair<Song, double>> scored;
        
        for (const auto& song : library) {
            int skipCount = 0;
            skippedSongs.find(song.trackId, skipCount);
            if (skipCount > 2) continue; // Skip frequently skipped songs
            
            double score = calculateRecommendationScore(song);
            scored.push_back({song, score});
        }
        
        std::sort(scored.begin(), scored.end(),
                 [](const auto& a, const auto& b) { return a.second > b.second; });
        
        std::vector<Song> recommendations;
        for (int i = 0; i < std::min(limit, (int)scored.size()); i++) {
            recommendations.push_back(scored[i].first);
        }
        
        return recommendations;
    }
    
    double calculateRecommendationScore(const Song& song) {
        double score = 0;
        
        // Genre preference
        int genreCount = 0;
        genrePreferences.find(song.genre, genreCount);
        score += (double)genreCount / std::max(1, totalPlays) * 3.0;
        
        // Artist preference
        int artistCount = 0;
        artistPreferences.find(song.artistName, artistCount);
        score += (double)artistCount / std::max(1, totalPlays) * 2.0;
        
        // Mood preference
        int moodCount = 0;
        moodPreferences.find(song.mood, moodCount);
        score += (double)moodCount / std::max(1, totalPlays) * 2.0;
        
        // Popularity factor
        score += song.popularity / 100.0;
        
        return score;
    }
    
    std::map<std::string, int> getTopGenres(int limit = 5) {
        std::vector<std::string> genres = genrePreferences.getKeys();
        std::vector<std::pair<std::string, int>> genreCounts;
        
        for (const auto& genre : genres) {
            int count = 0;
            genrePreferences.find(genre, count);
            genreCounts.push_back({genre, count});
        }
        
        std::sort(genreCounts.begin(), genreCounts.end(),
                 [](const auto& a, const auto& b) { return a.second > b.second; });
        
        std::map<std::string, int> result;
        for (int i = 0; i < std::min(limit, (int)genreCounts.size()); i++) {
            result[genreCounts[i].first] = genreCounts[i].second;
        }
        
        return result;
    }
    
    std::map<std::string, int> getTopArtists(int limit = 5) {
        std::vector<std::string> artists = artistPreferences.getKeys();
        std::vector<std::pair<std::string, int>> artistCounts;
        
        for (const auto& artist : artists) {
            int count = 0;
            artistPreferences.find(artist, count);
            artistCounts.push_back({artist, count});
        }
        
        std::sort(artistCounts.begin(), artistCounts.end(),
                 [](const auto& a, const auto& b) { return a.second > b.second; });
        
        std::map<std::string, int> result;
        for (int i = 0; i < std::min(limit, (int)artistCounts.size()); i++) {
            result[artistCounts[i].first] = artistCounts[i].second;
        }
        
        return result;
    }
    
    void reset() {
        genrePreferences.clear();
        artistPreferences.clear();
        moodPreferences.clear();
        skippedSongs.clear();
        totalPlays = 0;
    }
};

#endif