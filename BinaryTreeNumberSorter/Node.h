#ifndef NODE_H
#define NODE_H

using namespace std;

/*
* Node is a self-referential data structure, with pointers to
* a left child and a right child. Node also has generic data 
* associated with it.
*/

template <typename T>
class Node {

	public:
	
	// constructor initialization
	Node(T const& _data) : leftChild(nullptr), rightChild(nullptr), data(_data) {}

	bool isLeaf() const { return !(leftChild || rightChild); }	// no children
	bool isFull() const { return leftChild && rightChild; }	// two children
	bool hasLeftChild() const { return (leftChild) ? true : false; }	// left child
	bool hasRightChild() const { return (rightChild) ? true : false; }	// right child

	// getters
	Node* getLeftChild() const { return leftChild; }
	Node* getRightChild() const { return rightChild; }
	T getData() const { return data; }

	// setters
	void setLeftChild(Node* const leaf) { leftChild = leaf; }
	void setRightChild(Node* const leaf) { rightChild = leaf; }
	void setData(T const& _data) { data = _data; }

	private:

	Node* leftChild;
	Node* rightChild;

	T data;
};

#endif