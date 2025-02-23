#pragma once

#include <iostream>

/*
How to move through the tree:
	To go left, multiply the index by 2.
	To go right, multiply the index by 2 and add 1.
	To go up, divide the index by 2, if there is a remainder, that means it is the right child.
*/



template <typename T>
class Heap
{
public:


	virtual void insert(const T& data) = 0;
	virtual T top() const = 0;
	virtual void pop() = 0;
	virtual bool isEmpty() const = 0;
	virtual void erase(const T& data) = 0;

	virtual void siftup(size_t index) = 0;
	virtual void siftdown(size_t index) = 0;

	virtual void print() const = 0;



};


template <typename T>
class MaxHeap : public Heap<T>
{
	T* m_arr;
	T* m_back;
	T* m_end;

public:
	MaxHeap(size_t size);
	~MaxHeap();

	void insert(const T& data) override;

	inline T top() const override;
	void pop() override; // remove higher element

	bool isEmpty() const override { return m_back == m_arr; }

	void erase(const T& data) override; // remove element

private:
	static void siftup(size_t index, T* arr);
	static void siftdown(size_t index, T* arr, size_t size);
	inline void siftup(size_t index) override;
	inline void siftdown(size_t index) override;

public:
	void print() const override;

	static MaxHeap<T>* makeHeap(T* arr, size_t size);
	static T* heapSort(T* arr, size_t size);

};



template <typename T>
MaxHeap<T>::MaxHeap(size_t size)
{
	m_arr = new T[size];
	m_back = m_arr;
	m_end = m_arr + size;
}


template <typename T>
MaxHeap<T>::~MaxHeap()
{
	delete[] m_arr;
}

template <typename T>
void MaxHeap<T>::insert(const T& data)
{
	if (m_back == m_end) throw std::runtime_error("Heap lleno");
	*m_back = data;
	++m_back;
	siftup(m_back - m_arr - 1);
}

template <typename T>
T MaxHeap<T>::top() const
{
	return *m_arr;
}

template <typename T>
void MaxHeap<T>::pop()
{
	// Swamp with the last
	*m_arr = *(--m_back);
	siftdown(0);
}

template <typename T>
void MaxHeap<T>::erase(const T& data)
{
	// find the index of the element
	size_t size = m_back - m_arr;
	for (size_t i = 0; i < size; ++i)
	{
		if (m_arr[i] == data)
		{
			// Swamp with the last, and also decrese the limit
			m_arr[i] = *(--m_back);
			siftdown(i);
			return;
		}
	}
	// If the element is not found, do nothing
}

template <typename T>
void MaxHeap<T>::siftup(size_t index, T* arr)
{
	if (index == 0) return;

	// Compare with parent
	T* parent = arr + index / 2;
	T* current = arr + index;
	if (*parent < *current) // swamp
	{
		T temp = *parent;
		*parent = *current;
		*current = temp;
		siftup(index / 2, arr);
	}
}

template <typename T>
void MaxHeap<T>::siftdown(size_t index, T* arr, size_t size)
{
	size_t left = index * 2;
	size_t right = index * 2 + 1;

	if (left >= size) return; // No children

	size_t max = index;
	if (arr[left] > arr[max]) max = left;
	if (right < size && arr[right] > arr[max]) max = right;

	if (max != index) { // Swamp, if necesary
		T temp = arr[index];
		arr[index] = arr[max];
		arr[max] = temp;
		siftdown(max, arr, size);
	}
}

template <typename T>
void MaxHeap<T>::siftup(size_t index)
{
	siftup(index, m_arr);
}

template <typename T>
void MaxHeap<T>::siftdown(size_t index)
{
	siftdown(index, m_arr, m_back - m_arr);
}

template <typename T>
void MaxHeap<T>::print() const
{
	size_t index = 1; // Using index from [1, size]
	size_t size = m_back - m_arr;
	size_t iter = 0;

	int spaces = 0;

	while (iter < size) {
		for (int i = 0; i < spaces; ++i) std::cout << ' ' << '|';
		std::cout << m_arr[index-1] << '\n';

		if (index * 2 > size) { // has no left
			// Return to the parent from a left child, a left child is exacly the double of the parent
			// if we enter from the left child, means right child haven't been printed
			while (index % 2 != 0 || index + 1 > size) {
				index /= 2;
				spaces -= 1;
			}

			// Acces to the right child
			++index;
		}
		else {
			index *= 2;
			spaces += 1;
		}
		++iter;
	}
}


