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

	void _setValue(const T& value);

	size_t _getLeftIndex() const;
	size_t _getRightIndex() const;
	void _swap(bool left);

	bool _insert(MaxHeap<T>* node);

	MaxHeap<T>* _findLast(size_t lastIndex);

public:
	MaxHeap(const T& value);
	~MaxHeap();
	
	void insert(const T& value);
	void extractMax();

	size_t size() const;

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

/*
Set a new value for this node.
Input: the value.
*/
template<typename T>
inline void MaxHeap<T>::_setValue(const T& value)
{
	this->_items->at(this->_index) = value;
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
	return this->_items->at(this->_index);
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

	this->_setValue(childToSwap->getValue());
	childToSwap->_setValue(tmpValue);

	this->_index = childToSwap->_index;
	childToSwap->_index = tmpIndex;
}

/*
Insert a new node to the correct place in the heap.
Input: the node to insert.
Ouput: whether the node was inserted.
*/
template<typename T>
inline bool MaxHeap<T>::_insert(MaxHeap<T>* node)
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
	else if (!(this->_left && this->_left->_insert(node)) &&
		!(this->_right && this->_right->_insert(node)))
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

/*
Find the last node (the node that represents the last element in the vector).
Input: the index of the last element
*/
template<typename T>
inline MaxHeap<T>* MaxHeap<T>::_findLast(size_t lastIndex)
{
	MaxHeap<T>* last = nullptr;

	if (this->_index == lastIndex)
	{
		last = this;
	}
	else
	{
		if (this->_left)
		{
			last = this->_left->_findLast(lastIndex);
		}
		if (!last && this->_right)
		{
			last = this->_right->_findLast(lastIndex);
		}
	}
	return last;
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
	this->_items = nullptr;
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
	this->_insert(new MaxHeap<T>(this->_items, this->_items->size()));
	this->_items->push_back(value);
}

/*
Remove the maximum value (the root) from the heap.
Calling this function with only one node left will result in undefined behavior.
*/
template<typename T>
inline void MaxHeap<T>::extractMax()
{
	size_t lastIndex = this->_items->size() - 1;
	MaxHeap<T>* temp = this->_findLast(lastIndex);
	bool left = false; // who to swap with

	this->_setValue(temp->getValue());
	delete temp;
	temp = this;
	// while temp has at least one child
	while (temp->_left || temp->_right)
	{
		if (temp->_left)
		{
			if (temp->_right)
			{
				// prepare for a swap with the larger child
				left = temp->_right->getValue() < temp->_left->getValue() ?
					temp->_left : temp->_right;
			}
			else
			{
				left = true;
			}
		}
		else if (temp->_right)
		{
			left = false;
		}
		temp->_swap(left);
		temp = left ? temp->_left : temp->_right;
	}
}

/* get the size of the heap */
template<typename T>
inline size_t MaxHeap<T>::size() const
{
	return this->_items->size();
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
