#pragma once
#include <vector>

template<typename T>
class MaxHeap
{
private:
	// the items in the heap
	std::vector<T>* _items;
	// the index of "this" in the items vector
	size_t _index;
	// left and right children
	MaxHeap<T>* _left;
	MaxHeap<T>* _right;

	// private methods
	MaxHeap(std::vector<T>* items, size_t index);
public:
	MaxHeap(T value);
	~MaxHeap();
	
	void insert(T value);
	void extractMax();

	T getMax() const;
};

/* Create a childless heap node */
template<typename T>
inline MaxHeap<T>::MaxHeap(std::vector<T>* items, size_t index) :
	_items(items), _index(index)
{
	this->_left = nullptr;
	this->_right = nullptr;
}

template<typename T>
inline MaxHeap<T>::MaxHeap(T value)
{
	this->_items = new std::vector<T>();
	this->_index = 0;
	this->_left = nullptr;
	this->_right = nullptr;

	this->_items->push_back(value);
}

template<typename T>
inline MaxHeap<T>::~MaxHeap()
{
	delete this->_items;
}

/*
Insert a value to the heap.
Input: the value.
*/
template<typename T>
inline void MaxHeap<T>::insert(T value)
{
}

template<typename T>
inline T MaxHeap<T>::getMax() const
{
	return (*this->_items)[0];
}
