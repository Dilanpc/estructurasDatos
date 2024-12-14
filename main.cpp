#include <iostream>
#include <string>

#include "DinamicArray.hpp"

// Create subgroups for each string, then merge them
static void stringMadness(size_t n)
{
	std::cin.ignore();
	StaticArray<std::string*> strings(n); // using pointers to avoid copying strings

	DinamicArray<DinamicArray<std::string*>*> subGrp; // Save the combinations, using pointers for compatibility inside a DinamicArray

	// Read strings
	for (size_t i = 0; i < n; ++i)
	{
		// Get the string
		std::string* str = new std::string;
		std::getline(std::cin, *str);
		// Save the string and create a group with it
		strings.pushBack(str);
		subGrp.pushBack(new DinamicArray<std::string*>());
		subGrp[i]->pushBack(str);

	}


	// Read commands
	size_t a = 0;
	size_t b = 0;
	for (size_t i = 0; i < n - 1; ++i)
	{
		std::cin >> a >> b;

		--a; --b; // Adjust to index

		// Push all the pointers of group of 'b' to the group of 'a'
		for (size_t j = 0; j < subGrp[b]->size(); ++j)
		{
			subGrp[a]->pushBack((*subGrp[b])[j]);
		}
	}

	// Print result
	for (size_t i = 0; i < subGrp[a]->size(); ++i)
	{
		std::cout << *(*subGrp[a])[i]; // Print 'a' as it was the last modified
	}
	std::cout << std::endl;


	// Free memory
	for (size_t i = 0; i < n; ++i)
	{
		delete strings[i]; // std::string *
		delete subGrp[i]; // DinamicArray<std::string*> *
	}
}




int main(int argc, const char* argv[])
{
	size_t n;
	try {
		while (std::cin >> n)
		{
			stringMadness(n);
		}
	}
	catch (...) {
		return 0;
	}
	
}
