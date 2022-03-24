//============================================================================
// Name        : a4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#define SIZE 2069

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

	void insert(long int telephoneNo, string name)
	{
		int hashIndex = hashFunction(telephoneNo);
		cout << "hash index while inserting " << hashIndex << endl;
//		HashEntry newHashEntry(telephoneNo, name);
//		cout << "New hash entry: " << newHashEntry.telephoneNo << newHashEntry.name << endl;
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
			cout << "just after inserting: " << ht[hashIndex].telephoneNo << ht[hashIndex].name << endl;
	}

	void display(long int telephoneNo)
	{
		int hashIndex =  hashFunction(telephoneNo);
		int started = hashIndex-1;
		cout << "hash Index: " << hashIndex << endl;
//		ht[hashIndex].telephoneNo = 123;
		cout << "data: " << ht[hashIndex].telephoneNo << endl;
		bool found = false;
		while (!found)
		{
//			cout << "Stuck here" << endl;
			if(ht[hashIndex].telephoneNo == telephoneNo)
			{
				cout << telephoneNo << ht[hashIndex].name;
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
	}


	void showTable(){
		for(int i=0;i<SIZE;i++){
			if(ht[i].telephoneNo!=0){
				cout<<i<<":"<<ht[i].telephoneNo<<" "<<ht[i].name;
			}
		}
	}


};

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	HashTable directory;

	bool on = true;
	while (on)
	{

		cout << "1. Insert" << endl;
		cout << "2. Display" << endl;
		cout << "3. Exit" << endl;
		string choice;
		cin >> choice;

		if (choice == "1")
		{
			long int telephoneNo;
			string name;
			cout << "Enter telephone number: ";
			cin >> telephoneNo;
			cout << "Enter name: ";
			cin >> name;

			directory.insert(telephoneNo, name);
			directory.showTable();


		}
		else if (choice == "2")
		{
			directory.showTable();
			long int telephoneNo;
			cout << "Enter telephone no: ";
			cin >> telephoneNo;
			directory.display(telephoneNo);
			cout << "after display"<< endl;
		}
		else if (choice == "3")
		{
			on = false;
		}
		else
		{
			cout << "Invalid choice" << endl;
		}
	}
	return 0;
}
