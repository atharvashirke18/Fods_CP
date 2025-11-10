#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    std::vector<std::string> suggestions;
    
    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    TrieNode* root;
    
    void collectSuggestions(TrieNode* node, std::string prefix, 
                           std::vector<std::string>& results, int limit) {
        if (!node || results.size() >= limit) return;
        
        if (node->isEndOfWord) {
            results.push_back(prefix);
        }
        
        for (auto& pair : node->children) {
            collectSuggestions(pair.second, prefix + pair.first, results, limit);
        }
    }
    
    void deleteNode(TrieNode* node) {
        if (!node) return;
        for (auto& pair : node->children) {
            deleteNode(pair.second);
        }
        delete node;
    }

public:
    Trie() : root(new TrieNode()) {}
    
    ~Trie() {
        deleteNode(root);
    }
    
    void insert(const std::string& word) {
        if (word.empty()) return;
        
        TrieNode* current = root;
        std::string lower = word;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        
        for (char c : lower) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        current->isEndOfWord = true;
    }
    
    bool search(const std::string& word) {
        TrieNode* current = root;
        std::string lower = word;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        
        for (char c : lower) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children[c];
        }
        return current->isEndOfWord;
    }
    
    std::vector<std::string> autocomplete(const std::string& prefix, int limit = 10) {
        std::vector<std::string> results;
        TrieNode* current = root;
        std::string lower = prefix;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        
        for (char c : lower) {
            if (current->children.find(c) == current->children.end()) {
                return results;
            }
            current = current->children[c];
        }
        
        collectSuggestions(current, prefix, results, limit);
        return results;
    }
    
    void clear() {
        deleteNode(root);
        root = new TrieNode();
    }
};

#endif