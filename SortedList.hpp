#pragma once

#include <iostream>
#include "StaticArray.hpp"

template<typename T>
class SortedList : protected StaticArray<T>
{
public:
	SortedList(size_t size);

protected:
	typename StaticArray<T>::Iterator search(const T& value) const;


public:
	void insert(const T& value);

	T* find(const T& value) const override;

	using StaticArray<T>::popFront;
	using StaticArray<T>::popBack;

	using StaticArray<T>::empty;
	using StaticArray<T>::print;

	using StaticArray<T>::begin;
	using StaticArray<T>::back;
	using StaticArray<T>::end;

	using StaticArray<T>::size;
	using StaticArray<T>::capacity;
	using StaticArray<T>::operator[];
};

template <typename T>
SortedList<T>::SortedList(size_t size)
	: StaticArray<T>(size)
{
}

template<typename T>
typename StaticArray<T>::Iterator SortedList<T>::search(const T& value) const
{
	auto left = begin();
	auto right = back();

	auto mid = begin();
	while (right - left > 0)
	{
		mid = left + (right - left) / 2; // get the middle of the two iterators
		if (*mid < value) // Move right
		{
			left = mid + 1; // +1 avoids infinite loop when left + 1 == right, also mid is already checked
		}
		else // Move left
		{
			right = mid;
		}
	}

	return right;
}

template <typename T>
void SortedList<T>::insert(const T& value) {
	StaticArray<T>::addBefore(search(value), value);
}

template <typename T>
T* SortedList<T>::find(const T& value) const
{
	auto it = search(value);

	if (it < back() && *it == value) {
		return &(*it);
	}

	return nullptr;
}