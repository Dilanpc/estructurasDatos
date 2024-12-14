#pragma once

#include <iostream>
#include "StaticArray.hpp"


template <typename T>
class DinamicArray : public StaticArray<T>
{
protected:
	using StaticArray<T>::m_arr;
	using StaticArray<T>::m_end;
	using StaticArray<T>::m_last;


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
	if (m_last >= m_end) // if the array is full
	{
		size_t size = m_end - m_arr; // size of the old array
		T* newArr = new T[size * 2];
		*newArr = value; // push first

		for (T* i = m_arr, *j = newArr + 1; i < m_last; ++i, ++j)
		{
			*j = *i;
		}

		delete[] m_arr;
		m_arr = newArr;
		m_last = newArr + size + 1; // +1 because we pushed first
		m_end = newArr + size * 2;

	}
	else
	{
		StaticArray<T>::pushFront(value);
	}
}

template <typename T>
void DinamicArray<T>::pushBack(const T& value)
{
	if (m_last >= m_end) // if the array is full
	{
		size_t size = m_end - m_arr; // size of the old array
		T* newArr = new T[size * 2];
		for (T* i = m_arr, *j = newArr; i < m_last; ++i, ++j)
		{
			*j = *i;
		}
		*(newArr + size) = value; // push last
		delete[] m_arr;
		m_arr = newArr;
		m_last = newArr + size + 1; // +1 because we pushed last
		m_end = newArr + size * 2;
	}
	else
	{
		StaticArray<T>::pushBack(value);
	}
}

