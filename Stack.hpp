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
	size_t capacity() const { return end - bottom; }

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
		throw std::runtime_error("Stack Overflow");
	}
	*last = value;
	++last;
}

template <typename T>
T Stack<T>::pop() {
	if (bottom == last) {
		throw std::runtime_error("Stack Underflow");
	}
	return *(--last);
}

template <typename T>
T& Stack<T>::top() {
	if (bottom == last) {
		throw std::runtime_error("Stack Underflow");
	}
	return *(last - 1);
}

template <typename T>
void Stack<T>::empty()
{
	last = bottom;
}