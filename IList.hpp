#pragma once


template<typename T>
class IList
{
public:
	virtual void pushFront(const T& value) = 0;
	virtual void pushBack(const T& value) = 0;

	virtual T popFront() = 0;
	virtual T popBack() = 0;

	virtual T* find(const T& value) const = 0;
	virtual void erase(T* element) = 0;

	virtual void empty() = 0;

	virtual void print() const = 0;


};