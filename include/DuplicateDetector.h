#ifndef DUPLICATEDETECTOR_H
#define DUPLICATEDETECTOR_H

#include "Song.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

class DuplicateDetector {
private:
    // Levenshtein distance for string similarity
    int levenshteinDistance(const std::string& s1, const std::string& s2) {
        int m = s1.length();
        int n = s2.length();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));
        
        for (int i = 0; i <= m; i++) dp[i][0] = i;
        for (int j = 0; j <= n; j++) dp[0][j] = j;
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i-1] == s2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = 1 + std::min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
                }
            }
        }
        return dp[m][n];
    }
    
    std::string normalize(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        result.erase(std::remove_if(result.begin(), result.end(), 
                    [](char c) { return !std::isalnum(c); }), result.end());
        return result;
    }

public:
    struct DuplicatePair {
        Song song1;
        Song song2;
        double similarity;
    };
    
    std::vector<DuplicatePair> findDuplicates(const std::vector<Song>& songs, 
                                              double threshold = 0.8) {
        std::vector<DuplicatePair> duplicates;
        
        for (size_t i = 0; i < songs.size(); i++) {
            for (size_t j = i + 1; j < songs.size(); j++) {
                double sim = calculateSimilarity(songs[i], songs[j]);
                if (sim >= threshold) {
                    duplicates.push_back({songs[i], songs[j], sim});
                }
            }
        }
        return duplicates;
    }
    
    double calculateSimilarity(const Song& s1, const Song& s2) {
        std::string name1 = normalize(s1.trackName);
        std::string name2 = normalize(s2.trackName);
        std::string artist1 = normalize(s1.artistName);
        std::string artist2 = normalize(s2.artistName);
        
        // Check artist similarity first
        int artistDist = levenshteinDistance(artist1, artist2);
        double artistSim = 1.0 - (double)artistDist / std::max(artist1.length(), artist2.length());
        
        if (artistSim < 0.7) return 0.0;
        
        // Check track name similarity
        int nameDist = levenshteinDistance(name1, name2);
        double nameSim = 1.0 - (double)nameDist / std::max(name1.length(), name2.length());
        
        // Combined similarity (weighted)
        return 0.7 * nameSim + 0.3 * artistSim;
    }
    
    std::vector<Song> findSimilarSongs(const Song& target, 
                                       const std::vector<Song>& library,
                                       int limit = 10) {
        std::vector<std::pair<Song, double>> scored;
        
        for (const auto& song : library) {
            if (song.trackId == target.trackId) continue;
            
            double score = 0;
            // Audio feature similarity
            score += 1.0 - std::fabs(target.energy - song.energy);
            score += 1.0 - std::fabs(target.valence - song.valence);
            score += 1.0 - std::fabs(target.danceability - song.danceability);
            score += 1.0 - std::fabs(target.tempo - song.tempo) / 200.0;
            
            // Genre/mood match
            if (target.genre == song.genre) score += 1.0;
            if (target.mood == song.mood) score += 1.0;
            
            scored.push_back({song, score});
        }
        
        std::sort(scored.begin(), scored.end(), 
                 [](const auto& a, const auto& b) { return a.second > b.second; });
        
        std::vector<Song> result;
        for (int i = 0; i < std::min(limit, (int)scored.size()); i++) {
            result.push_back(scored[i].first);
        }
        return result;
    }
};

#endif