#include <iostream>


#include "StaticArray.hpp"
#include "SortedList.hpp"

static std::string classicalJump(const StaticArray<int>& arr)
{
	size_t n = arr.size();
	SortedList<int> diff(n - 1);

	for (int i = 0; i < n - 1; ++i) {
		diff.insert(
			(arr[i] - arr[i + 1]) < 0 ? (arr[i + 1] - arr[i]) : (arr[i] - arr[i + 1]) // Absolute value
		);
	}

	for (int i = 0; i < n - 2; ++i) { // Verify if all the numbers are
		if (diff[i+1] - diff[i] != 1) {
			return "Not jolly";
		}
	}
	return "Jolly";
}

StaticArray<int> read()
{
    size_t n;
	std::cin >> n;
	StaticArray<int> arr(n);


    for (int i = 0; i < n; ++i) {
        int value;
		std::cin >> value;
		arr.pushBack(value);
    }

    return arr;
}


int main(int argc, const char* argv[])
{
	while (std::cin) {
		try {
			StaticArray<int> arr = read();
			std::cout << classicalJump(arr) << std::endl;
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
			return 1;
		}
	}
}
