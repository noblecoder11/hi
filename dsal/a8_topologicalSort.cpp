//============================================================================
// Name        : a8_topologicalSort.cpp
// Author      : 21132_Shreyash Halge
// Version     : 1.0.0
// Copyright   : Your copyright notice
// Description : Write a C++/Java program to implement topological sorting on graph using object oriented programming features Design necessary class. (Use of graph)
//============================================================================

#include <iostream>
#include <stack>
using namespace std;

struct Node
{
	int dest;
	Node *next;

	Node()
	{
		dest = 0;
		next = NULL;
	}
	Node(int d)
	{
		dest = d;
		next = NULL;
	}
};

class Graph
{
	int n;
	Node** adjList;
	bool* visited;
	void topologicalSortUtil(int v, bool visited[], stack<int>& Stack);
public:
	Graph(int n);
	void push(int s, int d);
	void addEdge(int s, int d);
	void topologicalSort();
};

Graph::Graph(int n)
{

	this->n = n;
	adjList = new Node *[n];
	visited = new bool [n];
	for (int i = 0; i < n; i++)
	{
		adjList[i] = NULL;	bool* visited;
		visited[i] = false;
	}

	cout << "Graph with no edges created" << endl;

}

void Graph::push(int source, int destination)
{
	Node *newNode = new Node(destination);
	Node *ptr = adjList[source];

	if (ptr == NULL)
	{
		adjList[source] = newNode;
		return;
	}

	while (ptr->next != NULL)
		ptr = ptr->next;

	ptr->next = newNode;
}

void Graph::addEdge(int s, int d)
{
	push(s, d);
}

void Graph::topologicalSortUtil(int v, bool visited[],
                                stack<int>& Stack)
{

    visited[v] = true;

    Node* itr = adjList[v];
    while(itr->next != NULL)
    {
        if (!visited[itr->dest])
            topologicalSortUtil(itr->dest, visited, Stack);
    	itr = itr->next;
    }

    Stack.push(v);
}

void Graph::topologicalSort()
{
	stack<int> Stack;

	    bool* visited = new bool[n];
	    for (int i = 0; i < n; i++)
	        visited[i] = false;

	    for (int i = 0; i < n; i++)
	        if (visited[i] == false)
	            topologicalSortUtil(i, visited, Stack);

	    while (Stack.empty() == false) {
	        cout << Stack.top() << " ";
	        Stack.pop();
	    }
}

int main(){

	cout << "HELLO" << endl;
	Graph g(5);
	g.addEdge(0, 4);
	cout << "done";
	g.addEdge(1, 2);
	g.addEdge(2, 3);
	g.addEdge(4, 1);
	g.topologicalSort();
	cout << "Exiting" << endl;
}
