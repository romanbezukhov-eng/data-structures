#ifndef DATA_STRUCTURES_TQUEUE_H
#define DATA_STRUCTURES_TQUEUE_H

#include "TVector.h"

constexpr int defaultStartCapacity = 4;

template <class T, class TContainer = TVector<T>>
class TQueue {
private:
	TContainer data;
	size_t head = 0;
	size_t count = 0;

	void grow(size_t newN);
public:
	TQueue();
	explicit TQueue(size_t count);

	void push(const T& value);
	void pop();
	T &front();
	const T &front() const;
	T &back();
	const T &back() const;
	bool empty() const;
	size_t size() const;
	void clear();

	friend std::ostream& operator<<(std::ostream& os, const TQueue<T, TContainer>& queue) {
		for (size_t i = 0; i < queue.count; i++) {
			os << queue.data[(queue.head + i) % queue.data.size()] << " ";
		}
		return os;
	}

	friend std::istream& operator>>(std::istream& is, TQueue& queue) {
		std::string line;
		if (std::getline(is, line)) {
			std::stringstream ss(line);
			T value;
			while (ss >> value) {
				queue.push(value);
			}
		}
		return is;
	}
};

template <class T, class TContainer>
inline TQueue<T, TContainer>::TQueue() : data(defaultStartCapacity), head(0), count(0) {}

template <class T, class TContainer>
inline TQueue<T, TContainer>::TQueue(size_t n) : data(n), head(0) {
	if (data.size() == 0){
		grow(defaultStartCapacity);
	}
}

template <class T, class TContainer>
inline void TQueue<T, TContainer>::push(const T& value) {
	if (count == data.size()) {
		grow(data.size()*2);
	}
	data[(head + count) % data.size()] = value;
	count++;
}

template <class T, class TContainer>
inline void TQueue<T, TContainer>::pop() {
	if (count == 0) {
		throw std::out_of_range("Queue is empty");
	}
	head = (head + 1) % data.size();
	count--;
}

template <class T, class TContainer>
inline T& TQueue<T, TContainer>::front() {
	if (count == 0) {
		throw std::out_of_range("Queue is empty");
	}
	return data[head];
}

template <class T, class TContainer>
inline T& TQueue<T, TContainer>::back() {
	if (count == 0) {
		throw std::out_of_range("Queue is empty");
	}
	return data[(head + count - 1) % data.size()];
}

template <class T, class TContainer>
inline const T& TQueue<T, TContainer>::front() const {
	if (count == 0) {
		throw std::out_of_range("Queue is empty");
	}
	return data[head];
}

template <class T, class TContainer>
inline const T& TQueue<T, TContainer>::back() const {
	if (count == 0) {
		throw std::out_of_range("Queue is empty");
	}
	return data[(head + count - 1) % data.size()];
}

template <class T, class TContainer>
inline bool TQueue<T, TContainer>::empty() const {
	return count == 0;
}

template <class T, class TContainer>
inline size_t TQueue<T, TContainer>::size() const {
	return count;
}

template <class T, class TContainer>
inline void TQueue<T, TContainer>::clear() {
	TContainer tmp(defaultStartCapacity);
	data = tmp;
	head = 0;
	count = 0;
}

template <class T, class TContainer>
inline void TQueue<T, TContainer>::grow(size_t newN) {
	TContainer tmp(newN);
	for (size_t i = 0; i < data.size(); i++) {
		tmp[i] = data[(head+i) % data.size()];
	}
	data = tmp;
	head = 0;
}
#endif //DATA_STRUCTURES_TQUEUE_H