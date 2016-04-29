#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "Node.h"
#include <iomanip>
#include <functional>
#include <queue>
#include <vector>

using namespace std;

/*
* Binary Tree a container-esque data structure used to store data in a sorted fashion. 
* No duplicate data is allowed within the Binary tree, so all the Nodes are unique.
* Binary tree holds a pointer to the root Node in the tree
*
* This implementation of a Binary Search Tree allows for:
*
* -Traversal: Preorder, Inorder, Postorder, Levelorder
* -Insertion
* -Deletion
* -Searching
* -Displaying: Full Tree, Sub Tree
* -Getting The Root
* -Conversion To A Sorted Vector
*/

template <typename T>
class BinaryTree {

	public:

	enum class Traversal { PREORDER, INORDER, POSTORDER, LEVELORDER };

	BinaryTree() : root(nullptr) {}
	~BinaryTree();

	bool insert(T const& data) { return insert(data, root); }	// add a node
	bool remove(T const& data) { return remove(data, root); }	// remove a node
	
	// return true if node exists, else false
	bool contains(T const& data) { return (search(data, root)) ? true : false; }
	
	void traverse();	// traverse using every traversal pattern
	void traverse(Traversal order);	// traverse using only the given pattern
	
	// display the subtree to output, based on the node associated with the given data
	void display(T const& data) { display(0, search(data, root)); }
	
	vector<T>* toSortedVector();	// return the vector form of the binary search tree
	
	Node<T>* getRoot() const { return root; }	// return the binary search tree root
	
	private:
	
	bool insert(T const& data, Node<T>* node);	// insert a new node
	bool remove(T const& data, Node<T>* node);	// remove an old node

	void preOrder(Node<T>* node);	// traverse in preorder
	void inOrder(Node<T>* node);	// traverse inorder
	void postOrder(Node<T>* node);	// traverse postorder
	void levelOrder(Node<T>* node);	// traverse levelorder

	void display(int spacing, Node<T>* node);	// display the subtree

	void toSortedVector(vector<T>* mVector, Node<T>* node);	// convert from BST to vector

	// if the node exists within the BST, return its pointer
	Node<T>* search(T const& data, Node<T>* node);

	// if the node exists within the BST, return its parent's pointer
	Node<T>* parentOf(T const& data, Node<T>* node, Node<T>* parent);

	Node<T>* findMin(Node<T>* node);	// return the minimum Node in the BST
	Node<T>* findMax(Node<T>* node);	// return the maximum Node in the BST

	Node<T>* root;	// Binary Search Tree root
};


template <typename T>
BinaryTree<T>::~BinaryTree() {	// destructor deletes all the Nodes in the BST

	// lamda functions can't use recursion, so I did this instead...
	// the function returns nothing, but takes in a node as a parameter

	function<void (Node<T>*)> deconstruct = [&](Node<T>* node) {

		if (node) {

			// postorder deletion
			deconstruct(node->getLeftChild());
			deconstruct(node->getRightChild());
			delete node;
		}
	};

	deconstruct(root);
}

template <typename T>
void BinaryTree<T>::traverse(Traversal order) {

	if (order == Traversal::PREORDER) { 
		
		cout << "Preorder:   ";  
		preOrder(root); 
		cout << endl;

	} else if (order == Traversal::INORDER) { 
		
		cout << "Inorder:    "; 
		inOrder(root); 
		cout << endl;

	} else if (order == Traversal::POSTORDER) { 
		
		cout << "Postorder:  "; 
		postOrder(root); 
		cout << endl;

	} else { 
		
		cout << "Levelorder: "; 
		levelOrder(root); 
		cout << endl;

	}
}

template <typename T>
void BinaryTree<T>::traverse() {
	
	traverse(Traversal::INORDER);
	traverse(Traversal::PREORDER);
	traverse(Traversal::POSTORDER);
	traverse(Traversal::LEVELORDER);
}

/*
* It is the responsibility of whomever calls this function to delete
* the vector, in order to free resources
*/
template <typename T>
vector<T>* BinaryTree<T>::toSortedVector() {
	
	vector<T>* mVector = new vector<T>();
	toSortedVector(mVector, root); 
	return mVector; 
}

template <typename T>
bool BinaryTree<T>::insert(T const& data, Node<T>* node) {

	if (!node) {	// if there is no root

		root = new Node<T>(data);
		return true;
	}

	if (data < node->getData()) {	// if the data is less than, go left

		// while node can traverse farther to the left
		if (node->hasLeftChild()) { insert(data, node->getLeftChild()); } 
		else {	// node has no left child

			node->setLeftChild(new Node<T>(data));
			return true;
		}

	} else if (data > node->getData()) {	// if the data is greater than, go right

		// while node can traverse farther to the right
		if (node->hasRightChild()) { insert(data, node->getRightChild()); } 
		else {	// node has no right child

			node->setRightChild(new Node<T>(data));
			return true;
		}

	} else {	// if the data is equal to current node, return because no duplicate values

		return false;
	}

	return false;
}

