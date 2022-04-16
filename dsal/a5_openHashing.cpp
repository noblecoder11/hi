//============================================================================
// Name        : a5_openHashing.cpp
// Author      : Shreyash Halge 21132
// Version     : 1.0.0
// Copyright   : 
// Description : Implement all the functions of a dictionary (ADT) using hashing and handle collisions using separate chaining using linked list. Data: Set of (key, value) pairs, Keys are mapped to values, Keys must be comparable, Keys must be unique. Standard Operations: Insert (key, value), Find(key), Delete(key)
//============================================================================

#include <iostream>
using namespace std;
#define SIZE 5

class HashEntry
{
private:
    string key, meaning;
    HashEntry* next;
public:
    HashEntry();
    HashEntry(string key, string meaning);
    friend class HashTable;
};

HashEntry::HashEntry()
{
    this -> key = "";
    this -> meaning = "";
    this->next = NULL;
}

HashEntry::HashEntry(string key, string meaning)
{
    this->key = key;
    this->meaning = meaning;
    this->next = NULL;
}

class HashTable
{
    HashEntry* ht[SIZE];

public:
    HashTable();
    static int comparisons;
    int hashFunction(string key);
    void insertKey(string key, string meaning);
    pair<int, int> searchKey(string key);
    void deleteKey(string key);
    void displayTable();
};

HashTable::HashTable()
{
    for (int i = 0; i < SIZE; i++)
    {
        ht[i] = NULL;
    }
}

int HashTable::comparisons = 0;

int HashTable::hashFunction(string key)
{
    return key.length()%SIZE;
}

void HashTable::insertKey(string key, string meaning)
{
    int hashIndex = hashFunction(key);

    HashEntry* temp = new HashEntry(key, meaning);

    if (ht[hashIndex] == NULL)
    {
        ht[hashIndex] = temp;
    }
    else
    {
        HashEntry* ptr = ht[hashIndex];
        while(ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        
        ptr->next = temp;
    }
}

pair<int, int> HashTable::searchKey(string key)
{
    int hashIndex = hashFunction(key);
    comparisons = 0;

    if (ht[hashIndex] == NULL)
    {
        comparisons++;
        // cout << "Key not present" << endl;
        return make_pair(comparisons, 0);
    }
    else
    {
        HashEntry* ptr = ht[hashIndex];
        
        while (true)
        {
            comparisons++;
            if (ptr->key == key)
                break;
            if (ptr->next == NULL)
                break;
            ptr = ptr -> next;
        }

        if (ptr->key != key)
        {
            // cout << "Key not found" << endl;
            return make_pair(comparisons, 0);
        }
        else
        {
            cout << hashIndex << ": " << ptr->key << " " << ptr->meaning << endl;
            return make_pair(comparisons, 1);
        }
        
        
    }
}

void HashTable::deleteKey(string key)
{
    int hashIndex = hashFunction(key);

    HashEntry* temp = ht[hashIndex];
    HashEntry* prev = NULL;
     
    // If head node itself holds the key to be deleted
    if (temp != NULL && temp->key == key)
    {
        ht[hashIndex] = temp->next; // Changed head
        delete temp;            // free old head
        return;
    }
    else
    {
        while (temp != NULL && temp->key != key)
        {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL)
        {
            cout << "Key not present" << endl;
            return;
        }

        prev->next = temp->next;
        delete temp;
    }
}

void HashTable::displayTable()
{
    cout << "------ DICTIONARY ------\n";
    for (int i = 0; i < SIZE; i++)
    {
        cout << i;
        HashEntry* ptr = ht[i];
        if (ptr == NULL)
        {
            cout << endl;
            continue;
        }
            

        while (ptr != NULL)
        {
            cout << " --> | " << ptr->key << ": " << ptr->meaning << " |"; 
            ptr = ptr -> next;
        }
        cout << endl;
    }
    cout << "------------------------\n";
}

int main()
{
    HashTable dictionary;
    // cout << "hello world" << endl;
    // dictionary.insertKey("hi", "greeting");
    // dictionary.insertKey("to", "word");
    // dictionary.displayTable();


    while (true)
    {
        cout << "\nMAIN MENU" << endl;
        cout << "1. Insert Key\n";
        cout << "2. Search Key\n";
        cout << "3. Display Table\n";
        cout << "4. Delete Key\n";
        cout << "5. Exit\n";

        string choice;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == "1")
        {
            string key, meaning;
            cout << "Enter key: ";
            cin >> key;
            cout << "Enter meaning: ";
            cin >> meaning;

            if (dictionary.searchKey(key).second == 1)
            {
                cout << "Key already exists" << endl;
            }
            else
            {
                dictionary.insertKey(key, meaning);
            }

        }
        else if (choice == "2")
        {
            string key;
            cout << "Enter key: ";
            cin >> key;

            pair <int, int> result = dictionary.searchKey(key);
            int comparisons = result.first;
            bool found = result.second;

            if(!found)
            {
                cout << "Key not present" << endl;    
                cout << "Comparisons: " << comparisons << endl;
            }
            else
            {
                cout << "Comparisons: " << comparisons << endl;
            }

        }
        else if (choice == "3")
        {
            dictionary.displayTable();
        }
        else if (choice == "4")
        {
            string key;
            cout << "Enter key: ";
            cin >> key;
            dictionary.deleteKey(key);
            cout << "Key deleted successfully\n";
        }
        else if (choice == "5")
        {
            cout << "Thank You. Exiting..." << endl;
            break;
        }
        else
        {
            cout << "Enter valid choice" << endl;
        }
    }

return 0;
}
