//============================================================================
// Name        : a2_bst.cpp
// Author      : 21132_Shreyash Halge
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string.h>
using namespace std;

class dictionary
{
public:
	string word, meaning;
	dictionary *left, *right;
	static int count;

	dictionary();
	dictionary(string dictionary, string meaning);	// constructor
	dictionary* insertWord(dictionary* root, string word, string meaning);
	void inorder(dictionary* root);
	void rev_inorder(dictionary* root);
	dictionary* search(dictionary* root, string word);
	dictionary* deleteWord(dictionary* root, string word);
	dictionary* minValueNode(dictionary* node);

};

int dictionary::count = 0;

dictionary::dictionary()
{
	this->word = "";
	this->meaning = "";
	this->left = this->right = NULL;
}

dictionary::dictionary(string word, string meaning)
{
	this->word = word;
	this->meaning = meaning;
	this->left = this->right = NULL;
}

dictionary* dictionary::insertWord(dictionary* root, string word, string meaning)
{

    // converting string to all lowercase
    for (int i = 0; i < word.length(); i++)
  	{
  		word[i] = tolower(word[i]);
  	}
    
	if (!root)
	{
		return new dictionary(word, meaning);
	}

	if (word < root->word)
	{
		root->left = insertWord(root->left, word, meaning);
	}
	else
	{
		root->right = insertWord(root->right, word, meaning);
	}

	return root;
}

void dictionary::inorder(dictionary* root)
{
	if (!root)
		return;

	inorder(root->left);
	cout << "=>" << root->word << ": " << root->meaning << endl;
	inorder(root->right);

}

void dictionary::rev_inorder(dictionary* root)
{
	if (!root)
		return;

	rev_inorder(root->right);
	cout << root->word << ": " << root->meaning << endl;
	rev_inorder(root->left);

}

dictionary* dictionary::search(dictionary* root, string word)
{
    // converting string to all lowercase
    for (int i = 0; i < word.length(); i++)
  	{
  		word[i] = tolower(word[i]);
  	}

	count++;

	if (root == NULL || root->word == word)
	   return root;

	// Key is greater than root's key
	if (root->word < word)
	   return search(root->right, word);

	// Key is smaller than root's key
	return search(root->left, word);
}

dictionary* dictionary::minValueNode(dictionary* node)
{
	    dictionary* current = node;

	    while (current && current->left != NULL)
	        current = current->left;

	    return current;
}

dictionary* dictionary::deleteWord(dictionary* root, string word)
{
    // converting string to all lowercase
    for (int i = 0; i < word.length(); i++)
  	{
  		word[i] = tolower(word[i]);
  	}

    if (root == NULL)
        return root;

    // traversing to find node
    if (word < root->word)
        root->left = deleteWord(root->left, word);

    else if (word > root->word)
        root->right = deleteWord(root->right, word);

    else {		// equal / found

        // node has no child
        if (root->left==NULL and root->right==NULL)
            return NULL;

        // node with only one child
        else if (root->left == NULL) {
            dictionary* temp = root->right;
            delete(root);
            return temp;
        }
        else if (root->right == NULL) {
            dictionary* temp = root->left;
            delete(root);
            return temp;
        }

        // with two children
        dictionary* temp = minValueNode(root->right);  // returns inorder successor

        root->word = temp->word;
        root->meaning = temp->meaning;// copy inorder successor data to root

        root->right = deleteWord(root->right, temp->word); // delete inorder successor
    }
    return root;
}

int main() {

	dictionary myDictionary;
	dictionary *root = NULL;

	cout << "\nWELCOME TO DICTIONARY!" << endl;

	while(true)
	{
		cout << "\n--------------------------\n";
		cout << "MENU\n";
		cout << "1. Create Dictionary\n";
		cout << "2. Add a word\n";
		cout << "3. Search\n";
		cout << "4. View in ascending order\n";
		cout << "5. View in descending order\n";
		cout << "6. Update meaning\n";
		cout << "7. Delete a word\n";
		cout << "8. Exit\n";
		cout << "--------------------------\n";

		cout << "Enter your choice: ";
		string choice;
		cin >> choice;

		if (choice == "1") // create
		{
			cout << "Enter words and their meaning. Enter ` key to finish.\n";
			while (true)
			{
				string word, meaning;
				cout << "Enter word: ";
				cin >> word;
				if (word == "`")
				{
					break;
				}
				else
				{
					cout << "Enter meaning of " << word << ": ";
					cin.ignore();
					getline(cin, meaning);
				}

				if (root == NULL)
					root = myDictionary.insertWord(root, word, meaning);
				else
					myDictionary.insertWord(root, word, meaning);
			}
		}
		else if (choice == "2") // insert
		{
			cout << "Enter a word: ";
			string word;
			cin >> word;
			cout << "Enter meaning: ";
			string meaning;
			cin.ignore();
			getline(cin, meaning);

			myDictionary.insertWord(root, word, meaning);
		}
		else if (choice == "3") // search
		{
			cout << "Enter a word: ";
			string word;
			cin >> word;
			dictionary::count = 0;
			dictionary* searchResult = myDictionary.search(root, word);
			if (searchResult ==  NULL)
			{
				cout << "Not Found" << endl;
			}
			else
			{
				cout << "=> " << searchResult->word <<": "<< searchResult->meaning << endl;
			}

			cout << "Number of comparisons: " << dictionary::count << endl;

		}
		else if (choice =="4") // ascending
		{
			cout << "Dictionary in ascending order:\n";
			if (root == NULL)
				cout << "Tree is empty\n";
			else
				myDictionary.inorder(root);
		}
		else if (choice == "5") //descending
		{
			cout << "Dictionary in descending order:\n";cout << "Dictionary in ascending order:\n";
			if (root == NULL)
				cout << "Tree is empty\n";
			else
				myDictionary.rev_inorder(root);
		}
		else if (choice == "6") // update meaning
		{
			cout << "Enter a word: ";
			string word;
			cin >> word;
			dictionary* searchResult = myDictionary.search(root, word);
			if (searchResult ==  NULL)
			{
				cout << "Not Found" << endl;
			}
			else
			{
				cout << "=> " << searchResult->word <<": "<< searchResult->meaning << endl;
				cout << "Enter new meaning: ";
				string meaning;
				cin.ignore();
				getline(cin, meaning);
				searchResult->meaning = meaning;
				cout << "Meaning Updated.\n";
			}
		}
		else if (choice == "7") // delete
		{
			cout << "Enter a word to delete: ";
			string word;
			cin >> word;
			myDictionary.deleteWord(root, word);
			cout << "Node deleted successfully.\n";
		}
		else if (choice == "8") // exit
		{
			cout << "Thank You. Exiting...";
			break;
		}
		else // exception handling
		{
			cout << "Incorrect choice entered." << endl;
		}

	}
	return 0;
}
