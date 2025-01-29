#pragma once

template <typename T>
class AVLTree
{
	class Node
	{
	public:
		Node(T data) { this->data = data; }
		~Node();
		Node* left{};
		Node* right{};
		T data;
		unsigned int height = 1;
	};

	unsigned int getHeight(Node* node) const // Adds protection to the nullptr
	{
		if (node == nullptr)
			return 0;
		return node->height;
	}
	void adjustHeight(Node* node)
	{
		unsigned int left = getHeight(node->left);
		unsigned int right = getHeight(node->right);
		node->height = 1 + ((left < right) ? right : left);
	}

public:

	AVLTree();
	~AVLTree();

	void insert(const T& data);
	void erase(const T& data);

	Node* rebalance(Node* root);
	Node* rebalance(Node* root, std::stack<Node*>& path);
	Node* rotleft(Node* root);
	Node* rotright(Node* root);

	void print() const { print(root); }


private:
	void simpleErase(Node* parent, Node* node);

	void print(Node* root, unsigned int space=0) const;

	Node* root{};


};




template <typename T>
AVLTree<T>::Node::~Node()
{
	delete left;
	delete right;
}


template <typename T>
AVLTree<T>::AVLTree()
{
}

template <typename T>
AVLTree<T>::~AVLTree()
{
	delete root;
}


template <typename T>
void AVLTree<T>::insert(const T& data)
{
	if (!root) {
		root = new Node(data);
		return;
	}
	Node* current = root;
	std::stack<Node*> path; // Save the path to the new node in order to check if the tree is balanced
	path.push(current);
	// Find the right place to insert the new node
	while (true) // Until find a break
	{
		if (data < current->data) // Go left
		{
			if (current->left == nullptr) {
				current->left = new Node(data);
				break;
			}
			current = current->left; // Advance
		}
		else // Go right
		{
			if (current->right == nullptr) {
				current->right = new Node(data);
				break;
			}
			current = current->right; // Advance
		}
		path.push(current);
	}

	// Balance from the new node to the root
	root = rebalance(root, path);
}




// Verify if the given node is balanced by mesuaring the height of the subtrees
// If the difference is greater than 1, rotate the node and return the new root
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::rebalance(AVLTree<T>::Node* root)
{
	// Find best direction
	unsigned int right = getHeight(root->right);
	unsigned int left = getHeight(root->left);
	int diff = right - left;
	if (std::abs(diff) <= 1) return root; // Not neccesary to rotate

	Node* newRoot;
	if (diff < 0) // left side is higher. Rotate right
	{
		unsigned int subRight = getHeight(root->left->right);
		unsigned int subLeft = getHeight(root->left->left);

		if (subRight > subLeft) { // Internal rotation
			root->left = rotleft(root->left);
		}

		newRoot = rotright(root);
	}
	else // Rotate left
	{
		unsigned int subRight = getHeight(root->right->right);
		unsigned int subLeft = getHeight(root->right->left);

		if (subLeft > subRight) { // Internal rotation
			root->right = rotright(root->right);
		}

		newRoot = rotleft(root);

	}
	return newRoot;
}

template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::rebalance(AVLTree<T>::Node* root, std::stack<Node*>& path)
{
	// Check if the tree is balanced from current node to root
	Node* newRoot;
	while (true) {
		newRoot = rebalance(path.top());
		adjustHeight(newRoot);
		path.pop();
		if (!path.empty()) { // Adjust the parent to the new root
			Node* parent = path.top();
			if (newRoot->data < parent->data) { // check if the new root is the left or right child of the parent
				parent->left = newRoot;
			}
			else {
				parent->right = newRoot;
			}
		}
		else {
			return newRoot;
		}
	}
}

template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::rotleft(Node* root)
{
	Node* newRoot = root->right;

	root->right = newRoot->left; // Set subtree between root and the new root
	adjustHeight(root);
	newRoot->left = root; // Ascend the new Root
	adjustHeight(newRoot);


	return newRoot;
}

template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::rotright(Node* root)
{
	Node* newRoot = root->left;

	root->left = newRoot->right; // Set subtree between root and the new root
	adjustHeight(root);
	newRoot->right = root; // Ascend the new Root
	adjustHeight(newRoot);

	return newRoot;
}


template <typename T>
void AVLTree<T>::print(Node* root, unsigned int space) const
{
	if (root == nullptr) return;
	print(root->right, space + 5); // Go to the right most of the subtree, increse the space because is a deeper level
	for (unsigned int i = 0; i < space; i++)
		std::cout << ' ';
	std::cout << root->data << '-' << root->height << '\n';
	print(root->left, space + 5); // When the right is already printed, print the left
}