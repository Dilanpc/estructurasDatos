#include <iostream>
#include <vector>


class Tree;

class Node
{
public:
	std::vector<unsigned int> children; // Index of children nodes

	unsigned int height = 0;
	unsigned int diameter = 0; // longest path between two nodes that GOES THROUGH this node

	// Calculate height and diameter of the node and all its children, use when the tree will not be modified
	void calculate(Tree& tree);
	
};


class Tree
{
public:
	Tree(unsigned int n) : nodes(n) {}
	std::vector<Node> nodes;

	unsigned int diametre = 0; // Longest path between two nodes, it is calculated in calcHeights and calcule of each node

	void calcHeights()
	{
		for (Node& node : nodes)
		{
			node.calculate(*this);
		}
	}
};




unsigned int maxDiameter(unsigned int n)
{
	Tree tree(n);

	// Read tree
	for (unsigned int i = 0; i < n - 1; i++)
	{
		unsigned int a, b;
		std::cin >> a >> b;
		// Adjust as index
		--a;
		--b;

		tree.nodes[a].children.push_back(b);
	}

	tree.calcHeights();

	return tree.diametre;
}


void Node::calculate(Tree& tree)
{
	if (height != 0) // Already calculated
		return;

	std::vector<Node>& nodes = tree.nodes;
	height = 1;
	for (unsigned int childIndex : children)
	{
		nodes[childIndex].calculate(tree);
		height = std::max(height, nodes[childIndex].height + 1);
	}

	// Calculate diameter
	if (children.size() == 1) // if there is only one child, the diameter is the height of the child
	{
		diameter = nodes[children[0]].height;
	}
	for (unsigned int i = 0; i < children.size(); i++) // Find the highest 
	{
		for (unsigned int j = i + 1; j < children.size(); j++) // Find the second highest
		{
			diameter = std::max(diameter, nodes[children[i]].height + nodes[children[j]].height);
		}
	}

	tree.diametre = std::max(tree.diametre, diameter);

}






int main(int argc, const char* argv[])
{
	std::ios_base::sync_with_stdio(false);

	unsigned int n;
	std::cin >> n;

	std::cout << maxDiameter(n) << '\n';

	
}
