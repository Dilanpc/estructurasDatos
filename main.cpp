#include <iostream>

#include "Stack.hpp"

static void bugPlanning(Stack<int>& stack)
{
	size_t n = stack.capacity();
	int value;

	std::cin >> value;
	stack.push(value); // Fisrt value always goes to the stack

	for (size_t i = 0; i < n - 1; ++i)
	{
		std::cin >> value;

		if (value > stack.top()) // Add the value to the stack only if it is greater than the last
			stack.push(value);
	}

	// Print result
	std::cout << stack.size() << std::endl;
	stack.print();
}



int main(int argc, const char* argv[])
{
	try {
		size_t n;
		while (std::cin >> n)
		{
			Stack<int> stack(n);
			bugPlanning(stack);
		}
	}
	catch (...) {
		return 0;
	}
	
}
