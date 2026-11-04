#ifndef DATA_STRUCTURES_TSTACK_H
#define DATA_STRUCTURES_TSTACK_H

#include "TVector.h"
#include <stdexcept>

template <typename T, typename TContainer = TVector<T>>
class TStack {
private:
    TContainer data;
public:
    void push(const T& el);
    void pop();
    T& top();
    const T& top() const;
    bool empty() const;
    size_t size() const;
    void clear();

};

template <typename T, typename TContainer>
inline void TStack<T, TContainer>::push(const T& el) {
    data.push_back(el);
}

template <typename T, typename TContainer>
inline void TStack<T, TContainer>::pop() {
    if (data.empty()) {
        throw std::out_of_range("Stack is empty");
    }
    data.pop_back();
}

template <typename T, typename TContainer>
inline T& TStack<T, TContainer>::top() {
    if (data.empty()) {
        throw std::out_of_range("Stack is empty");
    }
    return data.back();
}

template <typename T, typename TContainer>
inline const T& TStack<T, TContainer>::top() const {
    if (data.empty()) {
        throw std::out_of_range("Stack is empty");
    }
    return data.back();
}

template <typename T, typename TContainer>
inline bool TStack<T, TContainer>::empty() const {
    return data.empty();
}

template <typename T, typename TContainer>
inline size_t TStack<T, TContainer>::size() const {
    return data.size();
}

template <typename T, typename TContainer>
inline void TStack<T, TContainer>::clear() {
    data.clear();
}


#endif //DATA_STRUCTURES_TSTACK_H