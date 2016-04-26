#include "BinaryTree.h"

template <typename T>
BinaryTree<T>::~BinaryTree() {

	auto deconstruct = [](Node<T>* node) {

		if (node) {

			deconstruct(node->getLeftChild());
			deconstruct(node->getRightChild());
			delete node;
		}
	};

	deconstruct(root);
}

template <typename T>
void BinaryTree<T>::display(Traversal order) {

	if (order == Traversal::PREORDER) preOrder(root);
	else if (order == Traversal::INORDER) inOrder(root);
	else postOrder(root);
}

template <typename T>
bool BinaryTree<T>::insert(T const& _data, Node<T>* leaf) {

	if (!leaf) {
	
		root = new Node<T>(_data);
	}
}