//============================================================================
// Name        : a7_primsAlgorithm.cpp
// Author      : 21132_Shreyash Halge
// Version     :
// Copyright   : Your copyright notice
// Description : Prim's Algorithm
//============================================================================

#include <iostream>
using namespace std;
#define MAX_INT 2147483647

class Graph
{
	int n;
	int** adjMat;


public:
	Graph(int n);
	int minKey(int [], bool []);
	void printMST(int []);
	void primMST();
};

Graph::Graph(int n)	//constructor
{
	this->n = n;
	adjMat = new int* [n];
	for (int i = 0; i< n; i++)
	{
		adjMat[i] = new int [n];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << "Enter the cost of telephone line between " << i << " and " << j << ": ";
			cin >> adjMat[i][j];
		}

	}
}

int Graph::minKey(int key[], bool mstSet[]) // returns index of vertex with minimum weight
{
    int min = MAX_INT, min_index;

    for (int v = 0; v < n; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

void Graph::printMST(int parent[])
{
    cout<<"Edge \tWeight\n";
    for (int i = 1; i < n; i++)
        cout<<parent[i]<<" - "<<i<<" \t"<<adjMat[i][parent[i]]<<" \n";
}

void Graph::primMST()
{
    int parent[n];
    int key[n];
    bool mstSet[n];

    for (int i = 0; i < n; i++)
        key[i] = MAX_INT, mstSet[i] = false;

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < n - 1; count++)
    {
        int u = minKey(key, mstSet);

        mstSet[u] = true;

        for (int v = 0; v < n; v++)
            if (adjMat[u][v] && mstSet[v] == false && adjMat[u][v] < key[v])
                parent[v] = u, key[v] = adjMat[u][v];
    }

    printMST(parent);
}



int main() {
	Graph rates(6);
	rates.primMST();
	return 0;
}
