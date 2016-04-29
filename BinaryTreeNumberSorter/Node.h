#ifndef NODE_H
#define NODE_H

using namespace std;

template <typename T>
class Node {

	public:
	
	Node(T const& _data) : leftChild(nullptr), rightChild(nullptr), data(_data) {}

	bool isLeaf() const { return !(leftChild || rightChild); }
	bool isFull() const { return leftChild && rightChild; }
	bool hasLeftChild() const { return (leftChild) ? true : false; }
	bool hasRightChild() const { return (rightChild) ? true : false; }

	Node* getLeftChild() const { return leftChild; }
	Node* getRightChild() const { return rightChild; }
	T getData() const { return data; }

	void setLeftChild(Node* const leaf) { leftChild = leaf; }
	void setRightChild(Node* const leaf) { rightChild = leaf; }
	void setData(T const& _data) { data = _data; }

	private:

	Node* leftChild;
	Node* rightChild;

	T data;
};

#endif