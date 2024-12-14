#include <iostream>
#include <string>

#include "StaticArray.hpp"
#include "LinkedListT.hpp"

// Create subgroups for each string, then merge them
static void stringMadness(size_t n)
{
	std::cin.ignore();

	StaticArray<LinkedListT<std::string*>*> groups(n); // using pointers to avoid copying lists

	// Read strings
	for (size_t i = 0; i < n; ++i)
	{
		// Get the string
		std::string* str = new std::string;
		std::getline(std::cin, *str);

		// Creat a grup
		groups.pushBack(new LinkedListT<std::string*>);
		groups[i]->pushBack(str);
	}


	// Read commands
	size_t a = 0;
	size_t b = 0;
	for (size_t i = 0; i < n - 1; ++i)
	{
		std::cin >> a >> b;

		--a; --b; // Adjust to index

		// Push all the pointers of group of 'b' to the group of 'a'
		groups[a]->pushBack(*groups[b]);
	}

	// Print result
	for (const auto& it : *groups[a])
	{
		std::cout << *it;
	}
	std::cout << std::endl;


	// Free memory
	for (size_t i = 0; i < n; ++i)
	{
		for (auto it : *groups[i])
		{
			delete it; // delete the string
		}
		delete groups[i]; // delete the list
	}
}




int main(int argc, const char* argv[])
{
	std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); // Fast IO

	size_t n;

	while (std::cin >> n)
	{
		stringMadness(n);
	}
}
