#pragma once

#include <iostream>
#include "StaticArray.hpp"

// vjudge.com


template <typename T>
class DinamicArray : public StaticArray<T>
{
protected:
	using StaticArray<T>::arr;
	using StaticArray<T>::end;
	using StaticArray<T>::last;


public:
	DinamicArray();
	DinamicArray(size_t size);

	void pushFront(const T& value) override;
	void pushBack(const T& value) override;

};

template <typename T>
DinamicArray<T>::DinamicArray()
	: StaticArray<T>(2)
{
}

template <typename T>
DinamicArray<T>::DinamicArray(size_t size)
	: StaticArray<T>(size)
{
}

template <typename T>
void DinamicArray<T>::pushFront(const T& value)
{
	if (last >= end) // if the array is full
	{
		size_t size = end - arr; // size of the old array
		T* newArr = new T[size * 2];
		*newArr = value; // push first

		for (T* i = arr, *j = newArr + 1; i < last; ++i, ++j)
		{
			*j = *i;
		}

		delete[] arr;
		arr = newArr;
		last = newArr + size + 1; // +1 because we pushed first
		end = newArr + size * 2;

	}
	else
	{
		StaticArray<T>::pushFront(value);
	}
}

template <typename T>
void DinamicArray<T>::pushBack(const T& value)
{
	if (last >= end) // if the array is full
	{
		size_t size = end - arr; // size of the old array
		T* newArr = new T[size * 2];
		for (T* i = arr, *j = newArr; i < last; ++i, ++j)
		{
			*j = *i;
		}
		*(newArr + size) = value; // push last
		delete[] arr;
		arr = newArr;
		last = newArr + size + 1; // +1 because we pushed last
		end = newArr + size * 2;
	}
	else
	{
		StaticArray<T>::pushBack(value);
	}
}

