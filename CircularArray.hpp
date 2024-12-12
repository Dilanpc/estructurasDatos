#pragma once

#include <iostream>
#include "StaticArray.hpp"


template <typename T>
class CircularArray : public StaticArray<T>
{
	using StaticArray<T>::arr;
	using StaticArray<T>::end;
	using StaticArray<T>::last;
	T* front;
	bool full = false;
public:
	CircularArray(size_t size);

	void pushFront(const T& value) override;
	void pushBack(const T& value) override;

	T popFront() override;
	T popBack() override;

	size_t size();

	void print() const override;

};



template <typename T>
CircularArray<T>::CircularArray(size_t size)
	: StaticArray<T>(size), front(arr)
{
}

template <typename T>
void CircularArray<T>::pushFront(const T& value)
{
	if (full) {
		throw std::runtime_error("Error: Lista llena. No se puede agregar el elemento.");
	}

	--front;
	if (front < arr) {
		front = end - 1;
	}
	*front = value;
	if (front == last) {
		full = true;
	}

}

template <typename T>
void CircularArray<T>::pushBack(const T& value) {
	if (!full) { // If the queue is not full
		*last = value;
		++last;
		if (last == end) {
			last = arr;
		}
		if (last == front) {
			full = true;
		}
	}
	else {
		throw std::runtime_error("Error: Lista llena. No se puede agregar el elemento.");
	}
}

template <typename T>
T CircularArray<T>::popFront() {
	if (front == last && !full) {
		throw std::runtime_error("Array is empty");
	}
	T value = *front;
	++front;
	if (front == end) {
		front = arr;
	}
	full = false;
	return value;
}

template <typename T>
T CircularArray<T>::popBack()
{
	if (last == front && !full) {
		throw std::runtime_error("Error: Lista vacia. No se puede eliminar el elemento.");
	}
	--last;
	if (last < arr) {
		last = end - 1;
	}
	if (full) {
		full = false;
	}
	return *last;
}


template <typename T>
size_t CircularArray<T>::size()
{
	if (full) return end - arr;
	if (front <= last) return last - front;
	return (end - front) + (last - arr);
}

template <typename T>
void CircularArray<T>::print() const
{
	std::cout << "Elementos en el arreglo: [";
	T* it = front;
	if (front == last && !full) { // is empty
		std::cout << "]" << std::endl;
		return;
	}
	while (true) {
		std::cout << *it;
		++it;
		if (it == end) {
			it = arr;
		}
		if (it == last) {
			break;
		}
		std::cout << " ";
	}
	std::cout << "]" << std::endl;
}