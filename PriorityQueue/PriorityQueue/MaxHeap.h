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

	size_t _getLeftIndex() const;
	size_t _getRightIndex() const;


	void _swap(bool left);

	bool insert(MaxHeap<T>* node);
public:
	MaxHeap(const T& value);
	~MaxHeap();
	
	void insert(const T& value);
	void extractMax();

	const T& getValue() const;

	friend std::ostream& operator<<(std::ostream& os, const MaxHeap<T>& heap);
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
inline size_t MaxHeap<T>::_getLeftIndex() const
{
	return (this->_index + 1) * 2 - 1;
}

/* Get the index of the right child, using this->_index */
template<typename T>
inline size_t MaxHeap<T>::_getRightIndex() const
{
	return (this->_index + 1) * 2;
}

/*
Get the value of this node from the _items vector.
*/
template<typename T>
inline const T& MaxHeap<T>::getValue() const
{
	return (*this->_items)[this->_index];
}

/*
Swap the values this and one of its childs.
Input: whether to swap with the left child.
*/
template<typename T>
inline void MaxHeap<T>::_swap(bool left)
{
	MaxHeap<T>* childToSwap = left ? this->_left : this->_right;
	size_t tmpIndex = this->_index;
	T tmpValue = this->_items->at(tmpIndex);

	this->_items->at(this->_index) = childToSwap->getValue();
	childToSwap->_items->at(childToSwap->_index) = tmpValue;

	this->_index = childToSwap->_index;
	childToSwap->_index = tmpIndex;
}

/*
Insert a new node to the correct place in the heap.
Input: the node to insert.
Ouput: whether the node was inserted.
*/
template<typename T>
inline bool MaxHeap<T>::insert(MaxHeap<T>* node)
{
	bool left = false;

	if (this->_getLeftIndex() == node->_index)
	{
		this->_left = node;
	}
	else if (this->_getRightIndex() == node->_index)
	{
		this->_right = node;
	}
	// if the node can't be inserted to either of the children
	else if (!(this->_left && this->_left->insert(node)) &&
		!(this->_right && this->_right->insert(node)))
	{
		return false;
	}
	// if we reached here, the node has been inserted.
	if (left || this->getValue() < this->_right->getValue())
	{
		this->_swap(left);
	}
	return true;
}

template<typename T>
inline MaxHeap<T>::MaxHeap(const T& value)
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
	// delete all nodes recursively
	if (this->_left)
	{
		delete this->_left;
	}
	if (this->_right)
	{
		delete this->_right;
	}
}

/*
Insert a value to the heap.
Input: the value.
*/
template<typename T>
inline void MaxHeap<T>::insert(const T& value)
{
	this->insert(new MaxHeap<T>(this->_items, this->_items->size()));
	this->_items->push_back(value);
}

/*
Print all of the values in the items vector.
Input os: ouput stream to print the values to.
Input heap: the heap to print from.
Output: os.
*/
template<typename T>
std::ostream& operator<<(std::ostream& os, const MaxHeap<T>& heap)
{
	auto end = heap._items->end();

	for (auto i = heap._items->begin(); i != end; i++)
	{
		os << *i << std::endl;
	}
	return os;
}
