#include <iostream>

#include "StaticArray.hpp"


static std::string classicalJump(const StaticArray<int>& arr)
{
	size_t n = arr.size();
	if (n < 2) {
		return "Jolly";
	}

	StaticArray<bool> diff(n - 1);
	for (int i = 0; i < n - 1; ++i) {
		diff.pushBack(false);
	}

	for (int i = 0; i < n - 1; ++i) {
		int value = std::abs(arr[i] - arr[i + 1]);
		//  lower limit      upper limit        already exists
		if (value < 1 || value >= n || diff[value - 1]) {
			return "Not jolly";
		}
		diff[value - 1] = true;
	}


	return "Jolly";
}

void read(StaticArray<int>& arr)
{
	size_t n = arr.capacity();

	for (int i = 0; i < n; ++i) {
		int value;
		std::cin >> value;
		arr.pushBack(value);
	}
}


int main(int argc, const char* argv[])
{
	try {
		size_t n;
		while (std::cin >> n) {
			StaticArray<int> arr(n);
			read(arr);
			std::cout << classicalJump(arr) << std::endl;
		}
	}
	catch (...) {
		return 0;
	}
}
