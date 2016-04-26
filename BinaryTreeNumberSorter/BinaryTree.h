#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "Node.h"

using namespace std;

template <typename T>
class BinaryTree {

	public:

	enum class Traversal { PREORDER, INORDER, POSTORDER };

	BinaryTree() : root(nullptr) {}
	~BinaryTree();

	bool insert(T const& _data) { return insert(_data, root); }
	bool remove(T const& _data) { return remove(_data, root); }
	void display(Traversal order);
	sam;
	private:
	
	bool insert(T const& _data, Node<T>* node);
	bool remove(T const& _data, Node<T>* node);

	void preOrder(Node<T>* node);
	void inOrder(Node<T>* node);
	void postOrder(Node<T>* node);

	Node<T>* root;
};

#endif