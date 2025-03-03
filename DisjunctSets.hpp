#pragma once

#include <iostream>
#include <vector>

 // Using Ranks
class DisjunctSets
{
	struct Node
	{
		size_t parent;
		unsigned int rank = 0;
		Node(const int& index) : parent(index) {}
	};


	Node* m_arr;
	size_t m_size;

public:
	DisjunctSets(size_t size);
	~DisjunctSets();

	size_t find(size_t index);
	void join(const int dataOe, int dataTwo);

	void print() const;
};



DisjunctSets::DisjunctSets(size_t size)
{
	m_size = size;
	m_arr = static_cast<Node*>(operator new(sizeof(Node) * size)); // Reserve memory for the array of Nodes
	for (size_t i = 0; i < size; ++i)
	{
		new (m_arr + i) Node(i);
	}
}


DisjunctSets::~DisjunctSets()
{
	for (size_t i = 0; i < m_size; ++i)
	{
		m_arr[i].~Node();
	}
	operator delete[] (m_arr);
}


size_t DisjunctSets::find(size_t index)
{	
	while (m_arr[index].parent != index)
	{
		index = m_arr[index].parent;
	}
	return index;
}



void DisjunctSets::join(const int dataOne, const int dataTwo)
{
	// Get the number of the set of each element
	size_t iOne = find(dataOne);
	size_t iTwo = find(dataTwo);
	if (iOne == iTwo) // Are in the same set
		return;

	// join with the one with higher rank
	if (m_arr[iOne].rank < m_arr[iTwo].rank)
	{
		m_arr[iOne].parent = iTwo;
	}
	else if (m_arr[iOne].rank > m_arr[iTwo].rank)
	{
		m_arr[iTwo].parent = iOne;
	}
	else // if the ranks are equal, join to iTwo and increase its rank
	{
		m_arr[iOne].parent = iTwo;
		++m_arr[iTwo].rank;
	}

}


void DisjunctSets::print() const
{
	for (size_t i = 0; i < m_size; ++i)
	{
		std::cout << i << " ";
	}
	std::cout << '\n';

	for (size_t i = 0; i < m_size; ++i)
	{
		std::cout << m_arr[i].parent << " ";
	}
	std::cout << '\n';
}











/////////////////////////////

// Using Path Compression
class DisjunctSetsPC
{
	struct Node
	{
		size_t parent;
		Node(const int& index) : parent(index) {} // At the beginning, each element is root
	};

	Node* m_arr;
	size_t m_size;

public:
	DisjunctSetsPC(size_t size);
	~DisjunctSetsPC();
	size_t find(size_t index);
	void join(const int dataOe, int dataTwo);
	bool isSameSet(const int dataOne, const int dataTwo) { return find(dataOne) == find(dataTwo); }
	void print() const;

};



DisjunctSetsPC::DisjunctSetsPC(size_t size)
{
	m_size = size;
	m_arr = static_cast<Node*>(operator new(sizeof(Node) * size)); // Reserve memory for the array of Nodes
	for (size_t i = 0; i < size; ++i)
	{
		new (m_arr + i) Node(i);
	}
}


DisjunctSetsPC::~DisjunctSetsPC()
{
	for (size_t i = 0; i < m_size; ++i)
	{
		m_arr[i].~Node();
	}
	operator delete[](m_arr);
}


size_t DisjunctSetsPC::find(size_t index)
{
	if (m_arr[index].parent == index) // Is the root
		return index;
	// Path compression
	size_t root = find(m_arr[index].parent); // Recursion until find the root
	m_arr[index].parent = root; 
	return root;
}


void DisjunctSetsPC::join(const int dataOne, const int dataTwo)
{
	// Get the number of the set of each element
	size_t iOne = find(dataOne);
	size_t iTwo = find(dataTwo);
	if (iOne == iTwo) // Are in the same set
		return;
	m_arr[iOne].parent = m_arr[iTwo].parent;
}


void DisjunctSetsPC::print() const
{
	for (size_t i = 0; i < m_size; ++i)
	{
		std::cout << i << " ";
	}
	std::cout << '\n';
	for (size_t i = 0; i < m_size; ++i)
	{
		std::cout << m_arr[i].parent << " ";
	}
	std::cout << '\n';
}