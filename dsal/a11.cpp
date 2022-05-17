//============================================================================
// Name        : a11_heapSort.cpp
// Author      : 21132 Shreyash Halge
// Date        : 16 May 2022
// Copyright   : Your copyright notice
// Description : Implement the Heap sort algorithm implemented in CPP/Java demonstrating heap data structure with modularity of programming language
//============================================================================
#include <iostream>
using namespace std;

class Heap
{
    int *heap;
    int last;

public:
    Heap(int x)
    {
        heap = new int[x + 1];
        last = 0;
    }

    void insert(int x)
    {
        int i = ++last;
        heap[i] = x;
        while (i != 0)
        {
            if (i == 0)
                continue;
            if (heap[i] > heap[i / 2] && i != 1)
                swap(heap[i], heap[i / 2]);
            i /= 2;
        }
        cout << "After insertion: ";
        for (int i = 1; i <= last; i++)
            cout << heap[i] << " ";
    }

    void deleteLast()
    {
        swap(heap[last], heap[1]);
        int size = last;
        last--;
        for (int i = 1; i <= size; i++)
        {
            int rt = 1, ch = 2;
            while (ch < last)
            {
                if (heap[ch + 1] > heap[ch])
                    ch++;
                if (heap[rt] < heap[ch])
                {
                    swap(heap[rt], heap[ch]);
                    rt = ch;
                    ch *= 2;
                }
                else
                    break;
            }
            if (last > 2)
                swap(heap[last--], heap[1]);
            else if (heap[1] > heap[2])
                swap(heap[1], heap[2]);
        }
        cout << "\nHeap sort: ";
        for (int i = 1; i <= size; i++)
            cout << heap[i] << " ";
        cout << endl;
    }
};

int main()
{
    bool menu = 1;
    int x;
    Heap* HP = new Heap(100);
    cout << "HEAP SORT" << endl;
    while (x!=-1)
    {
        cout << "\nEnter element to be inserted(Enter -1 to exit): ";
        cin >> x;
        if (x!=-1)
            HP->insert(x);
    }

    cout << "\nSorted List: ";
    HP->deleteLast();

    return 0;
}

/*
HEAP SORT

Enter element to be inserted(Enter -1 to exit): 4
After insertion: 4 
Enter element to be inserted(Enter -1 to exit): 10
After insertion: 10 4 
Enter element to be inserted(Enter -1 to exit): 3
After insertion: 10 4 3 
Enter element to be inserted(Enter -1 to exit): 5
After insertion: 10 5 3 4 
Enter element to be inserted(Enter -1 to exit): 1
After insertion: 10 5 3 4 1 
Enter element to be inserted(Enter -1 to exit): -1

Sorted List:
Heap sort: 1 3 4 5 10
*/
