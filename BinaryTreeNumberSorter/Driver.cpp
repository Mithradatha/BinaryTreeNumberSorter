/*
* Name: Samuel Kellar
* Email: skellar2014@my.fit.edu
* Purpose:
*	Create a binary search tree, in order
*	to perform various user inteneded functions
* Algorithm:
*	A) Create a BST
*	B) While the user wants to continue:
*		1. Ask for input
*		2. Perform expected output
*	C) Delete BST
*	D) If Vector Created:
*		1. Delete Vector
*/


#include "BinaryTree.h"
#include "RNG.h"
#include <iostream>
#include <string>
#include <stdlib.h>

int main() {

	string const cursor = "> ";

	auto clrScreen = []() {

		try {
			system("cls");
		} catch (const exception&) {
			try {
				system("clear");
			} catch (const exception&) {}
		}
	};

	auto isValid = [](int num) -> bool { return num > -1; };

	BinaryTree<int>* bt = new BinaryTree<int>;
	int root;
	
	cout << "Welcome, Would You Like To:" << endl << endl <<
		"1. Generate A Random Binary Search Tree" << endl <<
		"2. Generate Your Own Binary Search Tree" << endl <<
		endl << cursor;

	int input1;
	cin >> input1;

	switch (input1) {

		case 1:
		{
				  cout << endl << "How Many Elements Would You Like The Tree To Have:" 
					  << endl << endl << cursor;

				  int nElems;
				  cin >> nElems;

				  if (nElems < 1) break;

				  // if there are duplicate values generated randomly
				  cout << endl << "*Warning*: Tree Does Not Necessarily Have To Contain All " << 
					  nElems << " Elements..." << endl;

				  cout << endl << "What Range Should These Elements Be Within?" << endl <<
					  endl << "Min: ";

				  int min;
				  cin >> min;

				  if (!isValid(min)) break;

				  cout << "Max: ";

				  int max;
				  cin >> max;

				  if (!isValid(max)) break;

				  if (min > max) break;

				  clrScreen();
				  cout << "Generating Binary Search Tree..." << endl;

				  vector<int> nodes;
				  RNG rng(min, max);

				  for (int i = 0; i < nElems; ++i) 
						  nodes.push_back(rng.nextInt());

				  vector<int> sortedNodes = nodes;

				  sort(sortedNodes.begin(), sortedNodes.end());

				  // most likely scenario to create a balanced BST
				  root = sortedNodes.at(sortedNodes.size() / 2);
				  bt->insert(root);

				  for (auto& elem : nodes)
					  bt->insert(elem);

				  cout << "Binary Search Tree Finished Generating" << endl << endl;
		};
			break;
		
		case 2:

			cout << endl << "Please Enter The Value Of The Root Node: " << endl <<
				endl << cursor;

			cin >> root;

			if (!isValid(root)) break;
			
			clrScreen();
			cout << "Generating Binary Search Tree..." << endl;

			bt->insert(root);

			cout << "Binary Search Tree Finished Generating" << endl << endl;

			break;

		default:
			break;
	}

	bool outerRunning = true;

	do {

		cout <<
			"1. Add Node" << endl <<
			"2. Remove Node" << endl <<
			"3. Search For Node" << endl <<
			"4. Traverse Tree" << endl <<
			"5. Display Tree" << endl <<
			"6. Exit" << endl <<
			endl << cursor;
		
		int input2;
		cin >> input2;

		clrScreen();
		int val;

		switch (input2) {

			case 1:

				cout << "Node Value To Insert:" << endl <<
					endl << cursor;

				
				cin >> val;
				if (!isValid(val)) break;

				bt->insert(val);
				break;

			case 2:


				cout << "Node Value To Remove:" << endl <<
					endl << cursor;

				cin >> val;
				if (!isValid(val)) break; 

				bt->remove(val);
				break;

			case 3:

				cout << "Node Value To Search For:" << endl <<
					endl << cursor;

				cin >> val;
				if (!isValid(val)) break;

				cout << endl;

				(bt->contains(val)) ?
					cout << val << " Does Exist In Your Tree" << endl :
					cout << val << " Does Not Exist In Your Tree" << endl;
				break;

			case 4:

				cout << "Select Tree Traversal Type:" << endl << endl <<
					"1. Inorder" << endl <<
					"2. Preorder" << endl <<
					"3. Postorder" << endl <<
					"4. Levelorder" << endl <<
					"5. All Of The Above" << endl <<
					endl << cursor;

				int input3;
				cin >> input3;

				cout << endl;

				switch (input3) {

					case 1:

						bt->traverse(BinaryTree<int>::Traversal::INORDER);
						break;

					case 2:

						bt->traverse(BinaryTree<int>::Traversal::PREORDER);
						break;

					case 3:

						bt->traverse(BinaryTree<int>::Traversal::POSTORDER);
						break;

					case 4:

						bt->traverse(BinaryTree<int>::Traversal::LEVELORDER);
						break;

					case 5:

						bt->traverse();
						break;

					default:
						break;
				}

				break;

			case 5:

				cout << "Display:" << endl << endl <<
					"1. Full Tree" << endl <<
					"2. Sub Tree" << endl <<
					"3. Array" << endl <<
					endl << cursor;

				int input4;
				cin >> input4;

				cout << endl;

				switch (input4) {

					case 1:

						if (bt->getRoot())
						bt->display(bt->getRoot()->getData());
						cout << endl;
						break;

					case 2:

						cout << "Subtree Starting Node:" << endl <<
							endl << cursor;

						int val2;
						cin >> val2;

						if (!isValid(val2)) break;

						cout << endl;
						bt->display(val2);
						cout << endl;
						break;

					case 3:
					{
							  cout << endl;
							  if (!bt->getRoot()) break;
							  vector<int>* mVector = bt->toSortedVector();

							  int last = mVector->back();

							  cout << endl << "[";
							  for (auto& elem : *mVector) {

								  (elem == last) ? cout << elem : cout << elem << ", ";
							  }
							  cout << "]" << endl;

							  cout << endl;

							  delete mVector;
							  mVector = nullptr;
					};
						break;

					default:
						break;
				}
				break;

			case 6:

				outerRunning = false;
				break;

			default:
				break;
		}

		cout << endl;

	} while (outerRunning);

	delete bt;
	bt = nullptr;

	return 0;
}
