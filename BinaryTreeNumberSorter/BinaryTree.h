#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "Node.h"
#include <iomanip>
#include <functional>
#include <queue>
#include <vector>

using namespace std;

template <typename T>
class BinaryTree {

	public:

	enum class Traversal { PREORDER, INORDER, POSTORDER, LEVELORDER };

	BinaryTree() : root(nullptr) {}
	~BinaryTree();

	bool insert(T const& data) { return insert(data, root); }
	bool remove(T const& data) { return remove(data, root); }
	bool contains(T const& data) { return (search(data, root)) ? true : false; }
	void display(Traversal order);
	void display();
	void render(int spacing, Node<T>* node);
	vector<T>* toSortedVector() { vector<T>* mVector = new vector<T>(); toSortedVector(mVector, root); return mVector; }
	Node<T>* findMin(Node<T>* node);
	Node<T>* findMax(Node<T>* node);
	Node<T>* getRoot() const { return root; }
	Node<T>* parentOf(T const& data, Node<T>* node, Node<T>* parent);
	private:
	
	bool insert(T const& data, Node<T>* node);
	bool remove(T const& data, Node<T>* node);

	Node<T>* search(T const& data, Node<T>* node);
	
	void toSortedVector(vector<T>* mVector, Node<T>* node);

	void preOrder(Node<T>* node);
	void inOrder(Node<T>* node);
	void postOrder(Node<T>* node);
	void levelOrder(Node<T>* node);

	Node<T>* root;
};


template <typename T>
BinaryTree<T>::~BinaryTree() {

	function<void (Node<T>*)> deconstruct = [&](Node<T>* node) {

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
void BinaryTree<T>::display() {
	
	display(Traversal::INORDER);
	display(Traversal::PREORDER);
	display(Traversal::POSTORDER);
	display(Traversal::LEVELORDER);
}

template <typename T>
bool BinaryTree<T>::insert(T const& data, Node<T>* node) {

	if (!node) {

		root = new Node<T>(data);
		return true;
	}

	if (data < node->getData()) {

		if (node->hasLeftChild()) { insert(data, node->getLeftChild()); } 
		else {

			node->setLeftChild(new Node<T>(data));
			return true;
		}
	} else if (data > node->getData()) {

		if (node->hasRightChild()) { insert(data, node->getRightChild()); } 
		else {

			node->setRightChild(new Node<T>(data));
			return true;
		}
	} else {

		return false;
	}

	return false;
}

template <typename T>
bool BinaryTree<T>::remove(T const& data, Node<T>* node) {

	if (!node) { return false; }

	if (node == root && data == root->getData()) {

		if (root->hasLeftChild()) {

			root->setData(findMax(root->getLeftChild())->getData());
			
			if (root->getData() == root->getLeftChild()->getData()) {

				Node<T>* temp = root->getLeftChild();
				temp->setRightChild(root->getRightChild());
				delete root;
				root = temp;
				temp = nullptr;
				return true;

			} else { 
				remove(root->getData(), root->getLeftChild()); 
				return true; 
			}

		} else if (root->hasRightChild()) {

			root->setData(findMin(root->getRightChild())->getData());
			
			if (root->getData() == root->getRightChild()->getData()) {

				Node<T>* temp = root->getRightChild();
				temp->setLeftChild(root->getLeftChild());
				delete root;
				root = temp;
				temp = nullptr;
				return true;
			
			} else { 
				remove(root->getData(), root->getRightChild()); 
				return true; 
			}

		} else {

			delete root;
			root = nullptr;
			return true;
		}
	}

	Node<T>* parent = parentOf(data, node, node);
	Node<T>* mNode;

	string dir;

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

		mNode->setData(findMin(mNode->getRightChild())->getData());
		remove(mNode->getData(), mNode->getRightChild());
		return true;

	} else {	// mNode has one child
	
		if (mNode->hasLeftChild()) {

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
		
		parent = node;

		if (data < node->getData()) { return parentOf(data, node->getLeftChild(), parent); } 
		else { return parentOf(data, node->getRightChild(), parent); }
	}
}

template <typename T>
Node<T>* BinaryTree<T>::findMin(Node<T>* node) {

	if (!node) { return nullptr; }

	if (node->getLeftChild()) { return findMin(node->getLeftChild()); }
	else { return node; }
}

template <typename T>
Node<T>* BinaryTree<T>::findMax(Node<T>* node) {

	if (!node) { return nullptr; }

	if (node->getRightChild()) { return findMax(node->getRightChild()); } 
	else { return node; }
}

template <typename T>
void BinaryTree<T>::render(int spacing, Node<T>* node) {

	if (node) {

		render(spacing + 6, node->getRightChild());

		cout << setw(spacing) << " " << node->getData() << endl;

		render(spacing + 6, node->getLeftChild());
	}
}

template <typename T>
void BinaryTree<T>::toSortedVector(vector<T>* mVector, Node<T>* node) {

			if (node) {

				toSortedVector(mVector, node->getLeftChild());
				mVector->push_back(node->getData());
				toSortedVector(mVector, node->getRightChild());
			}
}

#endif