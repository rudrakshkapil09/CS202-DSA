//m-coloring of a graph
#include <iostream>
using namespace std;
const int nv = 10;
const int m = 3;

//special functions
int isSafe(int G[][nv], int colors[], int v, int c)
{
    for (int j = 0; j < nv; j++)
        if (G[v][j] && c == colors[j])
            return 0;
    return 1;
}

int assignColors(int G[][nv], int colors[], int v)
{
    if (v == nv) {
        cout << "Solved!\nThe colors are {";
        for (int k = 0; k < nv; k++) {
            cout << colors[k];
            (k == nv-1) ? cout << "}\n" : cout << ", ";
        }
        return 1;
    }
    else {
        for (int num = 1; num <= m; num++){
            if (isSafe(G, colors, v, num)) {
                colors[v] = num;
                if (assignColors(G, colors, v+1))
                    return 1;
                colors[v] = 0;
            }
        }
        return 0;
    }
    
}

//MAIN
int main()
{
    int graph[nv][nv] = {
        {0, 1, 0, 0, 1, 1, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 0, 1, 0},
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 1, 1},
        {0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
        {0, 0, 0, 1, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 1, 1, 0, 1}
    };
    
    int colors[nv];
    memset(colors, 0, sizeof(colors));
    if (!assignColors(graph, colors, 0))
        cout << "No solution :(";
}
