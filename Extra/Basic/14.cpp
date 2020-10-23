//Minimum queens required to cover all the squares of a chess board
#include <iostream>
#include <vector>
using namespace std;
const int M = 8;
const int N = 8;

//printing
void printMatrix(char G[][N], int i, int j)
{
    if (i < M) {
        if (!i && !j) {
            cout << "  |";
            for (char k = 'A'; k < 'A' + N; k++)
                cout << k << " ";
            cout << "\n--+---------";
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

//special functions
pair<int, int> findNext(char G[][N])
{
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++) {
            if (G[i][j] == '0')
                return {i, j};
        }
    return {-1, -1};
}

void markUnsafe(char G[][N], int i, int j, int &count)
{
    G[i][j] = 'Q';
    count++;
    for (int a = 0; a < M; a++) {
        if (a != j)
            G[i][a] = 'X';
        if (a != i)
            G[a][j] = 'X';
    }
    
    int orgi = i, orgj = j;
    for (i += 1, j += 1; i < M && j < N; i++, j++)
        G[i][j] = 'X';
    i = orgi; j = orgj;
    for (i += 1, j -= 1; i < M && j >= 0; i++, j--)
        G[i][j] = 'X';
    i = orgi; j = orgj;
    for (i -= 1, j -= 1; i >= 0 && j >= 0; i--, j--)
        G[i][j] = 'X';
    i = orgi; j = orgj;
    for (i -= 1, j += 1; i >= 0 && j < N; i--, j++)
        G[i][j] = 'X';
    i = orgi; j = orgj;
}

int placeQueens(char G[][N])
{
    int count = 0;
    while (1) {
        pair<int, int> next = findNext(G);
        if (next.first == -1)
            return count;
        markUnsafe(G, next.first, next.second, count);
    }
    return count;
}

//MAIN
int main()
{
    char board[M][N];
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = '0';
    
    int queens = placeQueens(board);
    printMatrix(board, 0, 0);
    cout << "\nNumber of queens required => " << queens << ".\n";
}
