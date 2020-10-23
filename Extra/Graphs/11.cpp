//Gold Mine Problem
#include <iostream>
#include <vector>
using namespace std;
const int M = 4;
const int N = 4;

//special functions
int yMoves[] = {1, 1,  1};
int xMoves[] = {1, 0, -1};

int isValid(int x, int y)
{
    return (x >= 0 && x < M && y >= 0 && y < N);
}

int mineGold(int G[][N], int i, int j, int maxgold, int max_gold, vector<pair<int, int>> &path)
{
    if (j == N-1)
        return maxgold + G[i][j];
    else {
        for (int k = 0; k < 3; k++) {
            int x = i + xMoves[k];
            int y = j + yMoves[k];
            if (isValid(x, y)) {
                if (path.size() < N-1) path.push_back({i, j});
                int oldmaxgold = max_gold;
                max_gold = max(mineGold(G, x, y, maxgold+G[i][j], max_gold, path), max_gold);
                if (oldmaxgold != max_gold && path.size() == N-1)
                    path.push_back({x, y});
            }
        }
        return max_gold;
    }
}

void checkAll(int G[][N])
{
    int maxgold = 0;
    vector<pair<int, int>> path, maxpath;
    for (int i = 0; i < M; i++) {
        path.resize(0);
        int maxfromi = mineGold(G, i, 0, 0, 0, path);
        if (maxfromi > maxgold) {
            maxpath = path;
            maxgold = maxfromi;
        }
    }
    
    cout << "Maximum possible => " << maxgold << "\n";
    for (int i = 0; i < maxpath.size(); i++) {
        cout << "(" << maxpath[i].first << ", " << maxpath[i].second << ")";
        (i < maxpath.size() - 1) ? cout << " -> " : cout << "\n";
    }
}

//MAIN
int main()
{
    int mat[M][N] = {
        {10, 33, 13, 15},
        {22, 21, 04, 1},
        {5, 0, 2, 3},
        {0, 6, 14, 2}
    };
    /*
     int mat[M][N]= { {1, 3, 1, 5},
     {2, 2, 4, 1},
     {5, 0, 2, 3},
     {0, 6, 1, 2}
     };
     */
    /*
     int mat[M][N] = {{1, 3, 3},
     {2, 1, 4},
     {0, 6, 4}}
     ;*/
    
    checkAll(mat);
}
