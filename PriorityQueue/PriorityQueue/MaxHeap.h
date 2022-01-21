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

	size_t getLeftIndex() const;
	size_t getRightIndex() const;

	void insert(MaxHeap<T>* node);
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

/* Get the index of the left child, using this->_index */
template<typename T>
inline size_t MaxHeap<T>::getLeftIndex() const
{
	return (this->_index + 1) * 2 - 1;
}

/* Get the index of the right child, using this->_index */
template<typename T>
inline size_t MaxHeap<T>::getRightIndex() const
{
	return (this->_index + 1) * 2;
}

/*
Insert a new node to the correct place in the heap.
Input: the node to insert.
*/
template<typename T>
inline void MaxHeap<T>::insert(MaxHeap<T>* node)
{
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
	this->insert(new MaxHeap<T>(this->_items, this->_items->size()));
	this->_items->push_back(value);
}

template<typename T>
inline T MaxHeap<T>::getMax() const
{
	return (*this->_items)[0];
}
