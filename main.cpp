#include <iostream>
#include <vector>


class Node
{
public:
	std::vector<Node*> children; // Index of children nodes, it also can point to the parent
	unsigned int height = 0;

	static unsigned int diameter; // Longest path between two nodes, it is calculated in calcHeights

	// Calculate height and diameter of the node and all its children, use when the tree will not be modified
	// it is calculated considering the current node as the root of a subtree
	void calculate(Node* parent);
	
};

unsigned int Node::diameter = 0;










void Node::calculate(Node* parent)
{
	if (height != 0) // Already calculated
		return;

	// Two highest heights of children
	unsigned int maxHeightOne = 0;
	unsigned int maxHeightTwo = 0;

	for (Node* child : children)
	{
		if (child == parent) // Parent, skip to avoid returning to the parent and infinite loop
			continue;

		child->calculate(this);
		if (child->height > maxHeightOne)
		{
			maxHeightTwo = maxHeightOne;
			maxHeightOne = child->height;
		}
		else if (child->height > maxHeightTwo)
		{
			maxHeightTwo = child->height;
		}
	}
	height = maxHeightOne + 1;

	// Largets path that goes through this node:
	// sum of the two highest heights of children

	diameter = std::max(diameter, maxHeightOne + maxHeightTwo);

}


unsigned int maxDiameter(unsigned int n)
{
	if (n == 1 || n == 0)
		return 0;

	std::vector<Node> nodes(n);


	// Read tree
	for (unsigned int i = 0; i < n - 1; ++i)
	{
		unsigned int a, b;
		std::cin >> a >> b;
		// Adjust as index
		--a;
		--b;

		nodes[a].children.push_back(&nodes[b]);
		nodes[b].children.push_back(&nodes[a]);
	}

	nodes[0].calculate(&nodes[0]);
	
	return Node::diameter;

	throw std::runtime_error("No root found");
}




int main(int argc, const char* argv[])
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);


	unsigned int n;
	std::cin >> n;

	std::cout << maxDiameter(n) << '\n';

	
}
