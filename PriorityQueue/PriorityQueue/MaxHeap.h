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
	MaxHeap();
	~MaxHeap();
	
	void insert(T value);
	void extractMax();

	T getMax() const;
};

template<typename T>
inline MaxHeap<T>::MaxHeap()
{
	this->_items = new std::vector<T>();
	this->_index = 0;
	this->_left = nullptr;
	this->_right = nullptr;
}

template<typename T>
inline MaxHeap<T>::~MaxHeap()
{
	delete this->_items;
}
