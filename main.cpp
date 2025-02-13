#include <iostream>
#include "Heap.hpp"




int sweet()
{
	int size;
	std::cin >> size;

	MinHeap<int> heap(size);

	int k;
	std::cin >> k;

	for (int i = 0; i < size; ++i)
	{
		int data;
		std::cin >> data;
		heap.insert(data);
	}


	int iter = 0;

	while (true)
	{
		if (heap.top() >= k) {
			return iter;
		}
		int a = heap.top();
		heap.pop();

		if (heap.isEmpty()) {
			return -1;
		}
		int b = heap.top();
		heap.pop();

		int result = a + 2 * b;
		heap.insert(result);

		++iter;
	}
}


int main(int argc, const char* argv[])
{
	std::ios_base::sync_with_stdio(false);

	std::cout << sweet() << std::endl;
}
