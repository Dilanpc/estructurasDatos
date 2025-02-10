#pragma once
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <string>


template <typename T>
class Tree
{
private:
	class Node
	{
	public:
		Node(T data);
		~Node();
		Node* left{};
		Node* right{};
		T data;
	};

public:
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

public:
	Tree();
	Tree(const T& data);
	Tree(const Node* root);
	~Tree();

	void insert(const T& data);
	void avlInsert(const T& data);

	void erase(const T& data);
	void simpleErase(Node* parent, Node* node);

	static Node* rebalance(Node* root);
	static Node* rebalance(Node* root, std::stack<Node*>& path);
	static Node* rotleft(Node* root);
	static Node* rotright(Node* root);

	Node* find(const T& data);
	std::vector<T> search(const T& min, const T& max) const;


	unsigned int getHeight() const;
	static unsigned int getHeight(const Node* node);

	unsigned int getSize() const;
	static unsigned int getSize(const Node* node);

	void print() const;
	void prettyPrint() const;
	void BFS() const;
	static void print(const Node* node, unsigned int space = 0);


	Iterator begin() const { return Iterator(root); }
	Iterator end() const { return Iterator(nullptr); }

private:

	Node* root{};

};

template <typename T>
Tree<T>::Node::Node(T data)
	: data(data)
{
}

template <typename T>
Tree<T>::Node::~Node() // Usign recursion
{
	delete left;
	delete right;
}

template<typename T>
Tree<T>::Tree()
{
}

template<typename T>
Tree<T>::Tree(const T& data)
{
	root = new Node(data);
}

template<typename T>
Tree<T>::Tree(const Tree<T>::Node* root)
	: root(root)
{
}

template<typename T>
Tree<T>::~Tree() // Using recursion
{
	delete root;
}


template <typename T>
void Tree<T>::insert(const T& data)
{
	if (!root) {
		root = new Node(data);
		return;
	}
	Node* current = root;

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
	}
}


template <typename T>
void Tree<T>::avlInsert(const T& data)
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

	
	root = rebalance(root, path);
}

template <typename T>
void Tree<T>::erase(const T& data)
{
	Node* node = root;
	Node* parent{};

	// Find the node to erase and its parent
	while (node) {
		if (node->data == data) break;
		parent = node;
		if (node->data < data) node = node->right;
		else node = node->left;
	}
	if (!node) return; // Not found



	if (!(node->right && node->left)) // if has one or none child
	{
		simpleErase(parent, node);
	}
	else { // Two children
		// Find a node with the previous value
		Node* current = node->left;
		Node* parent = node;
		while (current->right) {
			parent = current;
			current = current->right;
		}

		// Swap the values
		node->data = current->data;

		// Erase the node with the previous value
		simpleErase(parent, current);
	}
}

// Delete a node with one or none child
template <typename T>
void Tree<T>::simpleErase(Tree<T>::Node* parent, Tree<T>::Node* node)
{
	if (parent == nullptr) { // if is the root
		if (node->right) {
			root = node->right;
		}
		else {
			root = node->left;
		}
	}

	else if (parent->right == node) { // the right of the parent will remplace the node
		if (node->right) {
			parent->right = node->right;
		}
		else {
			parent->right = node->left;
		}
	}
	else { // the left of the parent will remplace the node
		if (node->right) {
			parent->left = node->right;
		}
		else {
			parent->left = node->left;
		}
	}
	operator delete(node); // Free memory without deleting the children
}

// Verify if the given node is balanced by mesuaring the height of the subtrees
// If the difference is greater than 1, rotate the node and return the new root
template <typename T>
typename Tree<T>::Node* Tree<T>::rebalance(typename Tree<T>::Node* root)
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

// Balance the tree from the given node following the given path
template <typename T>
typename Tree<T>::Node* Tree<T>::rebalance(typename Tree<T>::Node* root, std::stack<Node*>& path)
{
	if (path.empty()) return rebalance(root);
	// Check if the tree is balanced from current node to root
	Node* newRoot;
	while (true) {
		newRoot = rebalance(path.top());
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
typename Tree<T>::Node* Tree<T>::rotleft(Node* root)
{
	Node* newRoot = root->right;

	root->right = newRoot->left; // Set subtree between root and the new root
	newRoot->left = root; // Ascend the new Root

	return newRoot;
}

template <typename T>
typename Tree<T>::Node* Tree<T>::rotright(Node* root)
{
	Node* newRoot = root->left;

	root->left = newRoot->right; // Set subtree between root and the new root
	newRoot->right = root; // Ascend the new Root

	return newRoot;
}


template <typename T>
typename Tree<T>::Node* Tree<T>::find(const T& data)
{
	Node* current = root;
	if (!root) return nullptr;
	while (true)
	{
		if (current->data < data) // Go right
		{
			if (current->right) {
				current = current->right;
			}
			else {
				return current;
			}
		}
		else if (current->data > data)// Go left
		{
			if (current->left) {
				current = current->left;
			}
			else {
				return current;
			}
		}
		else // if is equal to data
			return current;
	}
	

}

template <typename T>
std::vector<T> Tree<T>::search(const T& min, const T& max) const
{
	std::vector<T> answer;

	Iterator it = root;
	while (*it < min && it != end()) // Find min
		++it;

	while (*it <= max && it != end()) { // Fill until max
		answer.push_back(*it);
		++it;
	}

	return answer;
}


template <typename T>
unsigned int Tree<T>::getHeight() const
{
	return getHeight(root);
}

template <typename T>
unsigned int Tree<T>::getHeight(const Tree<T>::Node* node)
{
	if (node == nullptr)
		return 0;
	if (node->left == nullptr && node->right == nullptr) // if it is a leaf
		return 1;

	unsigned int a = getHeight(node->left);
	unsigned int b = getHeight(node->right);
	return 1 + ((a < b) ? b : a); // get the max
}

template <typename T>
unsigned int Tree<T>::getSize() const
{
	return getSize(root);
}

template <typename T>
unsigned int Tree<T>::getSize(const Tree<T>::Node* node)
{
	if (node == nullptr)
		return 0;
	return 1 + getSize(node->left) + getSize(node->right);
}

template <typename T>
void Tree<T>::print() const
{
	print(root);
}


template <typename T>
void Tree<T>::print(const Tree<T>::Node* node, unsigned int space) // Preorder traversal
{
	for (unsigned int i = 0; i < space; ++i) std::cout << "| ";

	std::cout << node->data << '\n';

	if (node->right != nullptr)
		print(node->right, space + 1);
	if (node->left != nullptr)
		print(node->left, space + 1);
}

template <typename T>
void Tree<T>::prettyPrint() const
{
	Iterator it = begin();
	unsigned int height = getHeight();

	std::vector<std::string> lines(height);

	while (it != end()) {
		unsigned int level = it.getLevel();

		std::string data = std::to_string(*it);
		unsigned short dataSize = data.size();
		lines[level - 1] += data + ' ';

		// Fill the column with spaces except the current level
		for (int i = 0; i < height; ++i) {
			if (i != level - 1) {
				lines[i] += std::string(dataSize + 1, ' ');
			}
		}

		++it;
	}

	// Print the tree
	for (int i = 0; i < height; ++i) {
		std::cout << lines[i] << '\n';
	}


}

template <typename T>
void Tree<T>::BFS() const
{
	std::queue<Node*> queue;
	queue.push(root);
	while (!queue.empty())
	{
		Node* current = queue.front();
		queue.pop();
		std::cout << current->data << '\n';
		if (current->left)
			queue.push(current->left);
		if (current->right)
			queue.push(current->right);
	}

}