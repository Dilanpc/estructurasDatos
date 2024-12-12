#pragma once

#include <iostream>
#include "IList.hpp"


template <typename T>
class LinkedListS : public IList<T>
{

protected:
	struct Node
	{
		Node() = default;
		Node(T value) : value(value) {}
		T value;
		Node* next{};
	};

	class Iterator
	{
	friend class LinkedListS;
	protected:
		Node* current;
	public:
		Iterator(Node* node) : current(node) {}

		T& operator*() { return current->value; }

		Iterator& operator++() { current = current->next; return *this; }

		bool operator==(const Iterator& other) const {
			return current == other.current;
		}
		bool operator==(const Node* other) {
			return current == other;
		}

		bool operator!=(const Iterator& other) const {
			return current != other.current;
		}
		bool operator !=(const Node* other) {
			return current != other;
		}

		void advance(size_t n) {
			while (n-- && current) ++(*this);
		}

		
	};

	Node* head{};

public:
	virtual ~LinkedListS();

	void pushFront(const T& value) override;
	void pushBack(const T& value) override;

	T popFront() override;
	T popBack() override;

	T* find(const T& value) const override;
	void erase(T* element) override;

	virtual void addBefore(Iterator it, const T& value);
	virtual void addAfter(Iterator it, const T& value);

	void empty() override;

	void print() const override;

	Iterator begin() const { return Iterator(head); }
	Iterator end() const { return nullptr; } // last element->next is nullptr
};


template <typename T>
LinkedListS<T>::~LinkedListS()
{
	empty();
}

template <typename T>
void LinkedListS<T>::pushFront(const T& value)
{
	Node* node = new Node(value);

	node->next = head;
	head = node;
}

template <typename T>
void LinkedListS<T>::pushBack(const T& value)
{
	Node* node = new Node(value);
	if (!head) {
		head = node;
	}
	else {
		Node* current = head;
		while (current->next) {
			current = current->next;
		}
		// when next is nullptr
		current->next = node;
	}
}

template <typename T>
T LinkedListS<T>::popFront()
{
	if (!head) {
		throw std::runtime_error("Error: Lista vacia. No se puede eliminar el elemento.");
	}
	Node* toDelete = head;
	T value = toDelete->value;
	head = head->next;
	delete toDelete;
	return value;
}

template <typename T>
T LinkedListS<T>::popBack()
{
	if (!head) {
		throw std::runtime_error("Error: Lista vacia. No se puede eliminar el elemento.");
	}
	Node* toDelete = head;
	Node* previus{};
	while (toDelete->next) { // get to the last element
		previus = toDelete;
		toDelete = toDelete->next;
	}
	T value = toDelete->value;
	delete toDelete;
	if (previus) previus->next = nullptr;
	else head = nullptr; // if previus does not exist, there was only one element
	
	return value;
}

template <typename T>
T* LinkedListS<T>::find(const T& value) const
{
	for (Node* current = head; current; current = current->next) {
		if (current->value == value) {
			return &current->value;
		}
	}
	return nullptr;
}

template <typename T>
void LinkedListS<T>::erase(T* element)
{
	if (!head) {
		throw std::runtime_error("Error: Lista vacia. No se puede eliminar el elemento.");
	}
	Node* toDelete = head;
	Node* previus{};
	while (toDelete) {
		if (&toDelete->value == element) {
			if (previus) { // if it is NOT the first element
				previus->next = toDelete->next;
			}
			else { // if it is the first element
				head = toDelete->next;
			}
			delete toDelete;
			return;
		}
		previus = toDelete;
		toDelete = toDelete->next;
	}
	throw std::runtime_error("Error: Elemento no encontrado.");
}

template <typename T>
void LinkedListS<T>::addBefore(Iterator it, const T& value)
{
	if (it == begin()) {
		pushFront(value);
		return;
	}
	if (it == end()) {
		pushBack(value);
		return;
	}

	Node* node = new Node(value);
	Node* current = head;
	while (current->next && current->next != it.current) { // Get to the element before the iterator
		current = current->next;
	}
	node->next = current->next;
	current->next = node;

}

template <typename T>
void LinkedListS<T>::addAfter(Iterator it, const T& value)
{
	if (it == end()) {
		throw std::runtime_error("Error: No se puede agregar despues del final.");
	}
	Node* node = new Node(value);
	node->next = it.current->next;
	it.current->next = node;
}

template <typename T>
void LinkedListS<T>::empty()
{
	Node* node = head;
	Node* next;
	while (node) {
		next = node->next;
		delete node;
		node = next;
	}
	head = nullptr;
}

template <typename T>
void LinkedListS<T>::print() const
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