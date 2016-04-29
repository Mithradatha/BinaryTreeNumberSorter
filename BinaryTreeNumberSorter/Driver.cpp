#include "BinaryTree.h"

#include <iostream>
#include <string>
#include "RNG.h"

int main() {
	
	BinaryTree<int>* bt = new BinaryTree<int>;

	bt->insert(19);
	bt->insert(31);
	bt->insert(22);
	bt->insert(20);
	bt->insert(59);
	bt->insert(7);
	bt->insert(43);
	bt->insert(43);
	bt->insert(5);
	bt->insert(10);
	bt->insert(9);
	bt->insert(3);
	bt->insert(4);

	bt->display();

	bt->render(0, bt->getRoot());

	vector<int>* mVector = bt->toSortedVector();
	
	int last = mVector->back();

	cout << endl << "[";
	for (auto& elem : *mVector) {
		
		(elem == last) ? cout << elem : cout << elem << ", ";
	}
	cout << "]" << endl;

	cout << endl;

	RNG rng(0, 10);

	for (int i = 0; i < 20; ++i)
	cout << rng.nextInt() << endl;

	delete mVector;

	delete bt;

	return 0;
}
