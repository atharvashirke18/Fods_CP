#ifndef HASHSET_H
#define HASHSET_H

#include <string>
#include <vector>
#include <list>
#include <functional>

template<typename T>
class HashSet {
private:
    static const int TABLE_SIZE = 5003;
    std::vector<std::list<T>> table;
    
    int hash(const T& item) const {
        std::hash<T> hasher;
        return hasher(item) % TABLE_SIZE;
    }

public:     
    HashSet() : table(TABLE_SIZE) {}
    
    bool insert(const T& item) {
        int idx = hash(item);
        auto& bucket = table[idx];
        
        for (const auto& existing : bucket) {
            if (existing == item) return false;
        }
        bucket.push_back(item);
        return true;
    }
    
    bool contains(const T& item) const {
        int idx = hash(item);
        const auto& bucket = table[idx];
        
        for (const auto& existing : bucket) {
            if (existing == item) return true;
        }
        return false;
    }
    
    bool remove(const T& item) {
        int idx = hash(item);
        auto& bucket = table[idx];
        
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (*it == item) {
                bucket.erase(it);
                return true;
            }
        }
        return false;
    }
    
    std::vector<T> toVector() const {
        std::vector<T> result;
        for (const auto& bucket : table) {
            for (const auto& item : bucket) {
                result.push_back(item);
            }
        }
        return result;
    }
    
    void clear() {
        for (auto& bucket : table) {
            bucket.clear();
        }
    }
    
    int size() const {
        int count = 0;
        for (const auto& bucket : table) {
            count += bucket.size();
        }
        return count;
    }
};

#endif