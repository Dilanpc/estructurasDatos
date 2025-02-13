#include <iostream>



struct Orders
{
	unsigned int* preorder{};
	unsigned int* inoPos{}; // Acces by value-1 = preorder[i] - 1
	~Orders() {
		delete[] preorder;
		delete[] inoPos;
	}
};


Orders* readOrders(unsigned int size)
{
	Orders* orders = new Orders;
	orders->preorder = new unsigned int[size];
	orders->inoPos = new unsigned int[size];

	for (unsigned int i = 0; i < size; ++i) // Reading preorder
	{
		std::cin >> orders->preorder[i]; // Save preorder in the giving order
	}
	
	for (unsigned int i = 0; i < size; ++i) // Reading inorder
	{
		unsigned int data;
		std::cin >> data;
		orders->inoPos[data - 1] = i;
	}
	return orders;
}


void postorder(unsigned int left, unsigned int right, const Orders& orders, unsigned int& i)
{
	// left and right, limits in inorder list, are inlusive [left, right]

	// i =: current position in preorder

	if (left > right) // Base case, not existent subtree
		return;
	
	// Save the current root, it will be printed after its subtrees
	unsigned int current = orders.preorder[i];

	// Find the current root in inorder to divide it
	unsigned int inoIndex = orders.inoPos[current - 1]; // access by value - 1
	++i; // Search for the next in preorder, in the next calls

	// Base case
 	if (left != right) // is not a leaf
	{
		if (inoIndex != 0) // Necessary to avoid 0 - 1 = 4294967295
			postorder(left, inoIndex - 1, orders, i); // Left subtree
		postorder(inoIndex + 1, right, orders, i); // Right subtree
	}


	std::cout << current << ' ';
	
}




int main(int argc, const char* argv[])
{
	std::ios_base::sync_with_stdio(false);

	unsigned int size;
	std::cin >> size;

	Orders* orders = readOrders(size);

	unsigned int i = 0;
	postorder(0, size - 1, *orders, i);

	delete orders;
}
