//============================================================================
// Name        : a8_topologicalSort.cpp
// Author      : 21132_Shreyash Halge
// Date        : 16-05-2022
// Copyright   : Your copyright notice
// Description : Write a C++/Java program to implement topological sorting on graph using object oriented programming features Design necessary class ( Use of graph)
//============================================================================

#include <iostream>
using namespace std;

class Queue
{
public:
    class qNode
    {
    private:
        int data;
        qNode *next;

    public:
        friend class Queue;
        qNode()
        {
            data = -1;
            next = nullptr;
        }
        qNode(int x)
        {
            data = x;
            next = nullptr;
        }
    };
    Queue() { front = back = nullptr; }

private:
    qNode *front;
    qNode *back;

public:
    bool isEmpty() { return (front == nullptr && back == nullptr ? 1 : 0); }

    void enqueue(int x)
    {
        qNode *temp;
        temp = new qNode(x);
        if (front == nullptr && back == nullptr)
        {
            front = back = temp;
            return;
        }
        back->next = temp;
        back = temp;
    }

    int dequeue()
    {
        qNode *temp = front;
        front = front->next;
        int x = temp->data;
        if (front == nullptr)
            back = nullptr;
        delete temp;
        return x;
    }

    int frontElement()
    {
        if (front != nullptr)
            return front->data;
        return -1;
    }
};

class Graph
{
    int adjMatrix[20][20];
    int isVisited[20];
    int B[20];
    int size;

public:
    Graph(int x)
    {
        size = x;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
                adjMatrix[i][j] = 0;
        }
    }

    void insert(int, int, int &);

    int indegree(int);

    void showAdjMatrix();

    void topoSort();
};

void Graph::insert(int x, int y, int &cnt)
{
    if (adjMatrix[y][x] == 0)
        adjMatrix[x][y] = 1;
    else
    {
        cout << "\nShould be Directed Acyclic Graph (DAG)" << endl;
        cnt--;
    }
    cnt++;
}

int Graph::indegree(int x)
{
    int in_cnt = 0;
    for (int i = 0; i < size; i++)
    {
        if (adjMatrix[i][x] == 1)
            in_cnt++;
    }
    return in_cnt++;
}

void Graph::showAdjMatrix()
{
    cout << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            cout << adjMatrix[i][j] << "   ";
        cout << endl;
    }
}

void Graph::topoSort()
{
    Queue q;
    int j = 0;
    for (int i = 0; i < size; i++)
    {
        isVisited[i] = indegree(i);
        if (isVisited[i] == 0)
            q.enqueue(i);
    }
    while (!q.isEmpty())
    {
        int k = q.frontElement();
        q.dequeue();
        B[j++] = k;

        for (int i = 0; i < size; i++)
        {
            if (adjMatrix[k][i] == 1)
            {
                adjMatrix[k][i] = 0;
                isVisited[i] = isVisited[i] - 1;
                if (isVisited[i] == 0)
                    q.enqueue(i);
            }
        }
    }

    for (int i = 0; i < size; i++)
        cout << B[i] << ", ";
    cout << endl;
}

int main()
{
    bool menu = 1;
    int size;
    cout << "\nEnter number of vertices: ";
    cin >> size;
    Graph g(size);
    int ch;
    int cnt = 0;
    while (menu)
    {
        cout << "\n\n---- MENU ----\n1.Add edges \n2.Show adjacency matrix\n3.Topological Sort\n-1. Exit" << endl;
        cout << "Enter choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            int x, y;
            while (x!=-1)
            {
                cout << "\nSource(Enter -1 to stop): ";
                cin >> x;
                cout << "Destination: ";
                cin >> y;
                if(x!=-1)
                    g.insert(x, y, cnt);
            }
            break;

        case 2:
            g.showAdjMatrix();
            break;

        case 3:
            g.topoSort();
            break;

        case -1:
            menu = 0;
            cout << "Exiting..." << endl;
            break;

        default:
            break;
        }
    }

    return 0;
}

/*

Enter number of vertices: 6


---- MENU ----
1.Add edges 
2.Show adjacency matrix
3.Topological Sort
-1. Exit
Enter choice: 1

Source(Enter -1 to stop): 5
Destination: 0

Source(Enter -1 to stop): 5
Destination: 2

Source(Enter -1 to stop): 4
Destination: 0

Source(Enter -1 to stop): 4
Destination: 1

Source(Enter -1 to stop): 2
Destination: 3

Source(Enter -1 to stop): 3
Destination: 1

Source(Enter -1 to stop): -1
Destination: -1


---- MENU ----
1.Add edges
2.Show adjacency matrix
3.Topological Sort
-1. Exit
Enter choice: 2

0   0   0   0   0   0
0   0   0   0   0   0
0   0   0   1   0   0
0   1   0   0   0   0
1   1   0   0   0   0
1   0   1   0   0   0


---- MENU ----
1.Add edges
2.Show adjacency matrix
3.Topological Sort
-1. Exit
Enter choice: 3
4, 5, 0, 2, 3, 1, 


---- MENU ----
1.Add edges
2.Show adjacency matrix
3.Topological Sort
-1. Exit
Enter choice: -1
*/