template <typename T>
bool BinaryTree<T>::remove(T const& data, Node<T>* node) {

	if (!node) { return false; } // if the node is null

	// if you're trying to remove a root node
	if (node == root && data == root->getData()) {

		if (root->hasLeftChild()) {	// try left first

			// purposefully create a duplicate node
			root->setData(findMax(root->getLeftChild())->getData());
			
			// if the max node was the root node's immediate left child
			if (root->getData() == root->getLeftChild()->getData()) {

				// maximum means farthest right, so if the farthest right
				// is the root's immediate left, then the root's immediate
				// left has no right child
				
				Node<T>* temp = root->getLeftChild();
				temp->setRightChild(root->getRightChild());
				delete root;
				root = temp;
				temp = nullptr;
				return true;

			} else { // if the max node is farther down the tree
				remove(root->getData(), root->getLeftChild()); 
				return true; 
			}

		} else if (root->hasRightChild()) {	// try right child

			// purposefully create a duplicate node
			root->setData(findMin(root->getRightChild())->getData());
			
			// if the min node was the root node's immediate right child
			if (root->getData() == root->getRightChild()->getData()) {

				// minimum means farthest left, so if the farthest left
				// is the root's immediate right, then the root's immediate
				// right has no left child

				Node<T>* temp = root->getRightChild();
				temp->setLeftChild(root->getLeftChild());
				delete root;
				root = temp;
				temp = nullptr;
				return true;
			
			} else { // if the min node is farther down the tree
				remove(root->getData(), root->getRightChild()); 
				return true; 
			}

		} else { // if the root is a leaf

			delete root;
			root = nullptr;
			return true;
		}
	}

	// get a reference to the node's parent
	Node<T>* parent = parentOf(data, node, node);
	Node<T>* mNode;	// node to remove

	string dir;	// direction of traversal

	auto setRef = [](Node<T>* _parent, string _dir, Node<T>* leaf) {

		if (_dir == "left") { _parent->setLeftChild(leaf); } 
		else { _parent->setRightChild(leaf); }
	};

	if (parent->hasLeftChild() && parent->getLeftChild()->getData() == data) { 
		mNode = parent->getLeftChild();
		dir = "left";
	
	} else {
		mNode = parent->getRightChild();
		dir = "right";
	}

	if (mNode->isLeaf()) {

		delete mNode;
		mNode = nullptr;
		setRef(parent, dir, nullptr);
		return true;

	} else if (mNode->isFull()) {

		// could be either min or max, completely arbitrary
		mNode->setData(findMin(mNode->getRightChild())->getData());
		remove(mNode->getData(), mNode->getRightChild());
		return true;

	} else {	// mNode has one child
	
		if (mNode->hasLeftChild()) {	// mNode has a left child

			Node<T>* temp = mNode;
			mNode = mNode->getLeftChild();
			delete temp;
			temp = nullptr;
			setRef(parent, dir, mNode);
			return true;

		} else {	// mNode has a right child

			Node<T>* temp = mNode;
			mNode = mNode->getRightChild();
			delete temp;
			temp = nullptr;
			setRef(parent, dir, mNode);
			return true;
		}
	}

	return false;
}

template <typename T>
void BinaryTree<T>::preOrder(Node<T>* node) {

	if (node) {

		cout << node->getData() << " ";
		preOrder(node->getLeftChild());
		preOrder(node->getRightChild());
	}
}

template <typename T>
void BinaryTree<T>::inOrder(Node<T>* node) {

	if (node) {

		inOrder(node->getLeftChild());
		cout << node->getData() << " ";
		inOrder(node->getRightChild());
	}
}

template <typename T>
void BinaryTree<T>::postOrder(Node<T>* node) {

	if (node) {

		postOrder(node->getLeftChild());
		postOrder(node->getRightChild());
		cout << node->getData() << " ";
	}
}

template <typename T>
void BinaryTree<T>::levelOrder(Node<T>* node) {

	if (!node) return;

	queue<Node<T>*> mQ;

	mQ.push(node);

	while (!mQ.empty()) {

		Node<T>* current = mQ.front();
		cout << current->getData() << " ";

		if (current->hasLeftChild()) mQ.push(current->getLeftChild());

		if (current->hasRightChild()) mQ.push(current->getRightChild());

		mQ.pop();
	}
}

template <typename T>
Node<T>* BinaryTree<T>::search(T const& data, Node<T>* node) {

	if (!node) { return nullptr; }

	if (data == node->getData()) { return node; }
	else if (data < node->getData()) { return search(data, node->getLeftChild()); } 
	else { return search(data, node->getRightChild()); }
}

template <typename T>
Node<T>* BinaryTree<T>::parentOf(T const& data, Node<T>* node, Node<T>* parent) {

	if (!node) { return nullptr; }

	if (data == node->getData()) { return parent; } 
	else {
		
		parent = node;	// keep a reference to the node's parent

		if (data < node->getData()) { return parentOf(data, node->getLeftChild(), parent); } 
		else { return parentOf(data, node->getRightChild(), parent); }
	}
}

template <typename T>
Node<T>* BinaryTree<T>::findMin(Node<T>* node) {

	if (!node) { return nullptr; }

	// minimum is always to the left in a BST
	if (node->getLeftChild()) { return findMin(node->getLeftChild()); }
	else { return node; }
}

template <typename T>
Node<T>* BinaryTree<T>::findMax(Node<T>* node) {

	if (!node) { return nullptr; }

	// maximum is always to the right in BST
	if (node->getRightChild()) { return findMax(node->getRightChild()); } 
	else { return node; }
}

template <typename T>
void BinaryTree<T>::display(int spacing, Node<T>* node) {

	// inorder output, but gets right child before left

	if (node) {

		display(spacing + 6, node->getRightChild());

		cout << setw(spacing) << " " << node->getData() << endl;

		display(spacing + 6, node->getLeftChild());
	}
}

template <typename T>
void BinaryTree<T>::toSortedVector(vector<T>* mVector, Node<T>* node) {

	// inorder traversal makes it sorted

			if (node) {

				toSortedVector(mVector, node->getLeftChild());
				mVector->push_back(node->getData());
				toSortedVector(mVector, node->getRightChild());
			}
}

#endif