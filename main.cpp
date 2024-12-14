#include <iostream>

#include "Stack.hpp"


void brackets(size_t n)
{
	std::cin.ignore();

	Stack<char> stack(n);
	char c;
	size_t index = 0;

	for (size_t i = 0; i < n; ++i) { // iter each character
		c = std::cin.get();
		if (c != ' ' && c != '\n') // ignore spaces and new lines
		{
			if (c == '(' || c == '[' || c == '{')
			{
				stack.push(c);
			}
			else
			{
				if (stack.isEmpty()) // if closing bracket is found and stack is empty
				{
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the rest of the line
					std::cout << c << " " << index << std::endl;
					return;
				}
				if ((stack.top() == '(' && c == ')') ||
					(stack.top() == '[' && c == ']') ||
					(stack.top() == '{' && c == '}'))
				{
					stack.pop();
				}
				else // if bracket is closing and doesn't match the top of the stack
				{
					std::cout << c << " " << index << std::endl;
					return;
				}
			}
		}
		++index;
	}
	std::cout << "ok so far" << std::endl;
}


int main(int argc, const char* argv[])
{
	try {
		size_t n;
		while (std::cin >> n)
		{
			brackets(n);
		}
	}
	catch (...) {
		return 0;
	}
}