// The array must be full and dynimically allocated, the heap will take the ownership of the array
template <typename T>
MaxHeap<T>* MaxHeap<T>::makeHeap(T* arr, size_t size)
{
	MaxHeap<T>* heap = new MaxHeap<T>(0);
	delete heap->m_arr; // Delete the array created in the constructor, we will use the one passed as argument

	heap->m_arr = arr;
	heap->m_back = arr + size; // Supposing that the array is full
	heap->m_end = arr + size;

	// Sort
	for (size_t i = size / 2; i > 0; --i)
	{
		heap->siftdown(i);
	}
	heap->siftdown(0);

	return heap;
}

template <typename T>
T* MaxHeap<T>::heapSort(T* arr, size_t size)
{
	for (size_t i = size / 2; i > 0; --i)
	{
		siftdown(i, arr, size);
	}
	siftdown(0, arr, size);
	return arr;
}












////////////////////////////////////////////////////////

template <typename T>
class MinHeap : public Heap<T>
{
	T* m_arr;
	T* m_back;
	T* m_end;


public:
	MinHeap(size_t size);
	~MinHeap();

	void insert(const T& data) override;
	inline T top() const override;
	void pop() override; // remove higher element
	bool isEmpty() const override { return m_back == m_arr; }
	void erase(const T& data) override; // remove element

	static void siftup(size_t index, T* arr);
	static void siftdown(size_t index, T* arr, size_t size);
	inline void siftup(size_t index) override;
	inline void siftdown(size_t index) override;

	void print() const override;

};





template <typename T>
MinHeap<T>::MinHeap(size_t size)
{
	m_arr = new T[size];
	m_back = m_arr;
	m_end = m_arr + size;
}

template <typename T>
MinHeap<T>::~MinHeap()
{
	delete[] m_arr;
}

template <typename T>
void MinHeap<T>::insert(const T& data)
{
	if (m_back == m_end) throw std::runtime_error("Heap lleno");
	*m_back = data;
	++m_back;
	siftup(m_back - m_arr - 1);
}

template <typename T>
T MinHeap<T>::top() const
{
	return *m_arr;
}

template <typename T>
void MinHeap<T>::pop()
{
	// Swamp with the last
	*m_arr = *(--m_back);
	siftdown(0);
}

template <typename T>
void MinHeap<T>::erase(const T& data)
{
	// find the index of the element
	size_t size = m_back - m_arr;
	for (size_t i = 0; i < size; ++i)
	{
		if (m_arr[i] == data)
		{
			// Swamp with the last, and also decrese the limit
			m_arr[i] = *(--m_back);
			siftdown(i);
			return;
		}
	}
	// If the element is not found, do nothing
}


template <typename T>
void MinHeap<T>::siftup(size_t index, T* arr)
{
	if (index == 0) return;
	// Compare with parent
	T* parent = arr + index / 2;
	T* current = arr + index;
	if (*parent > *current) // swamp
	{
		T temp = *parent;
		*parent = *current;
		*current = temp;
		siftup(index / 2, arr); // siftup the parent
	}
}

template <typename T>
void MinHeap<T>::siftdown(size_t index, T* arr, size_t size)
{
	size_t left = index * 2;
	size_t right = index * 2 + 1;
	if (left >= size) return; // No children
	size_t min = index;
	if (arr[left] < arr[min]) min = left;
	if (right < size && arr[right] < arr[min]) min = right;
	if (min != index) { // Swamp, if necesary
		T temp = arr[index];
		arr[index] = arr[min];
		arr[min] = temp;
		siftdown(min, arr, size);
	}
}

template <typename T>
void MinHeap<T>::siftup(size_t index)
{
	siftup(index, m_arr);
}

template <typename T>
void MinHeap<T>::siftdown(size_t index)
{
	siftdown(index, m_arr, m_back - m_arr);
}

template <typename T>
void MinHeap<T>::print() const
{
	size_t index = 1; // Using index from [1, size]
	size_t size = m_back - m_arr;
	size_t iter = 0;
	int spaces = 0;
	
	while (iter < size) {
		for (int i = 0; i < spaces; ++i) std::cout << ' ' << '|';
		std::cout << m_arr[index - 1] << '\n';
		if (index * 2 > size) { // has no left
			// Return to the parent from a left child, a left child is exacly the double of the parent
			// if we enter from the left child, means right child haven't been printed
			while (index % 2 != 0 || index + 1 > size) {
				index /= 2;
				spaces -= 1;
			}
			// Acces to the right child
			++index;
		}
		else {
			index *= 2;
			spaces += 1;
		}
		++iter;
	}
}


