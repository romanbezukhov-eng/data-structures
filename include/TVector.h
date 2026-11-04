#pragma once

#include <stdexcept>
#include <cstddef>


const int FACTOR = 2;

template <typename T>
class TVector {
private:
    size_t n = 0;
    size_t capacity = 1;
    T *data = nullptr;

    void reserve(size_t newCapacity);
    void resize(size_t newN);
public:
    TVector();
    explicit TVector(size_t n, const T& value = T());
    TVector(const TVector<T> &v);
    ~TVector();
    TVector<T>& operator= (const TVector<T> &v);

    using iterator = T*;
    using const_iterator = const T*;

    iterator begin() { return data; }
    iterator end() { return data + n; }
    const_iterator begin() const { return data; }
    const_iterator end() const { return data + n; }
    const_iterator cbegin() const { return data; }
    const_iterator cend() const { return data + n; }

    size_t size() const { return n; }
    size_t getCapacity() const { return capacity; }

    const T& operator[] (size_t index) const { return data[index]; }
    T& operator[] (size_t index) { return data[index]; }

    T& at(size_t index);
    const T& at(size_t index) const;

    void push_back (const T& value);
    void pop_back();
    void insert(size_t index, const T& value);
    void erase(size_t index);
    void clear();
    bool empty() const;

    T& front() {
        if (n==0) throw std::out_of_range("TVector is empty");
        return data[0];
    }
    T& back() {
        if (n==0) throw std::out_of_range("TVector is empty");
        return data[n - 1];
    }
    const T& front() const {
        if (n==0) throw std::out_of_range("TVector is empty");
        return data[0];
    }
    const T& back() const {
        if (n==0) throw std::out_of_range("TVector is empty");
        return data[n - 1];
    }
};

template <typename T>
inline TVector<T>::TVector() : n(0), capacity(1) {
    data = new T[capacity];
}

template <typename T>
inline TVector<T>::TVector(size_t n_, const T& value) : n(n_) {
    if (n > 0) {
        capacity = FACTOR * n;
    } else {
        capacity = 1;
    }
    data = new T[capacity];
    for (size_t i = 0; i < n; i++) {
        data[i] = value;
    }
}

template <typename T>
inline TVector<T>::TVector(const TVector<T> &v) {
    n = v.n;
    capacity = v.capacity;
    data = new T[capacity];
    for (size_t i = 0; i < n; i++) {
        data[i] = v.data[i];
    }
}

template <typename T>
inline TVector<T>::~TVector() {
    delete[] data;
}

template <typename T>
inline TVector<T>& TVector<T>::operator=(const TVector<T> &v) {
    if (this != &v) {
        T* tmp = new T[v.capacity];
        for (size_t i = 0; i < v.n; i++) {
            tmp[i] = v.data[i];
        }
        delete[] data;
        data = tmp; n = v.n; capacity = v.capacity;
    }
    return *this;
}

template <typename T>
inline T& TVector<T>::at(size_t index) {
    if (index >= 0 && static_cast<size_t>(index) < n) {
        return data[index];
    }
    throw std::out_of_range("index out of range");
}

template <typename T>
inline const T& TVector<T>::at(size_t index) const {
    if (index >= 0 && static_cast<size_t>(index) < n) {
        return data[index];
    }
    throw std::out_of_range("index out of range");
}

template <typename T>
void TVector<T>::reserve(size_t newCapacity) {
    if (newCapacity <= capacity) {
        return;
    }
    T *tmp = new T[newCapacity];
    for (size_t i = 0; i < n; i++) {
        tmp[i] = data[i];
    }
    delete[] data;
    data = tmp;
    capacity = newCapacity;
}

template <typename T>
void TVector<T>::resize(size_t newN) {
    if (newN <= n) {
        n = newN;
        return;
    }
    if (newN <= capacity) {
        for (size_t i = n; i < newN; i++) {
            data[i] = T();
        }
        n = newN;
        return;
    }
    reserve(newN * FACTOR);
    for (size_t i = n; i < newN; i++) {
        data[i] = T();
    }
    n = newN;
}

template <typename T>
void TVector<T>::push_back(const T& value) {
    if (n == capacity) {
        reserve(capacity * FACTOR);
    }
    data[n++] = value;
}

template <typename T>
void TVector<T>::pop_back() {
    if (n == 0) {
        return;
    }
    n--;
}

template <typename T>
void TVector<T>::insert(size_t index, const T& value) {
    if (index > n) {
        throw std::out_of_range("index out of range");
    }
    if (n == capacity) {
        reserve(capacity * FACTOR);
    }
    for (size_t i = n; i > index; i--) {
        data[i] = data[i - 1];
    }
    data[index] = value;
    n++;
}

template <typename T>
void TVector<T>::erase(size_t index) {
    if (index >= n) {
        throw std::out_of_range("index out of range");
    }
    for (size_t i = index; i < n - 1; i++) {
        data[i] = data[i + 1];
    }
    n--;
}

template <typename T>
void TVector<T>::clear() {
    T* newData = new T[1]; // если будет исключение, то не дата не удалится
    delete[] data;
    data = newData;
    n = 0;
    capacity = 1;

}

template <typename T>
inline bool TVector<T>::empty() const {
    return n == 0;
}