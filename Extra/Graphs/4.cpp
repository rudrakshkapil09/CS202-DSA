//Detecting negative cycle in a graph - Floyd Warshall
#include <iostream>
using namespace std;
const int nv = 4;

//special functions
int floydWarshall(int G[][nv], int dist[][nv])
{
    for (int k = 0; k < nv; k++)
        for (int i = 0; i < nv; i++)
            for (int j = 0; j < nv; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
    
    for (int i = 0; i < nv; i++)
        if (dist[i][i] < 0)
            return 1;
    return 0;
}

//MAIN
int main()
{
    int G[nv][nv] = {
        0,    1, 9999, 9999,
        9999,    0,   -1, 9999,
        9999, 9999,    0,   -1,
        -1, 9999, 9999,    0,
    };
    
    int dist[nv][nv];
    for (int i = 0; i < nv; i++)
        for (int j = 0; j < nv; j++)
            dist[i][j] = G[i][j];
    
    (floydWarshall(G, dist)) ? cout << "Negative cycle found!\n" : cout << "Not found :(\n";
    
}
