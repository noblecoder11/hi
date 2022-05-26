#include <bits/stdc++.h>
using namespace std;

class graph
{
    int n;
    int **adjMat;
    int *inDegree;

public:
    queue<int>Q;
    graph(int n);
    void showAdjMat();
    void inDegreeCalculation();
    void topologicalSort();
};

graph::graph(int n)
{
    this->n = n;
    adjMat = new int* [n];
    inDegree = new int [n];
    for (int i = 0; i < n; i++)
    {
        adjMat[i] = new int[n];
        inDegree[i] = 0;
        for (int j = 0; j < n; j++)
        {
            adjMat[i][j] = 0;
        }
    }

    int s, d;
    while (s!=-1)
    {
        cout << "Enter source and destination indices(Enter -1 to stop): ";
        cin >> s >> d;
        if(s==-1) break;
        else{
            adjMat[s][d] = 1;
        } 
    }

}

void graph::inDegreeCalculation()
{
    for(int i=0; i<n;i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(adjMat[j][i] == 1) inDegree[i]++;
        }
        if(inDegree[i] == 0) Q.push(i);
    }
}

void graph::topologicalSort()
{
    inDegreeCalculation();
    while (!Q.empty())
    {
        int j = Q.front();
        Q.pop();
        cout << j << " ";

        for(int i = 0; i < n; i++)
        {
            if(adjMat[j][i] == 1)
            {
              inDegree[i]--;  
              if(inDegree[i] == 0)
              {
                  Q.push(i);
              }
            }
        }
    }
    
}

int main()
{
 graph myGraph(5);
    myGraph.topologicalSort();

return 0;
}
