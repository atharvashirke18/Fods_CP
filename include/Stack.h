#ifndef STACK_H
#define STACK_H

#include <vector>

template<typename T>
class Stack {
private:
    std::vector<T> items;
    int maxSize;

public:
    Stack(int max = 100) : maxSize(max) {}
    
    void push(const T& item) {
        if (items.size() >= maxSize) {
            items.erase(items.begin());
        }
        items.push_back(item);
    }
    
    bool pop(T& item) {
        if (items.empty()) return false;
        item = items.back();
        items.pop_back();
        return true;
    }
    
    bool peek(T& item) const {
        if (items.empty()) return false;
        item = items.back();
        return true;
    }
    
    bool isEmpty() const {
        return items.empty();
    }
    
    int size() const {
        return items.size();
    }
    
    void clear() {
        items.clear();
    }
    
    std::vector<T> getAll() const {
        return items;
    }
};

#endif