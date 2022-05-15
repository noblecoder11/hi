//============================================================================
// Name        : a7_primsAlgorithm.cpp
// Author      : 21132_Shreyash Halge
// Date        : 16 May 2022
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
		for (int j = 0; j <= i; j++)
		{
			if(i==j)
			{
				adjMat[i][j] = 0;
			}
			else
			{
				cout << "Enter the cost of telephone line between " << i << " and " << j << "(enter -1 if no telephone line exists): ";
				int temp;
				cin >> temp;
				if(temp == -1)
					adjMat[i][j] = MAX_INT;
				else
					adjMat[i][j] = adjMat[j][i] = temp;
			}

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
    int totCost = 0;
    for (int i = 1; i < n; i++)
    {
        cout<<parent[i]<<" - "<<i<<" \t"<<adjMat[i][parent[i]]<<" \n";
        totCost += adjMat[i][parent[i]];
    }
    cout << totCost << endl;

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
	cout << "Enter number of offices: ";
	int n;
	cin >> n;

	Graph rates(n);

	rates.primMST();

	cout << "Exiting..." << endl;
	return 0;
}

/*
Enter number of offices: 4
Enter the cost of telephone line between 1 and 0(enter -1 if no telephone line exists): 7 
Enter the cost of telephone line between 2 and 0(enter -1 if no telephone line exists): 6
Enter the cost of telephone line between 2 and 1(enter -1 if no telephone line exists): 4
Enter the cost of telephone line between 3 and 0(enter -1 if no telephone line exists): 2
Enter the cost of telephone line between 3 and 1(enter -1 if no telephone line exists): 12
Enter the cost of telephone line between 3 and 2(enter -1 if no telephone line exists): 3
Edge    Weight
2 - 1   4
3 - 2   3
0 - 3   2
9
Exiting...
*/
