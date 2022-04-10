//============================================================================
// Name        : a4.cpp
// Author      : 21132_Shreyash Halge
// Version     : 1.0.0
// Copyright   :
// Description : Telephone directory with hashing (linear probing with/without replacement)
//============================================================================

#include <iostream>
using namespace std;
#define SIZE 3

class HashEntry
{
	long int telephoneNo;
	string name;
public:
	friend class HashTable;
	HashEntry()
	{
		this->telephoneNo = 0;
		this->name = "";
	}

	HashEntry(long int telephoneNo, string name)
		{
			this->telephoneNo = telephoneNo;
			this->name = name;
		}
};

class HashTable
{
	HashEntry ht[SIZE];

public:

	int hashFunction (long int telephoneNo)
	{
//		int val = 1;
		return telephoneNo%SIZE;
	}

	// without chaining, without replacement
	void insert(long int telephoneNo, string name)
	{
		int hashIndex = hashFunction(telephoneNo);
//		HashEntry newHashEntry(telephoneNo, name);
			bool inserted = false;
			while(!inserted)
			{
				if (ht[hashIndex].telephoneNo == 0)
				{
					ht[hashIndex].telephoneNo = telephoneNo;
					ht[hashIndex].name = name;
					inserted = true;
					break;
				}
				else
				{
					hashIndex = (hashIndex+1)%SIZE;
				}
			}

	}

	void insertReplacement(long int telephoneNo, string name)
	{
		int hashIndex = hashFunction(telephoneNo);
		if (ht[hashIndex].telephoneNo != 0)
		{
			bool matched = (hashFunction(ht[hashIndex].telephoneNo) == hashIndex);
			if (matched)
			{
				insert(telephoneNo, name);
			}
			else
			{
				long int tempPhone = ht[hashIndex].telephoneNo;
				string tempName = ht[hashIndex].name;
				ht[hashIndex].telephoneNo = telephoneNo;
				ht[hashIndex].name = name;
				insert(tempPhone, tempName);
			}
		}
		else
		{
			insert(telephoneNo, name);
		}
	}

	int search(long int telephoneNo)
	{
		int hashIndex =  hashFunction(telephoneNo);
		int started = hashIndex-1;
		bool found = false;
		int comparisons = 0;
		while (!found)
		{
			comparisons++;
			if(ht[hashIndex].telephoneNo == telephoneNo)
			{
				cout << telephoneNo << ": " << ht[hashIndex].name << endl;
				found = true;
			}
			else if (hashIndex == started)
			{
				cout << "Not Found" << endl;
				break;
			}
			else
			{
				hashIndex = (hashIndex + 1)%SIZE;
			}
		}
		return comparisons;
	}


	void showTable(){
		cout <<"Hash table"<< endl;
		for(int i=0;i<SIZE;i++)
		{
			if(ht[i].telephoneNo!=0)
				cout<<i<<":"<<ht[i].telephoneNo<<" "<<ht[i].name << endl;
		}
	}

	int getSize()
	{
		int count = 0;
		for(int i=0;i<SIZE;i++)
		{
			if(ht[i].telephoneNo!=0)
				count++;
		}
		return count;
	}
};

int main() {
	cout << "Telephone directory" << endl; // prints !!!Hello World!!!
	HashTable directory;
	HashTable directoryWithReplacement;

	bool on = true;
	while (on)
	{
		cout << "MAIN MENU" << endl;
		cout << "1. Insert" << endl;
		cout << "2. Display" << endl;
		cout << "3. Search" << endl;
		cout << "4. Exit" << endl;
		string choice;
		cin >> choice;

		if (choice == "1")
		{
			bool takeInput = 1;

			while (takeInput)
			{
				if (directory.getSize() < SIZE)
				{
					cout << "Add user?(0/1): ";
					cin >> takeInput;
				}
				else
				{
					cout << "Directory is now full." << endl;
					break;
				}

				long int telephoneNo;
				string name;
				cout << "Enter telephone number: ";
				cin >> telephoneNo;
				cout << "Enter name: ";
				cin >> name;

				directory.insert(telephoneNo, name);
				directoryWithReplacement.insertReplacement(telephoneNo, name);

			}
		}
		else if (choice == "2")
		{
			directory.showTable();
			directoryWithReplacement.showTable();
		}
		else if (choice == "3")
		{
			long int telephoneNo;
			cout << "Enter telephone no: ";
			cin >> telephoneNo;
			int compar = directory.search(telephoneNo);
			int comparWithRepl = directoryWithReplacement.search(telephoneNo);

			cout << "Number of comparisons without replacement: " << compar << endl;
			cout << "Number of comparisons with replacement: " << comparWithRepl << endl;
		}
		else if (choice == "4")
		{
			on = false;
			cout << "Thank you. Exiting..." << endl;
		}
		else
		{
			cout << "Invalid choice" << endl;
		}
	}
	return 0;
}
