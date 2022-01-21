#pragma once
#include "MaxHeap.h"

template<typename T>
class PriorityQueue
{
private:
	MaxHeap<T>* _root;
public:
	PriorityQueue();
	~PriorityQueue();

	void push(const T& value);
	void pop();

	const T& top() const;
	bool empty() const;

	friend std::ostream& operator<<(std::ostream& os, const PriorityQueue<T>& q);
};

template<typename T>
PriorityQueue<T>::PriorityQueue()
{
	this->_root = nullptr;
}

template<typename T>
inline PriorityQueue<T>::~PriorityQueue()
{
	delete this->_root;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const PriorityQueue<T>& q)
{
	os << q._root;
	return os;
}
