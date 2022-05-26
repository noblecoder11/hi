// #include <bits/stdc++.h>
#include <iostream>
using namespace std;

class stack
{
public:
    int arr[100];
    int top1 = -1;

    stack()
    {
        for (int i = 0; i < 100; i++)
        {
            arr[i]=0;
        }
        
    }
    void push(int x)
    {
        arr[++top1] = x;
    }
    int top()
    {
        return arr[top1];
    }
    void pop()
    {
        top1--;
    }
    bool empty()
    {
        if(top1 == -1) return true;
        return false;
    }
};

class queue 
{
    int arr[100];
    int front1 = -1, rear = -1;

public:
    queue()
    {
        for (int i = 0; i < 100; i++)
        {
            arr[i]=0;
        }  
    }
    void push(int x)
    {
        arr[++front1] = x;
    }
    int front()
    {
        return arr[front1];
    }
    void pop()
    {
        front1--;
    }
    bool empty()
    {
        if(front1 == rear) return true;
        return false;
    }
};

class node
{
    int data;
    node* next;

    node(){next=NULL;};
    node(int data){
        this->data=data;
        next=NULL;
    };
    friend class graph;
};

class graph
{
    int n;
    node **adjList;
    bool *visited;
    string * landmarks;

public:
    graph(int n);
    void bfs(int s);
    void dfs(int s);
    void showAdjList();
    void addEdge(int s, int d);
    void showLandmarks();
};

graph::graph(int n)
{
    this->n = n;
    adjList = new node* [n];
    visited = new bool[n];
    landmarks = new string[n];

    for(int i=0; i<n; i++)
    {
        adjList[i] = NULL;
        visited[i] = false;
        cout << "Enter Landmark " << i << ": ";
        cin >> landmarks[i];
    }

}

void graph::showAdjList()
{
    for (int i = 0; i < n; i++)
    {
        cout << i << " ";
        cout << landmarks[i] << ": ";
        node* ptr = adjList[i];
        if (adjList[i] == NULL)
        {
            cout << "\n";
            continue;
        }
        
        while (ptr->next != NULL)
        {
            cout << landmarks[ptr->data] << "->";
            ptr=ptr->next;
        }
        cout << landmarks[ptr->data];
        cout << endl;
    }
}

void graph::addEdge(int s, int d)
{
    node* ptr = adjList[s];
    node* newNode = new node(d);
    if(adjList[s] == NULL)
    {
        adjList[s] = newNode;
        cout << "here" << endl;
        return;
    }

    while(ptr->next != NULL)
    {
        ptr = ptr->next;
    }

    ptr->next = newNode;

}

void graph::bfs(int s)
{
    queue Q;
    
    Q.push(s);
    visited[s] = true;
    while(!Q.empty())
    {
        int u = Q.front();
        cout << landmarks[u] << " ";
        Q.pop();

        node* ptr = adjList[u];
        for (ptr = adjList[u]; ptr != NULL; ptr=ptr->next)
        {
            if(!visited[ptr->data])
            {
                visited[ptr->data] = true;
                Q.push(ptr->data);
            }
        }
        
    }
}

void graph::dfs(int s)
{
    stack S;

    for(int i = 0; i < n; i++) visited[i] = false;

    S.push(s);

    while(!S.empty())
    {
        int u = S.top();
        S.pop();

        if(!visited[u])
        {
            visited[u] = true;
            cout << landmarks[u] << " ";
        }
        node* ptr = adjList[u];
        for (ptr = adjList[u]; ptr!=NULL; ptr=ptr->next)
        {
            if(!visited[ptr->data])
            {
                S.push(ptr->data);
            }   
        }
    }
    cout << endl;
}

int main()
{
    graph myMap(5);
    myMap.addEdge(1, 2);
    myMap.addEdge(0, 3);
    myMap.addEdge(0, 4);
    myMap.addEdge(0, 1);
    myMap.bfs(0);
    cout << "dfs: ";
    myMap.dfs(0);
    myMap.showAdjList();
return 0;
}
