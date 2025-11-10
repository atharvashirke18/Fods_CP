#ifndef BST_H
#define BST_H

#include "Song.h"
#include <functional>
#include <vector>

template<typename T>
struct BSTNode {
    T data;
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(const T& d) : data(d), left(nullptr), right(nullptr) {}
};

template<typename T>
class BST {
private:
    BSTNode<T>* root;
    std::function<bool(const T&, const T&)> comparator;
    
    BSTNode<T>* insert(BSTNode<T>* node, const T& data) {
        if (!node) return new BSTNode<T>(data);
        
        if (comparator(data, node->data)) {
            node->left = insert(node->left, data);
        } else {
            node->right = insert(node->right, data);
        }
        return node;
    }
    
    void inorder(BSTNode<T>* node, std::vector<T>& result) const {
        if (!node) return;
        inorder(node->left, result);
        result.push_back(node->data);
        inorder(node->right, result);
    }
    
    void clear(BSTNode<T>* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
    
    BSTNode<T>* search(BSTNode<T>* node, const T& key) const {
        if (!node) return nullptr;
        if (!comparator(key, node->data) && !comparator(node->data, key)) {
            return node;
        }
        if (comparator(key, node->data)) {
            return search(node->left, key);
        }
        return search(node->right, key);
    }

public:
    BST(std::function<bool(const T&, const T&)> comp) 
        : root(nullptr), comparator(comp) {}
    
    ~BST() { clear(root); }
    
    void insert(const T& data) {
        root = insert(root, data);
    }
    
    std::vector<T> getSorted() const {
        std::vector<T> result;
        inorder(root, result);
        return result;
    }
    
    bool find(const T& key) const {
        return search(root, key) != nullptr;
    }
    
    void rangeSearch(BSTNode<T>* node, double min, double max, 
                     std::function<double(const T&)> getValue,
                     std::vector<T>& result) const {
        if (!node) return;
        
        double val = getValue(node->data);
        if (val >= min && val <= max) {
            result.push_back(node->data);
        }
        if (val > min) rangeSearch(node->left, min, max, getValue, result);
        if (val < max) rangeSearch(node->right, min, max, getValue, result);
    }
    
    std::vector<T> rangeQuery(double min, double max, 
                              std::function<double(const T&)> getValue) const {
        std::vector<T> result;
        rangeSearch(root, min, max, getValue, result);
        return result;
    }
};

#endif