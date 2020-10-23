//Shortest path in an unweighted graph
#include <iostream>
#include <queue>
using namespace std;
const int nv = 8;

//special functions
void printPath(int prev[], int i, int goal)
{
    if (i != goal) {
        printPath(prev, prev[i], goal);
        cout << prev[i] << " -> ";
    }
}

void BFS(int G[][nv])
{
    int prev[nv] = {0};
    int dist[nv] = {0};
    for (int i = 0; i < nv; i++) {
        prev[i] = -1;
        dist[i] = 999;
    }
    
    queue<int> Q;
    Q.push(0);
    dist[0] = 0;
    
    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        for (int j = 0; j < nv; j++) {
            if (G[v][j] && dist[v] < dist[j]) {
                dist[j] = dist[v] + 1;
                prev[j] = v;
                Q.push(j);
            }
        }
    }
    
    int goal = 0;
    cout << "Enter goal: ";
    cin >> goal;
    cout << "Minimum distance => " << dist[goal] << "\n";
    cout << "Path => ";
    printPath(prev, goal, 0);
    cout << goal << "\n";
}

//MAIN
int main()
{
    int G[nv][nv] = {
        {0, 1, 0, 1, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 1, 0, 0, 1},
        {0, 0, 0, 1, 0, 1, 1, 1},
        {0, 0, 0, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 1, 0, 1},
        {0, 0, 0, 1, 1, 0, 1, 0}
    };
    
    BFS(G);
    return 0;
}
