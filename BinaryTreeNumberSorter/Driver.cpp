#include "BinaryTree.h"

#include <iostream>

int main() {
	
	Node<int>* node1 = new Node<int>(1);
	Node<int>* node2 = new Node<int>(2);

	cout << node1->getData() << endl << node2->getData() << endl;

	Node<int>* node3 = new Node<int>(3);

	node2->setRightChild(node3);
	node1->setRightChild(node2);

	Node<int>* root = node1;

	cout << endl <<
		root->getRightChild()->getRightChild()->getData() << endl;

	return 0;
}
