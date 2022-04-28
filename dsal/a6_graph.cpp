//============================================================================
// Name        : a6_graphUsingList.cpp
// Author      : 21132_Shreyash Halge
// Version     : 1.0.0
// Start Date  : 18 April 2022
// End Date    :
// Copyright   : Your copyright notice
// Description : Represent a give graph using adjacency list to perform DFS and BFS. Use the map of the area around colleges the graph. Identify the prominent landmarks as nodes and perform DFS and BFS on that.
//============================================================================

#include <bits/stdc++.h>
using namespace std;

struct Node
{
	int dest;
	Node* next;

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

public:
	Graph(int n);
	~Graph();
	void addEdge(int s, int d);
	void push(int source, int destination);
	void showList();
	void bfs(int start);
	void dfs(int start);
};

Graph::Graph(int n)
{
	adjList = new Node* [n];

	for (int i = 0; i < n; i++)
	{
		adjList[i] = NULL;
	}

	this->n = n;

	cout << "Graph with no edges created" << endl;

}

Graph::~Graph()
{
	delete [] adjList;
}

void Graph::push(int source, int destination)
{
	Node* newNode = new Node(destination);
	Node* ptr = adjList[source];

	if(ptr == NULL)
	{
		adjList[source] = newNode;
		return;
	}

	while(ptr->next != NULL)
		ptr = ptr->next;

	ptr->next = newNode;
}

void Graph::addEdge(int source, int destination)
{
	push(source, destination);

}

void Graph::showList()
{
	for (int i = 0; i < n; i++)
	{
		cout << i << ": ";
		Node* temp = adjList[i];

		if (adjList[i] == NULL)
		{
			cout << endl;
			continue;
		}
//		cout << adjList[i]->dest << " ";


		while (temp->next != NULL)
		{
			cout << temp->dest << " ";
			temp = temp->next;
		}
		cout << temp->dest << " ";

		cout << endl;
	}
}

void Graph::bfs(int start)
{
	bool visited[n];
	
}

int main() {

	cout << "Enter number of nodes: ";
	int n;
	cin >> n;
	Graph nearbyMap(n);

	while (true)
	{

		cout << "MAIN MENU" << endl;
		cout << "1. AddEdge\n";
		cout << "2. View Adj List\n";
		cout << "3. BFS\n";
		cout << "4. DFS\n";
		cout << "5. Exit\n";

		string choice;
		cin >> choice;

		if (choice == "1")
		{
			int s, d;
			cout << "Enter the source vertex: ";
			cin >> s;
			cout << "Enter the destination vertex: ";
			cin >> d;
			nearbyMap.addEdge(s, d);
		}
		else if (choice == "2")
		{
			nearbyMap.showList();
		}
		else if (choice == "3")
		{
			cout << "Enter starting point: ";
			int start;
			cin >> start;
			nearbyMap.bfs(start);
			
			cout << "Work in Progress\n";
		}
		else if (choice == "4")
		{
			cout << "Enter starting point: ";
			int start;
			cin >> start;
			nearbyMap.dfs(start);
			cout << "Work in Progress\n";
		}
		else if (choice == "5")
		{
			cout << "Exited successfully" << endl;
			break;
		}
		else
		{
			cout << "Enter a valid choice\n";
		}
	}



	return 0;
}
