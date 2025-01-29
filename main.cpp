#include <iostream>

#include "Tree.hpp"
#include "AVLTree.hpp"

#include <random>
int randint(int min, int max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

#define T int



int main(int argc, const char* argv[])
{
	std::ios_base::sync_with_stdio(false);

	
	//Tree<T> tree;
	AVLTree<T> balancedTree;
	for (int i = 0; i < 10; ++i)
	{
		balancedTree.insert(i);
		balancedTree.print();
		std::cout << "\n---\n";
	}
	
	balancedTree.print();
	
	std::cout << '\n';

	//balancedTree.erase(105);
	//balancedTree.erase(75);

	std::cout << "---------------\n";
	
}
