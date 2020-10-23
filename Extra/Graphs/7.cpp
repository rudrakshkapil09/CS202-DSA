//Shortest path in a Binary Maze
#include <iostream>
#include <queue>
using namespace std;
const int ROW = 9, COL = 10;

//struct definition
struct data {
    pair<int, int> pos;
    int dist;
};

//special functions
int isSafe(int i, int j, int visited[ROW][COL], int G[ROW][COL])
{
    return ((i < ROW) && (i >= 0) && (j < COL) && (j >= 0) && (!visited[i][j]) && (G[i][j]));
}

int BFS(pair<int, int> start, pair<int, int> solution, int G[ROW][COL])
{
    int i, j, dist;
    int xMoves[] = {1, -1, 0, 0};
    int yMoves[] = {0, 0, 1, -1};
    
    int visited[ROW][COL];
    memset(visited, 0, sizeof(visited));
    visited[start.first][start.second] = 1;
    
    queue<data> Q;
    Q.push({start, 0});
    struct data d;
    
    while (!Q.empty()) {
        if (Q.front().pos == solution)
            return Q.front().dist;
        
        dist = Q.front().dist;
        i = Q.front().pos.first;
        j = Q.front().pos.second;
        Q.pop();
        for (int k = 0; k < 4; k++) {
            int x = xMoves[k] + i;
            int y = yMoves[k] + j;
            if (isSafe(x, y, visited, G)) {
                visited[x][y] = 1;
                d.pos.first = x;
                d.pos.second = y;
                d.dist = dist+1;
                Q.push(d);
            }
        }
    }
    return 0;
}

//MAIN
int main()
{
    int mat[ROW][COL]  = {
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
        {1, 0, 1, 0, 1, 1, 1, 0, 1, 1 },
        {1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
        {1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
        {1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
        {1, 1, 0, 0, 0, 0, 1, 0, 0, 1 }
    };
    
    cout << "Minimum number of steps => " << BFS({0,0}, {8, 1}, mat) << "\n";
}
