#pragma once
#include "MaxHeap.h"

template<typename T>
class PriorityQueue
{
private:
	MaxHeap<T> _root;
public:
	PriorityQueue();
	~PriorityQueue();

	friend std::ostream& operator<<(std::ostream& os, const PriorityQueue<T>& q);
};

template<typename T>
PriorityQueue<T>::PriorityQueue()
{
}

template<typename T>
PriorityQueue<T>::~PriorityQueue()
{
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const PriorityQueue<T>& q)
{
	os << q._root;
	return os;
}