////////////////////////////////////////////////////////

template <typename T, unsigned int childrenNum>
class HeapArray : public Heap<T>
{
	T* m_arr;
	T* m_back;
	T* m_end;


public:
	HeapArray(size_t size);
	~HeapArray();
	void insert(const T& data) override;
	inline T top() const override;
	void pop() override; // remove higher element
	bool isEmpty() const override { return m_back == 0; }
	void erase(const T& data) override; // remove element
	static void siftup(size_t index, T* arr);
	static void siftdown(size_t index, T* arr, size_t size);
	inline void siftup(size_t index) override;
	inline void siftdown(size_t index) override;
	void print() const override;
};


template <typename T, unsigned int childrenNum>
HeapArray<T, childrenNum>::HeapArray(size_t size)
{
	m_arr = new T[size];
	m_back = m_arr;
	m_end = m_arr + size;
}

template <typename T, unsigned int childrenNum>
HeapArray<T, childrenNum>::~HeapArray()
{
	delete[] m_arr;
}

template <typename T, unsigned int childrenNum>
void HeapArray<T, childrenNum>::insert(const T& data)
{
	if (m_back == m_end) throw std::runtime_error("Heap lleno");
	*m_back = data;
	++m_back;
	siftup(m_back - m_arr - 1);
}

template <typename T, unsigned int childrenNum>
T HeapArray<T, childrenNum>::top() const
{
	return *m_arr;
}

template <typename T, unsigned int childrenNum>
void HeapArray<T, childrenNum>::pop()
{
	// Swamp with the last
	*m_arr = *(--m_back);
	siftdown(0);
}

template <typename T, unsigned int childrenNum>
void HeapArray<T, childrenNum>::erase(const T& data)
{
	// find the index of the element
	size_t size = m_back - m_arr;
	for (size_t i = 0; i < size; ++i)
	{
		if (m_arr[i] == data)
		{
			// Swamp with the last, and also decrese the limit
			m_arr[i] = *(--m_back);
			siftdown(i);
			return;
		}
	}
	// If the element is not found, do nothing
}

template <typename T, unsigned int childrenNum>
void HeapArray<T, childrenNum>::siftup(size_t index, T* arr)
{
	if (index == 0) return;
	// Compare with parent
	T* parent = arr + index / childrenNum;
	T* current = arr + index;
	if (*parent > *current) // swamp
	{
		T temp = *parent;
		*parent = *current;
		*current = temp;
		siftup(index / childrenNum, arr); // siftup the parent
	}
}

template <typename T, unsigned int childrenNum>
void HeapArray<T, childrenNum>::siftdown(size_t index, T* arr, size_t size)
{
	if (index * childrenNum >= size) return; // No children
	size_t children[childrenNum];
	for (size_t i = 0; i < childrenNum; ++i)
	{
		children[i] = index * childrenNum + i;
	}

	// Find the minimum
	size_t min = index;
	for (size_t i = 0; i < childrenNum; ++i)
	{
		
		if (children[i] < size) // If the child exists
		{
			if (arr[children[i]] < arr[min]) min = children[i];
		}
		else break; // No more children
	}

	if (min != index) { // Swamp, if necesary
		T temp = arr[index];
		arr[index] = arr[min];
		arr[min] = temp;
		siftdown(min, arr, size);
	}

}

template <typename T, unsigned int childrenNum>
void HeapArray<T, childrenNum>::siftup(size_t index)
{
	siftup(index, m_arr);
}

template <typename T, unsigned int childrenNum>
void HeapArray<T, childrenNum>::siftdown(size_t index)
{
	siftdown(index, m_arr, m_back - m_arr);
}

template <typename T, unsigned int childrenNum>
void HeapArray<T, childrenNum>::print() const
{
	size_t index = 1; // Using index from [1, size]
	size_t size = m_back - m_arr;
	size_t iter = 0;
	int spaces = 0;
	while (iter < size) {
		for (int i = 0; i < spaces; ++i) std::cout << ' ' << '|';
		std::cout << m_arr[index - 1] << '\n';
			if (index * childrenNum > size) { // has no left
				// Return to the parent from a left child, a left child is exacly the double of the parent
				// if we enter from the left child, means right child haven't been printed
				while (index % childrenNum != 0 || index + 1 > size) {
					index /= childrenNum;
					spaces -= 1;
				}
				// Acces to the right child
				++index;
			}
			else {
				index *= childrenNum;
				spaces += 1;
			}
		++iter;
	}
}


