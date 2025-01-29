#pragma once

#include <iostream>
#include <string>
#include <random>
#include "LinkedListD.hpp"

int randint(int min, int max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

//std::ios_base::sync_with_stdio(false); //Fast Output

void unixPath()
{
	char c;
	std::cin.get(c);
	LinkedListD<std::string*> stack;
	while (!std::cin.eof()) {
		if (c == '\n') {
			break;
		}

		while (std::cin.get(c) && c == '/'); // skip repeated '/'
		if (c == '\n') break;
		std::string* dir = new std::string("");
		*dir += c;

		while (std::cin.get(c) && c != '/' && c != '\n') {
			*dir += c;
		}
		if (*dir == ".") { // same directory
			delete dir;
			continue;
		}
		else if (*dir == "..") {
			delete dir;
			if (!stack.isEmpty())
				delete stack.popBack();
		}
		else {
			stack.pushBack(dir);
		}

	}

	// print
	if (stack.isEmpty()) {
		std::cout << '/';
	}
	for (auto str = stack.begin(); str != stack.end(); ++str) {
		std::cout << '/' << **str;
		delete* str; // delete string, the stak only will delete the pointers
	}
	std::cout << std::endl;


}
