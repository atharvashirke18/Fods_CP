#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "MusicLibrary.h"
#include "PlaylistGenerator.h"
#include <iostream>
#include <limits>

class UserInterface {
private:
    MusicLibrary& library;

public:
    UserInterface(MusicLibrary& lib) : library(lib) {}
    
    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
    
    void pause() {
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
    
    void showMainMenu() {
        std::cout << "\n╔════════════════════════════════════════╗\n";
        std::cout << "║   SMART MUSIC PLAYLIST GENERATOR      ║\n";
        std::cout << "╚════════════════════════════════════════╝\n";
        std::cout << "\n1. Library Management\n";
        std::cout << "2. Playlist Operations\n";
        std::cout << "3. Smart Features\n";
        std::cout << "4. Playback Control\n";
        std::cout << "5. User Profile\n";
        std::cout << "0. Exit\n";
        std::cout << "\nChoice: ";
    }
    
    void libraryManagementMenu() {
        while (true) {
            clearScreen();
            std::cout << "\n=== Library Management ===\n";
            std::cout << "1. Search songs\n";
            std::cout << "2. List songs by genre\n";
            std::cout << "3. List songs by mood\n";
            std::cout << "4. Browse by artist\n";
            std::cout << "5. Library statistics\n";
            std::cout << "0. Back\n";
            std::cout << "\nChoice: ";
            
            int choice;
            std::cin >> choice;
            std::cin.ignore();
            
            if (choice == 0) break;
            
            switch (choice) {
                case 1: searchSongs(); break;
                case 2: listByGenre(); break;
                case 3: listByMood(); break;
                case 4: browseByArtist(); break;
                case 5: showLibraryStats(); break;
                default: std::cout << "Invalid choice!\n"; pause();
            }
        }
    }
    
    void playlistOperationsMenu() {
        while (true) {
            clearScreen();
            std::cout << "\n=== Playlist Operations ===\n";
            std::cout << "1. Create new playlist\n";
            std::cout << "2. View playlists\n";
            std::cout << "3. Edit playlist\n";
            std::cout << "4. Delete playlist\n";
            std::cout << "5. Play playlist\n";
            std::cout << "0. Back\n";
            std::cout << "\nChoice: ";
            
            int choice;
            std::cin >> choice;
            std::cin.ignore();
            
            if (choice == 0) break;
            
            switch (choice) {
                case 1: createPlaylist(); break;
                case 2: viewPlaylists(); break;
                case 3: editPlaylist(); break;
                case 4: deletePlaylist(); break;
                case 5: playPlaylist(); break;
                default: std::cout << "Invalid choice!\n"; pause();
            }
        }
    }
    
    void smartFeaturesMenu() {
        while (true) {
            clearScreen();
            std::cout << "\n=== Smart Features ===\n";
            std::cout << "1. Generate mood playlist\n";
            std::cout << "2. Get recommendations\n";
            std::cout << "3. Find similar songs\n";
            std::cout << "4. Autocomplete search\n";
            std::cout << "5. Generate workout playlist\n";
            std::cout << "6. Generate relaxation playlist\n";
            std::cout << "7. Generate party playlist\n";
            std::cout << "0. Back\n";
            std::cout << "\nChoice: ";
            
            int choice;
            std::cin >> choice;
            std::cin.ignore();
            
            if (choice == 0) break;
            
            switch (choice) {
                case 1: generateMoodPlaylist(); break;
                case 2: showRecommendations(); break;
                case 3: findSimilarSongs(); break;
                case 4: autocompleteSearch(); break;
                case 5: generateWorkoutPlaylist(); break;
                case 6: generateRelaxationPlaylist(); break;
                case 7: generatePartyPlaylist(); break;
                default: std::cout << "Invalid choice!\n"; pause();
            }
        }
    }
    
    void playbackControlMenu() {
        while (true) {
            clearScreen();
            std::cout << "\n=== Playback Control ===\n";
            std::cout << "1. Play next in queue\n";
            std::cout << "2. Add song to queue\n";
            std::cout << "3. View queue\n";
            std::cout << "4. Recently played\n";
            std::cout << "5. Clear queue\n";
            std::cout << "0. Back\n";
            std::cout << "\nChoice: ";
            
            int choice;
            std::cin >> choice;
            std::cin.ignore();
            
            if (choice == 0) break;
            
            switch (choice) {
                case 1: library.playNext(); pause(); break;
                case 2: addToQueue(); break;
                case 3: library.getQueue().display(); pause(); break;
                case 4: library.showRecentlyPlayed(); pause(); break;
                case 5: library.getQueue().clear(); 
                       std::cout << "Queue cleared!\n"; pause(); break;
                default: std::cout << "Invalid choice!\n"; pause();
            }
        }
    }
    
    void userProfileMenu() {
        while (true) {
            clearScreen();
            std::cout << "\n=== User Profile ===\n";
            std::cout << "1. Top genres\n";
            std::cout << "2. Top artists\n";
            std::cout << "3. Listening stats\n";
            std::cout << "4. Reset preferences\n";
            std::cout << "0. Back\n";
            std::cout << "\nChoice: ";
            
            int choice;
            std::cin >> choice;
            std::cin.ignore();
            
            if (choice == 0) break;
            
            switch (choice) {
                case 1: showTopGenres(); break;
                case 2: showTopArtists(); break;
                case 3: showListeningStats(); break;
                case 4: 
                    library.getRecommendationEngine().reset();
                    std::cout << "Preferences reset!\n";
                    pause();
                    break;
                default: std::cout << "Invalid choice!\n"; pause();
            }
        }
    }

private:
    void searchSongs() {
        std::cout << "\nEnter search term: ";
        std::string query;
        std::getline(std::cin, query);
        
        auto results = library.searchByName(query);
        
        if (results.empty()) {
            std::cout << "No songs found!\n";
        } else {
            std::cout << "\n=== Search Results (" << results.size() << ") ===\n";
            for (size_t i = 0; i < results.size(); i++) {
                std::cout << (i + 1) << ". " << results[i].trackName 
                          << " - " << results[i].artistName 
                          << " [" << results[i].genre << "]\n";
            }
        }
        pause();
    }
    
    void listByGenre() {
        std::cout << "\nEnter genre: ";
        std::string genre;
        std::getline(std::cin, genre);
        
        auto& songs = library.getAllSongs();
        std::vector<Song> genreSongs;
        
        for (const auto& song : songs) {
            if (song.genre == genre) {
                genreSongs.push_back(song);
            }
        }
        
        if (genreSongs.empty()) {
            std::cout << "No songs found in this genre!\n";
        } else {
            std::cout << "\n=== " << genre << " Songs (" << genreSongs.size() << ") ===\n";
            for (size_t i = 0; i < std::min((size_t)20, genreSongs.size()); i++) {
                std::cout << (i + 1) << ". " << genreSongs[i].trackName 
                          << " - " << genreSongs[i].artistName << "\n";
            }
        }
        pause();
    }
    
    void listByMood() {
        std::cout << "\nAvailable moods: Happy, Sad, Energetic, Calm, Party, Neutral\n";
        std::cout << "Enter mood: ";
        std::string mood;
        std::getline(std::cin, mood);
        
        auto& songs = library.getAllSongs();
        std::vector<Song> moodSongs;
        
        for (const auto& song : songs) {
            if (song.mood == mood) {
                moodSongs.push_back(song);
            }
        }
        
        if (moodSongs.empty()) {
            std::cout << "No songs found for this mood!\n";
        } else {
            std::cout << "\n=== " << mood << " Songs (" << moodSongs.size() << ") ===\n";
            for (size_t i = 0; i < std::min((size_t)20, moodSongs.size()); i++) {
                std::cout << (i + 1) << ". " << moodSongs[i].trackName 
                          << " - " << moodSongs[i].artistName << "\n";
            }
        }
        pause();
    }
    
    void browseByArtist() {
        std::cout << "\nEnter artist name: ";
        std::string artist;
        std::getline(std::cin, artist);
        
        auto results = library.searchByArtist(artist);
        
        if (results.empty()) {
            std::cout << "No songs found by this artist!\n";
        } else {
            std::cout << "\n=== Songs by " << artist << " (" << results.size() << ") ===\n";
            for (size_t i = 0; i < std::min((size_t)30, results.size()); i++) {
                std::cout << (i + 1) << ". " << results[i].trackName << "\n";
            }
        }
        pause();
    }
    
    void showLibraryStats() {
        auto& songs = library.getAllSongs();
        std::cout << "\n=== Library Statistics ===\n";
        std::cout << "Total songs: " << songs.size() << "\n";
        
        HashSet<std::string> genres, artists;
        for (const auto& song : songs) {
            genres.insert(song.genre);
            artists.insert(song.artistName);
        }
        
        std::cout << "Unique artists: " << artists.size() << "\n";
        std::cout << "Unique genres: " << genres.size() << "\n";
        pause();
    }
    
    void createPlaylist() {
        std::cout << "\nPlaylist name: ";
        std::string name;
        std::getline(std::cin, name);
        
        Playlist* playlist = library.createPlaylist(name);
        std::cout << "Playlist '" << name << "' created!\n";
        
        std::cout << "\nAdd songs now? (y/n): ";
        char choice;
        std::cin >> choice;
        std::cin.ignore();
        
        if (choice == 'y' || choice == 'Y') {
            while (true) {
                std::cout << "\nSearch for song (or 'done' to finish): ";
                std::string query;
                std::getline(std::cin, query);
                
                if (query == "done") break;
                
                auto results = library.searchByName(query);
                if (!results.empty()) {
                    for (size_t i = 0; i < std::min((size_t)10, results.size()); i++) {
                        std::cout << (i + 1) << ". " << results[i].trackName 
                                  << " - " << results[i].artistName << "\n";
                    }
                    std::cout << "\nSelect song (0 to skip): ";
                    int idx;
                    std::cin >> idx;
                    std::cin.ignore();
                    
                    if (idx > 0 && idx <= results.size()) {
                        playlist->addSong(results[idx - 1]);
                        std::cout << "Added!\n";
                    }
                }
            }
        }
        pause();
    }
    
    void viewPlaylists() {
        auto& playlists = library.getPlaylists();
        if (playlists.empty()) {
            std::cout << "No playlists yet!\n";
        } else {
            std::cout << "\n=== Your Playlists ===\n";
            for (size_t i = 0; i < playlists.size(); i++) {
                std::cout << (i + 1) << ". " << playlists[i]->getName() 
                          << " (" << playlists[i]->getSize() << " songs)\n";
            }
            
            std::cout << "\nView details? (playlist number or 0): ";
            int choice;
            std::cin >> choice;
            std::cin.ignore();
            
            if (choice > 0 && choice <= playlists.size()) {
                playlists[choice - 1]->display();
            }
        }
        pause();
    }
    
    void editPlaylist() {
        auto& playlists = library.getPlaylists();
        if (playlists.empty()) {
            std::cout << "No playlists to edit!\n";
            pause();
            return;
        }
        
        for (size_t i = 0; i < playlists.size(); i++) {
            std::cout << (i + 1) << ". " << playlists[i]->getName() << "\n";
        }
        
        std::cout << "\nSelect playlist: ";
        int idx;
        std::cin >> idx;
        std::cin.ignore();
        
        if (idx > 0 && idx <= playlists.size()) {
            Playlist* playlist = playlists[idx - 1];
            playlist->display();
            
            std::cout << "\n1. Add songs\n2. Remove song\n0. Cancel\nChoice: ";
            int action;
            std::cin >> action;
            std::cin.ignore();
            
            if (action == 1) {
                std::cout << "Search for song: ";
                std::string query;
                std::getline(std::cin, query);
                
                auto results = library.searchByName(query);
                if (!results.empty()) {
                    for (size_t i = 0; i < std::min((size_t)10, results.size()); i++) {
                        std::cout << (i + 1) << ". " << results[i].trackName 
                                  << " - " << results[i].artistName << "\n";
                    }
                    std::cout << "\nSelect: ";
                    int s;
                    std::cin >> s;
                    if (s > 0 && s <= results.size()) {
                        playlist->addSong(results[s - 1]);
                        std::cout << "Added!\n";
                    }
                }
            }
        }
        pause();
    }
    
    void deletePlaylist() {
        auto& playlists = library.getPlaylists();
        if (playlists.empty()) {
            std::cout << "No playlists to delete!\n";
            pause();
            return;
        }
        
        for (size_t i = 0; i < playlists.size(); i++) {
            std::cout << (i + 1) << ". " << playlists[i]->getName() << "\n";
        }
        
        std::cout << "\nDelete playlist: ";
        int idx;
        std::cin >> idx;
        std::cin.ignore();
        
        if (idx > 0 && idx <= playlists.size()) {
            library.deletePlaylist(idx - 1);
            std::cout << "Playlist deleted!\n";
        }
        pause();
    }
    
    void playPlaylist() {
        auto& playlists = library.getPlaylists();
        if (playlists.empty()) {
            std::cout << "No playlists available!\n";
            pause();
            return;
        }
        
        for (size_t i = 0; i < playlists.size(); i++) {
            std::cout << (i + 1) << ". " << playlists[i]->getName() << "\n";
        }
        
        std::cout << "\nSelect playlist: ";
        int idx;
        std::cin >> idx;
        std::cin.ignore();
        
        if (idx > 0 && idx <= playlists.size()) {
            auto songs = playlists[idx - 1]->toVector();
            for (const auto& song : songs) {
                library.addToQueue(song);
            }
            std::cout << "Playlist added to queue!\n";
            library.playNext();
        }
        pause();
    }
    
    void generateMoodPlaylist() {
        std::cout << "\nAvailable moods: Happy, Sad, Energetic, Calm, Party, Neutral\n";
        std::cout << "Select mood: ";
        std::string mood;
        std::getline(std::cin, mood);
        
        std::cout << "Duration (minutes, default 30): ";
        std::string input;
        std::getline(std::cin, input);
        int duration = input.empty() ? 30 : std::stoi(input);
        
        Playlist* playlist = library.generateMoodPlaylist(mood, duration);
        library.getPlaylists().push_back(playlist);
        
        playlist->display();
        std::cout << "\nPlaylist created and saved!\n";
        pause();
    }
    
    void showRecommendations() {
        auto recommendations = library.getRecommendations(20);
        
        if (recommendations.empty()) {
            std::cout << "Not enough listening history for recommendations.\n";
        } else {
            std::cout << "\n=== Recommended for You ===\n";
            for (size_t i = 0; i < recommendations.size(); i++) {
                std::cout << (i + 1) << ". " << recommendations[i].trackName 
                          << " - " << recommendations[i].artistName 
                          << " [" << recommendations[i].mood << "]\n";
            }
        }
        pause();
    }
    
    void findSimilarSongs() {
        std::cout << "\nSearch for song: ";
        std::string query;
        std::getline(std::cin, query);
        
        auto results = library.searchByName(query);
        if (results.empty()) {
            std::cout << "Song not found!\n";
            pause();
            return;
        }
        
        for (size_t i = 0; i < std::min((size_t)5, results.size()); i++) {
            std::cout << (i + 1) << ". " << results[i].trackName 
                      << " - " << results[i].artistName << "\n";
        }
        
        std::cout << "\nSelect song: ";
        int idx;
        std::cin >> idx;
        std::cin.ignore();
        
        if (idx > 0 && idx <= results.size()) {
            auto similar = library.getSimilarSongs(results[idx - 1], 10);
            std::cout << "\n=== Similar Songs ===\n";
            for (size_t i = 0; i < similar.size(); i++) {
                std::cout << (i + 1) << ". " << similar[i].trackName 
                          << " - " << similar[i].artistName << "\n";
            }
        }
        pause();
    }
    
    void autocompleteSearch() {
        std::cout << "\n1. Search by track\n2. Search by artist\nChoice: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();
        
        std::cout << "Enter prefix: ";
        std::string prefix;
        std::getline(std::cin, prefix);
        
        std::vector<std::string> suggestions;
        if (choice == 1) {
            suggestions = library.autocompleteTrack(prefix);
        } else if (choice == 2) {
            suggestions = library.autocompleteArtist(prefix);
        }
        
        if (suggestions.empty()) {
            std::cout << "No suggestions found!\n";
        } else {
            std::cout << "\n=== Suggestions ===\n";
            for (size_t i = 0; i < suggestions.size(); i++) {
                std::cout << (i + 1) << ". " << suggestions[i] << "\n";
            }
        }
        pause();
    }
    
    void generateWorkoutPlaylist() {
        std::cout << "\nDuration (minutes, default 45): ";
        std::string input;
        std::getline(std::cin, input);
        int duration = input.empty() ? 45 : std::stoi(input);
        
        Playlist* playlist = PlaylistGenerator::generateWorkout(library.getAllSongs(), duration);
        library.getPlaylists().push_back(playlist);
        
        playlist->display();
        std::cout << "\nWorkout playlist created!\n";
        pause();
    }
    
    void generateRelaxationPlaylist() {
        std::cout << "\nDuration (minutes, default 30): ";
        std::string input;
        std::getline(std::cin, input);
        int duration = input.empty() ? 30 : std::stoi(input);
        
        Playlist* playlist = PlaylistGenerator::generateRelaxation(library.getAllSongs(), duration);
        library.getPlaylists().push_back(playlist);
        
        playlist->display();
        std::cout << "\nRelaxation playlist created!\n";
        pause();
    }
    
    void generatePartyPlaylist() {
        Playlist* playlist = PlaylistGenerator::generateParty(library.getAllSongs(), 40);
        library.getPlaylists().push_back(playlist);
        
        playlist->display();
        std::cout << "\nParty playlist created!\n";
        pause();
    }
    
    void addToQueue() {
        std::cout << "\nSearch for song: ";
        std::string query;
        std::getline(std::cin, query);
        
        auto results = library.searchByName(query);
        if (results.empty()) {
            std::cout << "No songs found!\n";
        } else {
            for (size_t i = 0; i < std::min((size_t)10, results.size()); i++) {
                std::cout << (i + 1) << ". " << results[i].trackName 
                          << " - " << results[i].artistName << "\n";
            }
            std::cout << "\nSelect song: ";
            int idx;
            std::cin >> idx;
            std::cin.ignore();
            
            if (idx > 0 && idx <= results.size()) {
                library.addToQueue(results[idx - 1]);
            }
        }
        pause();
    }
    
    void showTopGenres() {
        auto topGenres = library.getRecommendationEngine().getTopGenres(10);
        
        if (topGenres.empty()) {
            std::cout << "No listening history yet!\n";
        } else {
            std::cout << "\n=== Your Top Genres ===\n";
            int rank = 1;
            for (const auto& pair : topGenres) {
                std::cout << rank++ << ". " << pair.first 
                          << " (" << pair.second << " plays)\n";
            }
        }
        pause();
    }
    
    void showTopArtists() {
        auto topArtists = library.getRecommendationEngine().getTopArtists(10);
        
        if (topArtists.empty()) {
            std::cout << "No listening history yet!\n";
        } else {
            std::cout << "\n=== Your Top Artists ===\n";
            int rank = 1;
            for (const auto& pair : topArtists) {
                std::cout << rank++ << ". " << pair.first 
                          << " (" << pair.second << " plays)\n";
            }
        }
        pause();
    }
    
    void showListeningStats() {
        auto topGenres = library.getRecommendationEngine().getTopGenres(3);
        auto topArtists = library.getRecommendationEngine().getTopArtists(3);
        
        std::cout << "\n=== Your Listening Profile ===\n";
        std::cout << "\nTop Genres:\n";
        int rank = 1;
        for (const auto& pair : topGenres) {
            std::cout << rank++ << ". " << pair.first << "\n";
        }
        
        std::cout << "\nTop Artists:\n";
        rank = 1;
        for (const auto& pair : topArtists) {
            std::cout << rank++ << ". " << pair.first << "\n";
        }
        
        pause();
    }
};

#endif