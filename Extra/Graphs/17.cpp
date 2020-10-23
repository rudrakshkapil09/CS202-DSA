//Winning vertices
#include <iostream>
using namespace std;
const int nv = 5;

//special functions
int counter = 0;
void DFS(int G[][nv], int current, int visited[])
{
    visited[current] = 1;
    counter++;
    for (int i = 0; i < nv; i++)
        if (G[current][i] && !visited[i])
            DFS(G, i, visited);
}

void checkAll(int G[][nv])
{
    int flag = 0;
    for (int i = 0; i < nv; i++) {
        int visited[nv];
        memset(visited, 0, sizeof(visited));
        counter = 0;
        DFS(G, i, visited);
        
        if (counter % 2) {
            flag = 1;
            cout << i << " is a winning vertex!\n";
        }
    }
    if (!flag)
        cout << "No winning vertices :(\n";
}


//MAIN
int main()
{
    int G[nv][nv] = {
        0, 1, 1, 1, 1,
        1, 0, 1, 1, 1,
        1, 1, 0, 1, 1,
        1, 1, 1, 0, 1,
        1, 1, 1, 1, 0,
    };
    checkAll(G);
}

