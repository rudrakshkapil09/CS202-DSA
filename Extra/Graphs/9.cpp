//Shortest distance from a guard in a bank
#include <iostream>
#include <queue>
#include <iomanip>
using namespace std;
const int M = 5;
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

//struct defintion
struct node {
    int x, y, dist;
};

//special functions
void enQueueGuards(char data[M][N], queue<node> &Q, int output[M][N])
{
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++) {
            if (data[i][j] == 'G') {
                Q.push({i, j, 0});
                output[i][j] = 0;
            }
            else output[i][j] = -1;
        }
}

int isSafe(char data[M][N], int output[M][N], int x, int y) {
    return (x >= 0 && x < M && y >= 0 && y < N && data[x][y] == 'O' && output[x][y] == -1);
}

void printOutput(char data[M][N])
{
    int xMoves[] = {1, -1, 0, 0};
    int yMoves[] = {0, 0, 1, -1};
    
    int output[M][N], x, y, i, j, dist;
    queue<node> Q;
    enQueueGuards(data, Q, output); //also sets initial output values
    
    while (!Q.empty()) {
        i = Q.front().x;
        j = Q.front().y;
        dist = Q.front().dist;
        Q.pop();
        for (int k = 0; k < 4; k++) {
            x = i + xMoves[k];
            y = j + yMoves[k];
            if (isSafe(data, output, x, y)) {
                output[x][y] = dist+1;
                Q.push({x, y, dist+1});
            }
        }
    }
    
    cout << "Output:\n";
    printMatrix(output, 0, 0);
}


//MAIN
int main()
{
    char data[M][N] =  {
        {'O', 'O', 'O', 'O', 'G'},
        {'O', 'W', 'W', 'O', 'O'},
        {'O', 'O', 'O', 'W', 'O'},
        {'G', 'W', 'W', 'W', 'O'},
        {'O', 'O', 'O', 'O', 'G'}
    };
    
    printOutput(data);
    return 0;
}
