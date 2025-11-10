#ifndef QUEUE_H
#define QUEUE_H

#include "Song.h"

struct QueueNode {
    Song song;
    QueueNode* next;
    
    QueueNode(const Song& s) : song(s), next(nullptr) {}
};

class Queue {
private:
    QueueNode* front;
    QueueNode* rear;
    int count;

public:
    Queue() : front(nullptr), rear(nullptr), count(0) {}
    
    ~Queue() {
        clear();
    }
    
    void enqueue(const Song& song) {
        QueueNode* newNode = new QueueNode(song);
        if (!rear) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        count++;
    }
    
    bool dequeue(Song& song) {
        if (!front) return false;
        
        QueueNode* temp = front;
        song = front->song;
        front = front->next;
        
        if (!front) rear = nullptr;
        
        delete temp;
        count--;
        return true;
    }
    
    bool peek(Song& song) const {
        if (!front) return false;
        song = front->song;
        return true;
    }
    
    bool isEmpty() const {
        return front == nullptr;
    }
    
    int size() const {
        return count;
    }
    
    void clear() {
        while (front) {
            QueueNode* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
        count = 0;
    }
    
    void display() const {
        std::cout << "\n=== Song Queue (" << count << " songs) ===\n";
        QueueNode* current = front;
        int i = 1;
        while (current) {
            std::cout << i++ << ". " << current->song.trackName 
                      << " - " << current->song.artistName << "\n";
            current = current->next;
        }
    }
};

#endif