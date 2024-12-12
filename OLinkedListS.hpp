#pragma once

#include <iostream>
#include "LinkedListS.hpp"

template<typename T>
class OLinkedListS : protected LinkedListS<T>
{
protected:
	using LinkedListS<T>::head;

	typename LinkedListS<T>::Iterator search(const T& value) const;

public:
	void insert(const T& value);

	using LinkedListS<T>::popFront;
	using LinkedListS<T>::popBack;

	using LinkedListS<T>::empty;
	using LinkedListS<T>::print;

	using LinkedListS<T>::begin;
	using LinkedListS<T>::end;
};




template <typename T>
typename LinkedListS<T>::Iterator OLinkedListS<T>::search(const T& value) const
{
	typename LinkedListS<T>::Iterator it(head);
	typename LinkedListS<T>::Iterator prev(nullptr);

	while (it != LinkedListS<T>::end() && *it < value) {
		prev = it;
		++it;
	}

	return prev;
}

template <typename T>
void OLinkedListS<T>::insert(const T& value)
{
	auto it = search(value);
	if (it == nullptr) {
		LinkedListS<T>::pushFront(value);
	}
	else {
		LinkedListS<T>::addAfter(search(value), value);
	}
}