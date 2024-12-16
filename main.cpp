#include <iostream>

#include "StaticArray.hpp"


static size_t histograma(size_t n)
{
	// Read data
	StaticArray<size_t> data(n);
	for (size_t i = 0; i < n; ++i)
	{
		size_t x;
		std::cin >> x;
		data.pushBack(x);
	}

	size_t minHeigth = 0;

	size_t maxArea = 0;

	for (size_t first = 0; first < n; ++first)
	{
		if (data[first] <= minHeigth) // if the height is equal (or less) to the previus loop, it was already calculated, then skip 
			continue;
		minHeigth = data[first];

		for (size_t last = first; last < n; ++last)
		{
			// Calculate min height
			if (data[last] < minHeigth)
				minHeigth = data[last];
			 
			// Calculate area
			if (minHeigth * (last - first + 1) > maxArea)
				maxArea = minHeigth * (last - first + 1);

		}
	}
	return maxArea;
}



int main(int argc, const char* argv[])
{
	size_t n;
	while (std::cin >> n && n != 0)
	{
		std::cout << histograma(n) << std::endl;
	}
}
