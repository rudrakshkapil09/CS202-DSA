//Find shortest safe route in a path with landmines
#include <iostream>
#include <queue>
using namespace std;
const int ROW = 12, COL = 10;

//struct definition
struct data {
    pair<int, int> pos;
    int dist;
};

//special functions
int xMoves[] = {1, -1, 0, 0};
int yMoves[] = {0, 0, 1, -1};

int isValid(int i, int j) {
    return (i < ROW && j < COL && i >= 0 && j >= 0);
}

int isSafe(int G[][COL], int visited[][COL], int i, int j) {
    return (isValid(i, j) && G[i][j] > 0 && !visited[i][j]);
}

void markUnsafe(int G[][COL])
{
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            if (!G[i][j]) {
                for (int k = 0; k < 4; k++) {
                    int x = i+xMoves[k], y = j+yMoves[k];
                    if (isValid(x, y))
                        G[x][y] = -1;
                }
            }
}

void findShortest(int G[][COL], int visited[][COL], int i, int j, int &minsteps, int steps)
{
    if (j == COL-1 || steps > minsteps) {
        minsteps = min(minsteps, steps);
        return;
    }
    else {
        int x, y;
        visited[i][j] = 1;
        for (int k = 0; k < 4; k++) {
            x = xMoves[k] + i;
            y = yMoves[k] + j;
            if (isSafe(G, visited, x, y))
                findShortest(G, visited, x, y, minsteps, steps+1);
        }
        visited[i][j] = 0;
    }
}

void printOutput(int G[][COL])
{
    int minsteps = 9999;
    int visited[ROW][COL];
    memset(visited, 0, sizeof(visited));
    
    markUnsafe(G);
    for (int i = 0; i < ROW; i++) {
        if (G[i][0] > 0) {
            findShortest(G, visited, i, 0, minsteps, 0);
        }
    }
    
    (minsteps > ROW*COL) ? cout << "No route found :(\n" : cout << "Shortest path => " << minsteps << "\n";
}

//MAIN
int main()
{
    int mat[ROW][COL]  = {
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 0, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 },
        { 1, 0, 1, 1, 1, 1, 1, 1, 0, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 0, 1, 1, 1, 1, 0, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 1, 1, 1 }
    };
    
    printOutput(mat);
    return 0;
}
