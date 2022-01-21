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

	void print() const;
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

/*
Push a value to the queue.
Input: the value.
*/
template<typename T>
inline void PriorityQueue<T>::push(const T& value)
{
	if (this->_root)
	{
		this->_root->insert(value);
	}
	else
	{
		this->_root = new MaxHeap<T>(value);
	}
}

/* Pop the first value in the queue. */
template<typename T>
inline void PriorityQueue<T>::pop()
{
	if (this->_root->size() == 1)
	{
		delete this->_root;
		this->_root = nullptr;
	}
	else
	{
		this->_root->extractMax();
	}
}

/* Get the first value in the queue */
template<typename T>
inline const T& PriorityQueue<T>::top() const
{
	return this->_root->getValue();
}

/* Check if the queue is empty */
template<typename T>
inline bool PriorityQueue<T>::empty() const
{
	return this->_root->size() == 0;
}

/* print the queue */
template<typename T>
inline void PriorityQueue<T>::print() const
{
	if (this->_root)
	{
		this->_root->print();
	}
}
