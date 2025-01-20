#pragma once
#include <iostream>
#include <stack>


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

	class Iterator // Iter using a stack, left, root, right
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
	};

public:
	Tree();
	Tree(const T& data);
	Tree(const Node* root);
	~Tree();

	void insert(const T& data);


	unsigned int getHeight() const;
	static unsigned int getHeight(const Node* node);

	unsigned int getSize() const;
	static unsigned int getSize(const Node* node);

	void print() const;
	static void print(const Node* node, unsigned int space = 0);

	unsigned int height = 0;

	Iterator begin() { return Iterator(root); }
	Iterator end() { return Iterator(nullptr); }

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
	
	while (true) // Until find a return
	{
		if (data < current->data) // Go left
		{
			if (current->left == nullptr) {
				current->left = new Node(data);
				return;
			}
			current = current->left; // Advance
		}
		else // Go right
		{
			if (current->right == nullptr) {
				current->right = new Node(data);
				return;
			}
			current = current->right; // Advance
		}
	}
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
void Tree<T>::print(const Tree<T>::Node* node, unsigned int space)
{
	for (unsigned int i = 0; i < space; ++i) std::cout << "| ";

	std::cout << node->data << '\n';

	if (node->right != nullptr)
		print(node->right, space + 1);
	if (node->left != nullptr)
		print(node->left, space + 1);
}