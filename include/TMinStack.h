#ifndef DATA_STRUCTURES_TMINSTACK_H
#define DATA_STRUCTURES_TMINSTACK_H

#include "TStack.h"

template <class T>
class TMinStack {
    TStack<T> dataStack;
    TStack<T> minStack;

public:
    void push(const T& el) {
        dataStack.push(el);
        if (minStack.empty() || el <= minStack.top()) {
            minStack.push(el);
        }
    }

    void pop(){
        if (dataStack.empty()) {
            throw std::out_of_range("Stack is empty");
        }
        if (dataStack.top() == minStack.top()) {
            minStack.pop();
        }
        dataStack.pop();

    }

    T& top(){
        if (dataStack.empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return dataStack.top();
    }

    const T& top() const{
        if (dataStack.empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return dataStack.top();
    }

    bool empty() const {
        return dataStack.empty();
    }

    size_t size() const{
        return dataStack.size();
    }

    void clear(){
        dataStack.clear();
        minStack.clear();
    }

    friend std::ostream& operator<<(std::ostream& os, const TMinStack& stack) {
        os << stack.dataStack;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, TMinStack& stack) {
        is >> stack.dataStack;
        return is;
    }

    const T& min() const {
        if (dataStack.empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return minStack.top();
    }

    void print(std::ostream& os = std::cout) const {
        os << "dataStack: " << dataStack << "\n";
        os << "minStack: " << minStack << "\n";
    }
};


#endif //DATA_STRUCTURES_TMINSTACK_H