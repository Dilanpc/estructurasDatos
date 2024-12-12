#pragma once

#include "LinkedListS.hpp"

template <typename T>
class LinkedListT : public LinkedListS<T>
{
	using Node = typename LinkedListS<T>::Node;
	using LinkedListS<T>::head;

	class Iterator : public LinkedListS<T>::Iterator
	{
		friend class LinkedListT<T>;
	public:
		Iterator(Node* node) : LinkedListS<T>::Iterator(node) {}
	};

	Node* tail{};
public:

	void pushFront(const T& value) override;
	void pushBack(const T& value) override;

	T popFront() override;
	T popBack() override;

	void addAfter(Iterator it, T value);

};

template <typename T>
void LinkedListT<T>::pushFront(const T& value)
{
	Node* node = new Node(value);

	node->next = head;
	head = node;

	if (tail == nullptr) {
		tail = head;
	}
}

template <typename T>
void LinkedListT<T>::pushBack(const T& value)
{
	Node* node = new Node(value);

	if (!head) { // There is no elements
		head = node;
		tail = head;
	}
	else {
		tail->next = node;
		tail = node;
	}
}

template <typename T>
T LinkedListT<T>::popFront()
{
	if (!head) {
		throw std::runtime_error("Error: Lista vacia. No se puede eliminar el elemento.");
	}
	if (head == tail) {
		T value = head->value;
		delete head;
		head = nullptr;
		tail = nullptr;
		return value;
	}
	else {
		T value = head->value;
		Node* temp = head;
		head = head->next;
		delete temp;
		return value;
	}
}

template <typename T>
T LinkedListT<T>::popBack()
{
	if (!tail) {
		throw std::runtime_error("Error: Lista vacia. No se puede eliminar el elemento.");
	}
	if (tail == head) { // There is only one element
		T value = tail->value;
		delete tail;
		tail = nullptr;
		head = nullptr;
		return value;
	}
	else {
		Node* current = head;
		while (current->next != tail) {
			current = current->next;
		}
		T value = tail->value;
		delete tail;
		tail = current;
		tail->next = nullptr;
		return value;
	}
}


template <typename T>
void LinkedListT<T>::addAfter(Iterator it, T value)
{
	Node* node = new Node(value);
	node->next = it.current->next;
	it.current->next = node;
	if (it.current == tail) {
		tail = node;
	}
}
