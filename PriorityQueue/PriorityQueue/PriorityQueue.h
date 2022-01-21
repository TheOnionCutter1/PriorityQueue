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

	friend std::ostream& operator<<(std::ostream& os, const PriorityQueue& q);
};

template<typename T>
PriorityQueue<T>::PriorityQueue()
{
}

template<typename T>
PriorityQueue<T>::~PriorityQueue()
{
}
