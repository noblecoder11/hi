//============================================================================
// Name        : a2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class bst
{
public:
	string key, meaning;
	static int comparisons;
	bst *left, *right;
	bst *root;
	bst();
	bst(string key, string meaning);
	bst* search(bst* root, string key);
	bst* insert(bst* root, string key, string meaning);
	void inorder(bst* root);
	void revinorder(bst* root);
	void update(bst* root, string key);
};

int bst::comparisons = 0;

bst::bst()
{
			this->key = "";
			this->meaning = "";
			this->left = this->right = NULL;
}

bst::bst(string key, string meaning)
{
			this->key = key;
			this->meaning = meaning;
			this->left = this->right = NULL;
}

bst* bst::search(bst* root, string key)
{

	comparisons++;
	if (root == NULL || root->key == key)
	{
		return root;
	}

	if (root->key > key)
	{
		search(root->left, key);
	}
	else
	{
		search(root->right, key);
	}
	cout << comparisons << endl;
	return root;

}

bst* bst::insert(bst* root, string key, string meaning)
{


	if (root == NULL)
	{
		return new bst(key, meaning);

	}

	if (root->key > key)
	{
		root->left = insert(root->left, key, meaning);
	}
	else
	{
		root->right = insert(root->right, key, meaning);
	}
	return root;
}

void bst::inorder(bst* root)
{
	if(root == NULL)
		return;

	inorder(root->left);
	cout << root->key << ": " << root->meaning << endl;
	inorder(root->right);
}

void bst::revinorder(bst* root)
{
	if(root == NULL)
		return;

	inorder(root->right);
	cout << root->key << ": " << root->meaning << endl;
	inorder(root->left);
}

void bst::update(bst* root, string key)
{
	bst* res = search(root, key);

	if (res == NULL)
	{
		cout << "No entry found" << endl;
	}
	else
	{
		cout << "Enter new meaning: ";
		string meaning;
		cin >> meaning;
		res->meaning = meaning;
	}
}

int main() {

	bst dictionary;
	bst* root = dictionary.root;
	root = dictionary.insert(root, "", "");
//	dictionary.insert(root, "Hi", "greeting");
//	dictionary.insert(root, "a", "greeting");
//	dictionary.insert(root, "b", "greeting");
//	dictionary.insert(root, "c", "greeting");
//	dictionary.insert(root, "d", "greeting");
	while(true)
	{
		cout << "Menu" << endl;
		cout << "1. Insert\n";
		cout << "2. Search\n";
		cout << "3. Ascending\n";
		cout << "4. Descending\n";
		cout << "5. Update Meaning\n";
		cout << "5. Exit\n";

		cout << "Enter your choice: ";
		int choice;
		cin >> choice;

		if (choice == 1)
		{

			string key, meaning;
			cout << "Enter key and its meaning: ";
			cin >> key >> meaning;
			dictionary.insert(root, key, meaning);
		}
		else if (choice == 2)
		{
			bst::comparisons = 0;
			string key, meaning;
			cout << "Enter key: ";
			cin >> key;
//			bst* result = dictionary.search(root, key);

//			if(result != NULL)
//			{
//				cout << "Found: " << result->key << ": " << result->meaning << endl;
//			}
//			else
//				cout << "NOT Found" << endl;
		}
		else if (choice == 3)
		{
			dictionary.inorder(root);
		}
		else if (choice == 4)
		{
			dictionary.revinorder(root);
		}
		else if (choice == 5)
		{
			cout << "Enter key whose meaning to update: ";
			string key;
			cin >> key;
			dictionary.update(root, key);
		}
		else if(choice == 6)
		{
			cout << "Exiting..." << endl;
			break;
		}
		else
		{
			cout << "Enter valid choice" << endl;
		}

	}

	return 0;
}
