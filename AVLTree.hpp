#pragma once

#include <stack>

// Do not add duplicate values
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

	class Iterator // Iter using a stack, left, root, right. Inorder traversal
	{
		std::stack<Node*> stack;
		unsigned int level = 0;
	public:
		Iterator(Node* node) {
			while (node) { // Go to the leftmost node, and save the path in the stack
				stack.push(node);
				node = node->left;
				++level;
			}
		}
		~Iterator() {}
		Iterator& operator++() {
			if (stack.empty()) return *this;
			Node* current = stack.top();
			stack.pop();
			--level;
			if (current->right) { // if has right, go to the leftmost node of the right subtree
				Node* node = current->right;
				while (node) {
					stack.push(node);
					node = node->left;
					++level;
				}
			}
			return *this;
		};
		T& operator*() { return stack.top()->data; }
		bool operator==(const Iterator& other) {
			if (stack.empty() && other.stack.empty()) return true;
			if (stack.empty() || other.stack.empty()) return false;
			return stack.top() == other.stack.top();
		}
		bool operator!=(const Iterator& other) {
			if (stack.empty() && other.stack.empty()) return false;
			if (stack.empty() || other.stack.empty()) return true;
			return stack.top() != other.stack.top();
		}

		unsigned int getLevel() const { return level; }
		Node* getNode() { return stack.top(); }
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

	size_t getSize() const { return getSize(root); }
	size_t getSize(Node* root) const;

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


template <typename T>
void AVLTree<T>::erase(const T& data)
{
	if (!root) return;
	Node* current = root;
	Node* parent{};

	// Find the node to delete
	while (true)
	{
		if (current->data < data) { // Go right
			if (current->right == nullptr) return; // Not found
			if (current->right->data == data) break; // Found
			parent = current;
			current = current->right;
		}
		else { // Go left
			if (current->left == nullptr) return; // Not found
			if (current->left->data == data) break; // Found
			parent = current;
			current = current->left;
		}
	}

	// Check if the node has one or no children
	if (!(current->right && current->left)) {
		simpleErase(parent, current);
	}
	else {
		// Find the previous node
		Node* prev = current->left;
		parent = current;

		while (prev->right) {
			parent = prev;
			prev = prev->right;
		}

		current->data = prev->data; // Replace the data
		simpleErase(parent, prev);
	}
}

// To delete a node that have one or no children
template <typename T>
void AVLTree<T>::simpleErase(Node* parent, Node* node)
{
	if (parent == nullptr) // Is the root
	{
		if (root->left == nullptr) // If the node has no left child
		{
			root = node->right;
		}
		else // If the node has no right child
		{
			root = node->left;
		}
	}
	else if (parent->right == node) // Check if the node is the left or right child of the parent
	{
		if (node->left == nullptr) // If the node has no left child
		{
			parent->right = node->right;
		}
		else // If the node has no right child
		{
			parent->right = node->left;
		}
	}
	else
	{
		if (node->left == nullptr) // If the node has no left child
		{
			parent->left = node->right;
		}
		else // If the node has no right child
		{
			parent->left = node->left;
		}
	}

	operator delete(node); // Delete withou calling the destructor to avoid deleting the children
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
size_t AVLTree<T>::getSize(Node* root) const
{
	if (root == nullptr) return 0;
	// Verify if is a leaf
	if (root->left == nullptr && root->right == nullptr) return 1;
	return 1 + getSize(root->left) + getSize(root->right);
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