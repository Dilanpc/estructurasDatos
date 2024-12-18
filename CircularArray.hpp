#pragma once

#include <iostream>
#include "StaticArray.hpp"


template <typename T>
class CircularArray : public StaticArray<T>
{
	using StaticArray<T>::m_arr; // Aim to the first element of the array
	using StaticArray<T>::m_limit; // Aim to the next element of the array
	using StaticArray<T>::m_last; // Aim to the next available space
	T* front; // Aim to the first element
	bool full = false;


public:
	CircularArray(size_t size);

	void pushFront(const T& value) override;
	void pushBack(const T& value) override;

	T popFront() override;
	T popBack() override;

	size_t size() const override;

	void print() const override;

private:
	using StaticArray<T>::begin;
	using StaticArray<T>::end;
	using StaticArray<T>::back;

};



template <typename T>
CircularArray<T>::CircularArray(size_t size)
	: StaticArray<T>(size), front(m_arr)
{
}

template <typename T>
void CircularArray<T>::pushFront(const T& value)
{
	if (full) {
		throw std::runtime_error("Error: Lista llena. No se puede agregar el elemento.");
	}

	--front;
	if (front < m_arr) { // If the front is at the beginning of the array, move it to the end
		front = m_limit - 1;
	}
	*front = value;
	if (front == m_last) {
		full = true;
	}

}

template <typename T>
void CircularArray<T>::pushBack(const T& value) {
	if (full) {
		throw std::runtime_error("Error: Lista llena. No se puede agregar el elemento.");
	}
	
	*m_last = value;
	++m_last;
	if (m_last == m_limit) { // If the last is at the end of the array, move it to the beginning
		m_last = m_arr;
	}
	if (m_last == front) {
		full = true;
	}

}

template <typename T>
T CircularArray<T>::popFront() {
	if (front == m_last && !full) {
		throw std::runtime_error("Array is empty");
	}
	T value = *front;
	++front;
	if (front == m_limit) {  // If the front is at the end of the array, move it to the beginning
		front = m_arr;
	}
	full = false;
	return value;
}

template <typename T>
T CircularArray<T>::popBack()
{
	if (m_last == front && !full) {
		throw std::runtime_error("Error: Lista vacia. No se puede eliminar el elemento.");
	}
	--m_last;
	if (m_last < m_arr) { // If the last is at the beginning of the array, move it to the end
		m_last = m_limit - 1; // as m_last was pointing to the arr, we pop the last element of the array (m_limit-1)
	}
	if (full) {
		full = false;
	}
	return *m_last;
}


template <typename T>
size_t CircularArray<T>::size() const
{
	if (full) return m_limit - m_arr; // capacity
	if (front <= m_last) return m_last - front; // The array is contiguous
	return (m_limit - front) + (m_last - m_arr); // The array is not contiguous, so we need to sum the two parts
}

template <typename T>
void CircularArray<T>::print() const
{
	std::cout << "Elementos en el arreglo: [";
	T* it = front;
	if (front == m_last && !full) { // is empty
		std::cout << "]" << std::endl;
		return;
	}
	while (true) {
		std::cout << *it;
		++it;
		if (it == m_limit) {
			it = m_arr;
		}
		if (it == m_last) {
			break;
		}
		std::cout << " ";
	}
	std::cout << "]" << std::endl;
}