#include <iostream>

template <typename T>
class Queue
{
	T* arr;
	T* front;
	T* back;
	T* end;
	bool full = false;
public:
	Queue(size_t size);
	~Queue() { delete[] arr; }

	void enq(const T& value);
	T deq();

	size_t size();
};

template <typename T>
Queue<T>::Queue(size_t size)
	: arr(new T[size]),
	front(arr), back(arr), end(arr + size)
{
}

template <typename T>
void Queue<T>::enq(const T& value) {
	if (!full) { // If the queue is not full
		*back = value;
		++back;
		if (back == end) {
			back = arr;
		}
		if (back == front) {
			full = true;
		}
	}
	else {
		throw std::runtime_error("Queue is full");
	}
}

template <typename T>
T Queue<T>::deq() {
	if (front == back && !full) {
		throw std::runtime_error("Queue is empty");
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
size_t Queue<T>::size()
{
	if (full) return end - arr;
	if (front <= back) return back - front;
	return (end - front) + (back - arr);
}