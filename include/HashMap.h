#ifndef HASHMAP_H
#define HASHMAP_H

#include <string>
#include <vector>
#include <list>

template<typename K, typename V>
class HashMap {
private:
    static const int TABLE_SIZE = 10007; // Prime number for better distribution
    std::vector<std::list<std::pair<K, V>>> table;
    
    int hash(const K& key) const {
        std::hash<K> hasher;
        return hasher(key) % TABLE_SIZE;
    }

public:
    HashMap() : table(TABLE_SIZE) {}
    
    void insert(const K& key, const V& value) {
        int idx = hash(key);
        auto& bucket = table[idx];
        
        for (auto& pair : bucket) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        bucket.push_back({key, value});
    }
    
    bool find(const K& key, V& value) const {
        int idx = hash(key);
        const auto& bucket = table[idx];
        
        for (const auto& pair : bucket) {
            if (pair.first == key) {
                value = pair.second;
                return true;
            }
        }
        return false;
    }
    
    bool remove(const K& key) {
        int idx = hash(key);
        auto& bucket = table[idx];
        
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                return true;
            }
        }
        return false;
    }
    
    std::vector<K> getKeys() const {
        std::vector<K> keys;
        for (const auto& bucket : table) {
            for (const auto& pair : bucket) {
                keys.push_back(pair.first);
            }
        }
        return keys;
    }
    
    void clear() {
        for (auto& bucket : table) {
            bucket.clear();
        }
    }
};

#endif