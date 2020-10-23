//Minimum steps to reach target by a Knight | Set 1
#include <iostream>
#include <queue>
using namespace std;
const int nv = 31;

//struct definition
struct data {
    pair<int, int> pos;
    int dist;
};

//special functions
int isSafe(int i, int j, int visited[][nv])
{
    return ((i < nv) && (i >= 0) && (j < nv) && (j >= 0) && (!visited[i][j]));
}

int BFS(pair<int, int> start, pair<int, int> solution)
{
    int i, j, dist;
    int xMoves[] = {2, 2, -2, -2, 1, 1, -1, -1};
    int yMoves[] = {1 ,-1, 1, -1, 2,-2,  2, -2};
    
    int visited[nv][nv];
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
        for (int k = 0; k < 8; k++) {
            int x = xMoves[k] + i;
            int y = yMoves[k] + j;
            if (isSafe(x, y, visited)) {
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
    cout << "Minimum number of steps => " << BFS({1,1}, {30, 30}) << "\n";
}

