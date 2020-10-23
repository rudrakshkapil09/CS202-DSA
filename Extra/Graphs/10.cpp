//Minimum time to rot all oranges
#include <iostream>
#include <queue>
#include <iomanip>
using namespace std;
const int M = 3;
const int N = 5;

//graph functions
void printMatrix(int G[][N], int i, int j)
{
    if (i < M) {
        if (j < N) {
            cout << setw(3) << G[i][j];
            printMatrix(G, i, j+1);
        }
        else {
            cout << "\n";
            printMatrix(G, i+1, 0);
        }
    }
    else cout << "\n";
}


//special functions
int checkAll(int G[][N])
{
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            if (G[i][j] == 1)
                return 1;
    return 0;
}

void enQueueRotten(int data[M][N], queue<pair<int, int>> &Q)
{
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            if (data[i][j] == 2)
                Q.push({i, j});
}

int isSafe(int data[M][N], int x, int y) {
    return (x >= 0 && x < M && y >= 0 && y < N && data[x][y] == 1);
}

int printOutput(int data[M][N])
{
    int xMoves[] = {1, -1, 0, 0};
    int yMoves[] = {0, 0, 1, -1};
    
    int x, y, i, j, days = 0;
    pair<int, int> dummy = {-1, -1};
    queue<pair<int, int>> Q;
    enQueueRotten(data, Q); //also sets initial output values
    Q.push(dummy);
    
    while (!Q.empty()) {
        if (Q.front() == dummy && Q.size() != 1) {
            days++;
            Q.pop();
            Q.push(dummy);
            continue;
        }
        
        i = Q.front().first;
        j = Q.front().second;
        Q.pop();
        for (int k = 0; k < 4; k++) {
            x = i + xMoves[k];
            y = j + yMoves[k];
            if (isSafe(data, x, y)) {
                data[x][y] = 2;
                Q.push({x, y});
            }
        }
    }
    
    return (checkAll(data)) ? -1 : days;
}


//MAIN
int main()
{
    int data[][N] = {
        {2, 1, 0, 2, 1},
        {0, 0, 1, 2, 1},
        {1, 0, 0, 2, 1}
    };
    
    /*
     int data[][N] = {
     {2, 1, 0, 2, 1},
     {1, 0, 1, 2, 1},
     {1, 0, 0, 2, 1}
     }; */
    
    int days = printOutput(data);
    days >= 0 ? cout << "It took " << days << " days to rot all oranges.\n" : cout << "All can not become rotten :)\n";
    return 0;
}
