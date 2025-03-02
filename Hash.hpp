#pragma once


#include <vector>

// Save key and value
// Has dinamic hashing
// Does not verify if the key is already in the hash
template <typename T>
class HashInt
{
	struct Node
	{
		Node(const unsigned int key, const T& value)
			: key(key), value(value)
		{}
		unsigned int key;
		T value;
	};

public:
	HashInt(float maxLoad);
	~HashInt();

	unsigned int size = 0;
	float maxLoad;

	std::vector<std::vector<Node>> data;

	void insert(const unsigned int key, const T& value);
	void rehash(); // Doubles the size of the hash table

	void set(const unsigned int key, const T& value);
	T& get(const unsigned int key);
	inline T& operator[](const unsigned int key);

	float getLoadFactor() const {
		return float(size) / data.size();
	}

	void printSchema() const;

private:
	inline unsigned int h(const unsigned int key) const; // Returns the index
};



template <typename T>
HashInt<T>::HashInt(float maxLoad)
	: data(10), // m = 10
	maxLoad(maxLoad)
{
	
}

template <typename T>
HashInt<T>::~HashInt()
{


}

template <typename T>
void HashInt<T>::insert(const unsigned int key, const T& value)
{
	unsigned int index = h(key);
	data[index].emplace_back(key, value);
	++size;

	//   n     maxAlpha      m
	if (size > maxLoad * data.size())
	{
		std::cout << "Rehashing\n";
		rehash();
	}
}

template <typename T>
void HashInt<T>::rehash()
{
	std::vector<std::vector<Node>> oldData = data;
	data.clear();
	data.resize(oldData.size() * 2);

	for (int i = 0; i < oldData.size(); ++i)
	{
		for (int j = 0; j < oldData[i].size(); ++j)
		{
			unsigned int index = h(oldData[i][j].key);
			data[index].emplace_back(oldData[i][j].key, oldData[i][j].value);
		}
	}
}


template <typename T>
void HashInt<T>::set(const unsigned int key, const T& value)
{
	unsigned int index = h(key);
	for (int i = 0; i < data[index].size(); ++i) // Search in the collision list
	{
		if (data[index][i].key == key)
		{
			data[index][i].value = value;
			return;
		}
	}
}

template <typename T>
T& HashInt<T>::get(const unsigned int key)
{
	unsigned int index = h(key);
	for (int i = 0; i < data[index].size(); ++i) // Search in the collision list
	{
		if (data[index][i].key == key)
		{
			return data[index][i].value;
		}
	}
}

template <typename T>
T& HashInt<T>::operator[](const unsigned int key)
{
	return get(key);
}

template <typename T>
void HashInt<T>::printSchema() const
{
	for (int i = 0; i < data.size(); ++i)
	{
		std::cout << i << ": ";
		for (int j = 0; j < data[i].size(); ++j)
		{
			std::cout << data[i][j].key << " ";
		}
		std::cout << '\n';
	}
}

template <typename T>
unsigned int HashInt<T>::h(const unsigned int key) const
{
	static int a = 429; // Random number
	static int b = 351; // Random number
	int m = data.size();

	return (a * key + b) % m;
}