#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Song.h"
#include <iostream>

struct PlaylistNode {
    Song song;
    PlaylistNode* next;
    PlaylistNode* prev;
    
    PlaylistNode(const Song& s) : song(s), next(nullptr), prev(nullptr) {}
};

class Playlist {
private:
    PlaylistNode* head;
    PlaylistNode* tail;
    std::string name;
    int size;

public:
    Playlist(const std::string& n = "Untitled") 
        : head(nullptr), tail(nullptr), name(n), size(0) {}
    
    ~Playlist() {
        clear();
    }
    
    void addSong(const Song& song) {
        PlaylistNode* newNode = new PlaylistNode(song);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }
    
    void insertAt(const Song& song, int position) {
        if (position <= 0) {
            PlaylistNode* newNode = new PlaylistNode(song);
            newNode->next = head;
            if (head) head->prev = newNode;
            head = newNode;
            if (!tail) tail = head;
            size++;
            return;
        }
        
        PlaylistNode* current = head;
        for (int i = 0; i < position - 1 && current; i++) {
            current = current->next;
        }
        
        if (!current) {
            addSong(song);
            return;
        }
        
        PlaylistNode* newNode = new PlaylistNode(song);
        newNode->next = current->next;
        newNode->prev = current;
        if (current->next) current->next->prev = newNode;
        current->next = newNode;
        if (current == tail) tail = newNode;
        size++;
    }
    
    bool removeSong(const std::string& trackId) {
        PlaylistNode* current = head;
        while (current) {
            if (current->song.trackId == trackId) {
                if (current->prev) current->prev->next = current->next;
                else head = current->next;
                
                if (current->next) current->next->prev = current->prev;
                else tail = current->prev;
                
                delete current;
                size--;
                return true;
            }
            current = current->next;
        }
        return false;
    }
    
    void display() const {
        std::cout << "\n=== Playlist: " << name << " (" << size << " songs) ===\n";
        PlaylistNode* current = head;
        int i = 1;
        while (current) {
            std::cout << i++ << ". " << current->song.trackName 
                      << " - " << current->song.artistName << "\n";
            current = current->next;
        }
    }
    
    void clear() {
        while (head) {
            PlaylistNode* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }
    
    std::string getName() const { return name; }
    int getSize() const { return size; }
    PlaylistNode* getHead() const { return head; }
    
    std::vector<Song> toVector() const {
        std::vector<Song> songs;
        PlaylistNode* current = head;
        while (current) {
            songs.push_back(current->song);
            current = current->next;
        }
        return songs;
    }
};

#endif