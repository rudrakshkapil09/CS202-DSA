//K-cores in an undirected graph
#include <iostream>
#include <vector>
using namespace std;
const int nv = 9, K = 3;

//special functions
void calculatedegrees(int G[][nv], vector<int> &degrees, int i)
{
    for (int j = 0; j < nv; j++)
        if (G[i][j])
            degrees[i]++;
}

int DFS(int G[][nv], int v, vector<int> &visited, vector<int> &degree)
{
    visited[v] = 1;
    for (int j = 0; j < nv; j++) {
        if (G[v][j]) {
            if (degree[v] < K)
                degree[j]--;
            if (!visited[j]) {
                if (DFS(G, j, visited, degree))
                    degree[v]--;
            }
        }
    }
    return (degree[v] < K);
}

void printOutput(int G[][nv])
{
    vector<int> visited(nv, 0);
    vector<int> processed(nv, 0);
    vector<int> degree(nv, 0);
    
    int mindeg = 999;
    int start = 0;
    for (int i = 0; i < nv; i++) {
        calculatedegrees(G, degree, i);
        if (degree[i] < mindeg) {
            mindeg = degree[i];
            start = i;
        }
    }
    
    DFS(G, start, visited, degree);
    for (int i = 0; i < nv; i++)    //for any remaining unvisited
        if (!visited[i])
            DFS(G, i, visited, degree);
    
    cout << "K-cores:\n";
    for (int i = 0; i < nv; i++) {
        if (degree[i] < K)
            continue;
        cout << "[" << i << "] => ";
        for (int j = 0; j < nv; j++)
            if (G[i][j] && degree[j] >= K)
                cout << j << " -> ";
        cout << endl;
    }
}

//MAIN
int main()
{
    int G[nv][nv] = {
        {0, 1, 1, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 1, 0, 0, 0},
        {1, 1, 0, 1, 1, 1, 1, 0, 0},
        {0, 0, 1, 0, 1, 0, 1, 1, 0},
        {0, 0, 1, 1, 0, 0, 1, 1, 0},
        {0, 1, 1, 0, 0, 0, 1, 0, 1},
        {0, 0, 1, 1, 1, 1, 0, 1, 1},
        {0, 0, 0, 1, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0}
    };
    
    printOutput(G);
}
