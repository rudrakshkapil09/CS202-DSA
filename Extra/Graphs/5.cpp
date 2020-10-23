//Finding number of islands
#include <iostream>
using namespace std;
const int nv = 5;

//special functions
int isSafe(int G[][nv], int visited[][nv], int row, int col)
{
    return ((row < nv) && (col < nv) && (row >= 0) && (col >= 0) && !visited[row][col] && G[row][col]);
}

void DFS(int G[][nv], int visited[][nv], int row, int col)
{
    int rMoves[] = {-1, -1, -1, 0,  0, 1, 1,  1};
    int cMoves[] = { 1,  0, -1, 1, -1, 1, 0, -1};
    
    visited[row][col] = 1;
    for (int i = 0; i < 8; i++)
        if (isSafe(G, visited, row + rMoves[i], col + cMoves[i]))
            DFS(G, visited, row+rMoves[i], col+cMoves[i]);
}

int getIslands(int G[][nv])
{
    int visited[nv][nv];
    memset(visited, 0, sizeof(visited));
    
    int count = 0;
    for (int i = 0; i < nv; i++)
        for (int j = 0; j < nv; j++)
            if (G[i][j] && !visited[i][j]) {
                DFS(G, visited, i, j);
                count++;
            }
    return count;
}

//MAIN
int main()
{
    int G[nv][nv] = {
        {1, 1, 0, 0, 0},
        {0, 1, 0, 0, 1},
        {1, 0, 0, 1, 1},
        {0, 0, 0, 0, 0},
        {1, 0, 1, 0, 1}
    };
    
    cout << "Number of islands => " << getIslands(G) << "\n";
    
}
