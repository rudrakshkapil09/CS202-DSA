//N Queen Problem
#include <iostream>
using namespace std;
const int N = 8;

//Special Functions
void printMatrix(int G[][N], int i, int j)
{
    if (i < N) {
        if (!i && !j) {
            cout << "  |";
            for (char k = 'A'; k < 'A' + N; k++)
                cout << k << " ";
            cout << "\n--+----------------";
        }
        
        if (j < N) {
            if (!j) cout << "\n" << char(i+65) << " |";
            (G[i][j] > 0) ? cout << G[i][j] << " " : cout << "  ";
            printMatrix(G, i, j+1);
        }
        else printMatrix(G, i+1, 0);
    }
    else cout << "\n";
}

int isSafe(int G[][N], int row, int col)
{
    for (int j = 0; j < col; j++)
        if (G[row][j])
            return 0;
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (G[i][j])
            return 0;
    
    for (int i = row, j = col; i < N && j >= 0; i++, j--)
        if (G[i][j])
            return 0;
    return 1;
}

int isPlaced(int G[][N], int i, int j)
{
    if (j == N) {
        cout << "Solution found!\n";
        printMatrix(G, 0, 0);
        return 1;
    }
    else {
        for (; i < N; i++) {
            if (isSafe(G, i, j)) {
                G[i][j] = 1;
                if (isPlaced(G, 0, j+1))
                    return 1;
                G[i][j] = 0;
            }
        }
        return 0;
    }
}

//MAIN
int main()
{
    int board[N][N] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    
    if (!isPlaced(board, 0, 0)) cout << "No solution\n";
}
