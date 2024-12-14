#pragma once

#include <iostream>
#include "LinkedListS.hpp"


template <typename T>
class LinkedListD : public LinkedListS<T>
{
protected:
	struct Node
	{
		Node() = default;
		Node(T value) : value(value) {}
		T value;
		Node* prev{};
		Node* next{};
	};

	class Iterator
	{
		Node* current;
	public:
		Iterator(Node* node) : current(node) {}

		T& operator*() { return current->value; }

		Iterator& operator++() { current = current->next; return *this; }

		bool operator==(const Iterator& other) const {
			return current == other.current;
		}

		bool operator!=(const Iterator& other) const {
			return current != other.current;
		}
		bool operator!=(const Node* other) {
			return current != other;
		}

		void advance(size_t n) {
			while (n-- && current) ++(*this);
		}

		friend class LinkedListD;
	};



	Node* head{}; // overrides LinkedListS<T>::head
	Node* tail{};

public:
	~LinkedListD();

	void pushFront(const T& value) override;
	void pushBack(const T& value) override;
	void pushBack(LinkedListD<T>& list); // Append a list, the other list will be empty

	T popFront() override;
	T popBack() override;

	T* find(const T& value) const override;
	void erase(T* element) override;

	void addBefore(Iterator it, T value);
	void addAfter(Iterator it, T value);

	void empty() override;

	void print() const override;

	Iterator begin() { return Iterator(head); }
	Iterator end() { return nullptr; }

private:
	using LinkedListS<T>::pushBack;
};

template <typename T>
LinkedListD<T>::~LinkedListD()
{
	empty();
}

template <typename T>
void LinkedListD<T>::pushFront(const T& value)
{
	Node* node = new Node(value);

	node->next = head;

	if (!head) { // There is no elements
		tail = node;
	}
	else {
		head->prev = node;
	}
	head = node;
}


template<typename T>
void LinkedListD<T>::pushBack(const T& value)
{
	Node* node = new Node(value);
	if (tail) {
		node->prev = tail;
		tail->next = node;
		tail = node;
	}
	else {
		tail = node;
		head = node;
	}
}

template <typename T>
void LinkedListD<T>::pushBack(LinkedListD<T>& list)
{
	if (!head) {
		head = list.head;
		tail = list.tail;
	}
	else {
		tail->next = list.head;
		list.head->prev = tail;
		tail = list.tail;
	}
	list.head = nullptr; // empty the list, the memory now is managed by this list
	list.tail = nullptr;
}

template <typename T>
T LinkedListD<T>::popFront()
{
	if (!head) {
		throw std::runtime_error("Error: Lista vacia. No se puede eliminar el elemento.");
	}
	Node* toDelete = head;
	T value = toDelete->value;
	head = head->next;
	delete toDelete;
	if (head)
	{
		head->prev = nullptr;
	}
	return value;
}

template <typename T>
T LinkedListD<T>::popBack()
{
	if (!tail) {
		throw std::runtime_error("Error: Lista vacia. No se puede eliminar el elemento.");
	}

	Node* toDelete = tail;
	T value = toDelete->value;
	tail = tail->prev;
	delete toDelete;
	if (tail) {
		tail->next = nullptr;
	}
	else { // If the last element was deleted
		head = nullptr;
	}
	return value;
}

template <typename T>
T* LinkedListD<T>::find(const T& value) const
{
	for (Node* current = head; current; current = current->next) {
		if (current->value == value) {
			return &current->value;
		}
	}
	return nullptr;
}

template <typename T>
void LinkedListD<T>::erase(T* element)
{
	Node* toDelete{};
	for (Node* current = head; current; current = current->next) {
		if (&current->value == element) {
			toDelete = current;
			break;
		}
	}
	if (toDelete == head) {
		head = toDelete->next;
	}
	if (toDelete == tail) {
		tail = toDelete->prev;
	}
	if (toDelete->prev) {
		toDelete->prev->next = toDelete->next;
	}
	if (toDelete->next) {
		toDelete->next->prev = toDelete->prev;
	}
	delete toDelete;
}

template <typename T>
void LinkedListD<T>::addBefore(Iterator it, T value)
{
	if (!it.current) {
		std::cout << "Error: Iterator invalido." << std::endl;
		return;
	}
	Node* node = new Node(value);
	Node* current = it.current;
	node->next = current;
	node->prev = current->prev;
	if (current->prev) {
		current->prev->next = node;
	}
	else { // current is head
		head = node;
	}
	current->prev = node;
}

template <typename T>
void LinkedListD<T>::addAfter(Iterator it, T value)
{
	if (!it.current) {
		std::cout << "Error: Iterator invalido." << std::endl;
		return;
	}
	Node* node = new Node(value);
	Node* current = it.current;
	node->next = current->next;
	node->prev = current;
	if (current->next) {
		current->next->prev = node;
	}
	else { // current is tail
		tail = node;
	}
	current->next = node;
}

template <typename T>
void LinkedListD<T>::empty()
{
	Node* node = head;
	Node* next;
	while (node) {
		next = node->next;
		delete node;
		node = next;
	}
	head = nullptr;
	tail = nullptr;
}

template <typename T>
void LinkedListD<T>::print() const
{
	std::cout << "Elementos en la lista enlazada: [";
	for (Node* current = head; current; current = current->next) {
		std::cout << current->value;
		if (current->next) {
			std::cout << ' ';
		}
	}
	std::cout << ']' << std::endl;
}
