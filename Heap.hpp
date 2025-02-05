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
	T* m_arr;
	T* m_back;
	T* m_end;

public:
	Heap(size_t size);
	~Heap();

	void insert(const T& data);

	T getMax() const;
	void pop(); // remove higher element

	void erease(const T& data); // remove element

private:
	static void siftup(size_t index, T* arr);
	static void siftdown(size_t index, T* arr, size_t size);
	void siftup(size_t index);
	void siftdown(size_t index);

public:
	void print() const;

	static Heap<T>* makeHeap(T* arr, size_t size); // for i [n/2, 0] siftDown(i)
	static T* heapSort(T* arr, size_t size);
};



template <typename T>
Heap<T>::Heap(size_t size)
{
	m_arr = new T[size];
	m_back = m_arr;
	m_end = m_arr + size;
}


template <typename T>
Heap<T>::~Heap()
{
	delete[] m_arr;
}

template <typename T>
void Heap<T>::insert(const T& data)
{
	if (m_back == m_end) throw std::runtime_error("Heap lleno");
	*m_back = data;
	++m_back;
	siftup(m_back - m_arr - 1);
}

template <typename T>
T Heap<T>::getMax() const
{
	return *m_arr;
}

template <typename T>
void Heap<T>::pop()
{
	// Swamp with the last
	*m_arr = *(--m_back);
	siftdown(0);
}

template <typename T>
void Heap<T>::erease(const T& data)
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
void Heap<T>::siftup(size_t index, T* arr)
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
void Heap<T>::siftdown(size_t index, T* arr, size_t size)
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
void Heap<T>::siftup(size_t index)
{
	siftup(index, m_arr);
}

template <typename T>
void Heap<T>::siftdown(size_t index)
{
	siftdown(index, m_arr, m_back - m_arr);
}

template <typename T>
void Heap<T>::print() const
{
	size_t index = 1; // Using index from [1, size]
	size_t size = m_back - m_arr;
	size_t capacity = m_end - m_arr;
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

template <typename T>
Heap<T>* Heap<T>::makeHeap(T* arr, size_t size)
{
	Heap<T>* heap = new Heap<T>(0);
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
T* Heap<T>::heapSort(T* arr, size_t size)
{
	for (size_t i = size / 2; i > 0; --i)
	{
		siftdown(i, arr, size);
	}
	siftdown(0, arr, size);
	return arr;
}