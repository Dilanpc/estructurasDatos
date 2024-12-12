#pragma once

#include <iostream>

template <typename T>
class Stack
{
	T* bottom;
	T* last;
	T* end;


public:
	Stack(size_t size);
	~Stack();

	void push(const T& value);
	T pop(); // Returns a copy
	T& top();

	void empty();
	size_t size() const { return last - bottom; }

};

template <typename T>
Stack<T>::Stack(size_t size)
	: bottom(new T[size]),
	last(bottom), end(bottom + size)
{
}

template <typename T>
Stack<T>::~Stack() {
	delete[] bottom;
}

template <typename T>
void Stack<T>::push(const T& value) {
	if (last > end) {
		std::cout << "Stack Overflow" << std::endl;
		return;
	}
	*last = value;
	++last;
}

template <typename T>
T Stack<T>::pop() {
	if (bottom == last) {
		return 0;
	}
	return *(--last);
}

template <typename T>
T& Stack<T>::top() {
	return *(last - 1);
}

template <typename T>
void Stack<T>::empty()
{
	last = bottom;
}