#pragma once

#include <iostream>
#include "IList.hpp"

template <typename T>
class StaticArray : public IList<T>
{
protected:
	T* m_arr;
	T* m_last;
	T* m_end;

	class Iterator
	{
		T* current;

	public:
		Iterator(T* current) : current(current) {}

		T& operator*() { return *current; }

		T& operator->() { return *current; }

		Iterator& operator++() { ++current; return *this; }
		Iterator& operator--() { --current; return *this; }

		Iterator operator+(size_t n) { return Iterator(current + n); }
		Iterator operator-(size_t n) { return Iterator(current - n); }

		Iterator& operator+=(size_t n) { current += n; return *this; }
		Iterator& operator-=(size_t n) { current -= n; return *this; }

		ptrdiff_t operator-(const Iterator& other) { return current - other.current; }

		bool operator==(const Iterator& other) const {
			return current == other.current;
		}

		bool operator!=(const Iterator& other) const {
			return current != other.current;
		}

		bool operator<(const Iterator& other) const {
			return current < other.current;
		}

		void advance(size_t n) {
			while (n-- && current) ++(*this);
		}
	};

public:
	StaticArray(size_t size);
	virtual ~StaticArray();

	void pushFront(const T& value) override;
	void pushBack(const T& value) override;

	T popFront() override;
	T popBack() override;
	
	T* find(const T& value) const override;
	void erase(T* value) override;

	void addBefore(T* reference, const T& value);
	void addBefore(Iterator it, const T& value);
	void addAfter(T* reference, const T& value);
	void addAfter(Iterator it, const T& value);

	void addAt(T value, size_t index);
	void popAt(size_t index);

	Iterator begin() const { return Iterator(m_arr); }
	Iterator back() const { return Iterator(m_last); }
	Iterator end() const { return Iterator(m_end); }

	void empty() override;

	size_t size() const;
	size_t capacity() const;
	virtual T& operator[](size_t index) const;
	void print() const override;

};


template <typename T>
StaticArray<T>::StaticArray(size_t size)
{
	m_arr = new T[size];
	m_last = m_arr;
	m_end = m_arr + size;
}

template <typename T>
StaticArray<T>::~StaticArray()
{
	delete[] m_arr;
}



template <typename T>
void StaticArray<T>::pushFront(const T& value)
{
	if (m_last == m_end) {
		throw std::runtime_error("Error: Lista llena. No se puede agregar el elemento.");
	}

	for (T* current = m_last; current > m_arr; --current) {
		*current = *(current - 1);
	}
	*m_arr = value;
	++m_last;

}

template <typename T>
void StaticArray<T>::pushBack(const T& value)
{
	if (m_last < m_end) {
		*m_last = value;
		++m_last;
	}
	else {
		throw std::runtime_error("Error: Lista llena. No se puede agregar el elemento.");
	}
}

template <typename T>
T StaticArray<T>::popFront()
{
	if (m_last == m_arr) {
		throw std::runtime_error("Error: Lista vacia. No se puede eliminar el elemento.");
	}
	--m_last;
	for (T* current = m_arr; current < m_last; ++current) {
		*current = *(current + 1);
	}
	return *m_last;
}


template <typename T>
T StaticArray<T>::popBack()
{
	if (m_last != m_arr) {
		m_last = m_last - 1;
		return *m_last;
	}
	else {
		throw std::runtime_error("Error: Lista vacia. No se puede eliminar el elemento.");
	}
}

template <typename T>
T* StaticArray<T>::find(const T& value) const
{
	for (T* current = m_arr; current < m_last; ++current) {
		if (*current == value) {
			return current;
		}
	}
	return nullptr;
}

template <typename T>
void StaticArray<T>::erase(T* value)
{
	if (!find(*value)) {
		throw std::runtime_error("Error: Elemento no encontrado. No se puede eliminar.");
	}
	for (T* current = value; current < m_last; ++current) {
		*current = *(current + 1);
	}
	--m_last;
}

template <typename T>
void StaticArray<T>::addBefore(T* reference, const T& value)
{
	if (!find(reference)) {
		throw std::runtime_error("Error: Elemento no encontrado. No se puede agregar el elemento.");
	}
	if (m_last == end) {
		throw std::runtime_error("Error: Lista llena. No se puede agregar el elemento.");
	}
	for (T* current = m_last; current >= reference; --current) {
		*current = *(current - 1);
	}
	*reference = value;
	++m_last;
}

template <typename T>
void StaticArray<T>::addBefore(Iterator it, const T& value) {
	if (m_last == m_end) {
		throw std::runtime_error("Error: Lista llena. No se puede agregar el elemento.");
	}
	T* reference = &(*it); // Convert iterator to pointer
	for (T* current = m_last; current > reference; --current) {
		*current = *(current - 1);
	}
	*reference = value;
	++m_last;
}

template <typename T>
void StaticArray<T>::addAfter(T* reference, const T& value)
{
	if (!find(reference)) {
		throw std::runtime_error("Error: Elemento no encontrado. No se puede agregar el elemento.");
	}
	if (m_last == m_end) {
		throw std::runtime_error("Error: Lista llena. No se puede agregar el elemento.");
	}
	for (T* current = m_last; current > reference; --current) {
		*current = *(current - 1);
	}
	*(reference + 1) = value;
	++m_last;
}

template <typename T>
void StaticArray<T>::addAfter(Iterator it, const T& value) {
	if (m_last == m_end) {
		throw std::runtime_error("Error: Lista llena. No se puede agregar el elemento.");
	}
	T* reference = &(*it); // Convert iterator to pointer
	for (T* current = m_last; current > reference; --current) {
		*current = *(current - 1);
	}
	*(reference + 1) = value;
	++m_last;
}

template<typename T>
void StaticArray<T>::addAt(T value, size_t index)
{
	if (m_last - m_arr < index) {
		throw std::runtime_error("Error: Indice fuera de rango. No se puede agregar el elemento.");
	}
	if (m_last == end) {
		throw std::runtime_error("Error: Lista llena. No se puede agregar el elemento.");
	}
	// Encontrar el indice
	T* objetive = m_arr + index;
	for (T* current = m_last; current > objetive; --current) {
		*current = *(current - 1);
	}
	*objetive = value;
	++m_last;

}



template <typename T>
void StaticArray<T>::popAt(size_t index)
{
	if (m_last == m_arr) {
		throw std::runtime_error("Error: Lista vacia. No se puede eliminar el elemento.");
	}

	--m_last;
	for (T* current = m_arr + index; current < m_last; ++current) {
		*current = *(current + 1);
	}

}

template <typename T>
void StaticArray<T>::empty()
{
	m_last = m_arr;
}

template <typename T>
size_t StaticArray<T>::size() const
{
	return m_last - m_arr;
}

template <typename T>
size_t StaticArray<T>::capacity() const
{
	return m_end - m_arr;
}

template <typename T>
T& StaticArray<T>::operator[](size_t index) const
{
	if (index >= size()) {
		throw std::runtime_error("Error: Indice fuera de rango.");
	}
	return m_arr[index];
}

template <typename T>
void StaticArray<T>::print() const
{
	std::cout << "Elementos en el arreglo: [";
	for (T* it = m_arr; it < m_last; ++it) {
		std::cout << *it;
		if (it != m_last - 1) {
			std::cout << " ";
		}
	}
	std::cout << "]" << std::endl;
}


