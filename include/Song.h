#ifndef SONG_H
#define SONG_H

#include <string>
#include <iostream>

struct Song {
    std::string genre;
    std::string artistName;
    std::string trackName;
    std::string trackId;
    int popularity;
    double acousticness;
    double danceability;
    int durationMs;
    double energy;
    double instrumentalness;
    std::string key;
    double liveness;
    double loudness;
    std::string mode;
    double speechiness;
    double tempo;
    std::string timeSignature;
    double valence;
    
    // Mood classification (derived)
    std::string mood;
    
    Song() : popularity(0), acousticness(0), danceability(0), durationMs(0),
             energy(0), instrumentalness(0), liveness(0), loudness(0),
             speechiness(0), tempo(0), valence(0) {}
    
    // Calculate mood based on audio features
    void calculateMood() {
        if (valence > 0.6 && energy > 0.6) mood = "Happy";
        else if (valence < 0.4 && energy < 0.4) mood = "Sad";
        else if (energy > 0.7) mood = "Energetic";
        else if (acousticness > 0.6 && energy < 0.5) mood = "Calm";
        else if (valence > 0.5 && danceability > 0.6) mood = "Party";
        else mood = "Neutral";
    }
    
    void display() const {
        std::cout << "Track: " << trackName << "\n"
                  << "Artist: " << artistName << "\n"
                  << "Genre: " << genre << "\n"
                  << "Mood: " << mood << "\n"
                  << "Tempo: " << tempo << " BPM\n"
                  << "Energy: " << energy << "\n"
                  << "Popularity: " << popularity << "\n";
    }
    
    // For BST comparisons
    bool operator<(const Song& other) const {
        return trackName < other.trackName;
    }
    
    bool operator>(const Song& other) const {
        return trackName > other.trackName;
    }
};

#endif