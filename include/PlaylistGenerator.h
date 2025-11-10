#ifndef PLAYLISTGENERATOR_H
#define PLAYLISTGENERATOR_H

#include "Song.h"
#include "LinkedList.h"
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

class PlaylistGenerator {
public:
    static Playlist* generateByGenre(const std::vector<Song>& library,
                                      const std::string& genre,
                                      int maxSongs = 25) {
        Playlist* playlist = new Playlist(genre + " Mix");
        std::vector<Song> genreSongs;
        
        for (const auto& song : library) {
            if (song.genre == genre) {
                genreSongs.push_back(song);
            }
        }
        
        // Sort by popularity
        std::sort(genreSongs.begin(), genreSongs.end(),
                 [](const Song& a, const Song& b) { 
                     return a.popularity > b.popularity; 
                 });
        
        for (int i = 0; i < std::min(maxSongs, (int)genreSongs.size()); i++) {
            playlist->addSong(genreSongs[i]);
        }
        
        return playlist;
    }
    
    static Playlist* generateWorkout(const std::vector<Song>& library, int duration = 45) {
        Playlist* playlist = new Playlist("Workout Mix");
        std::vector<Song> workoutSongs;
        
        // High energy, fast tempo songs
        for (const auto& song : library) {
            if (song.energy > 0.7 && song.tempo > 120 && song.tempo < 180) {
                workoutSongs.push_back(song);
            }
        }
        
        std::sort(workoutSongs.begin(), workoutSongs.end(),
                 [](const Song& a, const Song& b) { 
                     return a.energy > b.energy; 
                 });
        
        int totalDuration = 0;
        int targetDuration = duration * 60 * 1000;
        
        for (const auto& song : workoutSongs) {
            if (totalDuration >= targetDuration) break;
            playlist->addSong(song);
            totalDuration += song.durationMs;
        }
        
        return playlist;
    }
    
    static Playlist* generateRelaxation(const std::vector<Song>& library, int duration = 30) {
        Playlist* playlist = new Playlist("Relaxation Mix");
        std::vector<Song> calmSongs;
        
        // Low energy, acoustic, calm songs
        for (const auto& song : library) {
            if (song.energy < 0.5 && song.acousticness > 0.5 && song.valence < 0.6) {
                calmSongs.push_back(song);
            }
        }
        
        std::sort(calmSongs.begin(), calmSongs.end(),
                 [](const Song& a, const Song& b) { 
                     return a.acousticness > b.acousticness; 
                 });
        
        int totalDuration = 0;
        int targetDuration = duration * 60 * 1000;
        
        for (const auto& song : calmSongs) {
            if (totalDuration >= targetDuration) break;
            playlist->addSong(song);
            totalDuration += song.durationMs;
        }
        
        return playlist;
    }
    
    static Playlist* generateParty(const std::vector<Song>& library, int maxSongs = 40) {
        Playlist* playlist = new Playlist("Party Mix");
        std::vector<Song> partySongs;
        
        // High danceability, energy, and valence
        for (const auto& song : library) {
            if (song.danceability > 0.7 && song.energy > 0.6 && song.valence > 0.6) {
                partySongs.push_back(song);
            }
        }
        
        std::sort(partySongs.begin(), partySongs.end(),
                 [](const Song& a, const Song& b) { 
                     return (a.danceability + a.energy) > (b.danceability + b.energy); 
                 });
        
        for (int i = 0; i < std::min(maxSongs, (int)partySongs.size()); i++) {
            playlist->addSong(partySongs[i]);
        }
        
        return playlist;
    }
    
    static Playlist* generateShuffle(const std::vector<Song>& library, int maxSongs = 50) {
        Playlist* playlist = new Playlist("Shuffle Mix");
        
        if (library.empty()) return playlist;
        
        std::vector<int> indices;
        for (int i = 0; i < library.size(); i++) {
            indices.push_back(i);
        }
        
        // Shuffle indices
        for (int i = indices.size() - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            std::swap(indices[i], indices[j]);
        }
        
        for (int i = 0; i < std::min(maxSongs, (int)indices.size()); i++) {
            playlist->addSong(library[indices[i]]);
        }
        
        return playlist;
    }
    
    static Playlist* generateByArtist(const std::vector<Song>& library,
                                       const std::string& artist,
                                       int maxSongs = 30) {
        Playlist* playlist = new Playlist(artist + " Collection");
        std::vector<Song> artistSongs;
        
        std::string lowerArtist = artist;
        std::transform(lowerArtist.begin(), lowerArtist.end(), 
                      lowerArtist.begin(), ::tolower);
        
        for (const auto& song : library) {
            std::string songArtist = song.artistName;
            std::transform(songArtist.begin(), songArtist.end(), 
                          songArtist.begin(), ::tolower);
            
            if (songArtist.find(lowerArtist) != std::string::npos) {
                artistSongs.push_back(song);
            }
        }
        
        std::sort(artistSongs.begin(), artistSongs.end(),
                 [](const Song& a, const Song& b) { 
                     return a.popularity > b.popularity; 
                 });
        
        for (int i = 0; i < std::min(maxSongs, (int)artistSongs.size()); i++) {
            playlist->addSong(artistSongs[i]);
        }
        
        return playlist;
    }
};

#endif