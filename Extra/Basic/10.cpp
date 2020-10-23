//Sudoku solver
#include <iostream>
using namespace std;
const int N = 9;

//special functions
void printMatrix(int G[][N], int i, int j, int flag)
{
    if (i < N) {
        if (i % 3 == 0 && !flag) {
            flag = 1;
            cout << "+–––––––+–––––––+–––––––+\n";
        }
        if (j % 3 == 0) cout << "| ";
        if (j < N) {
            (G[i][j] > 0) ? cout << G[i][j] << " " : cout << "  ";
            printMatrix(G, i, j+1, 1);
        }
        else {
            cout << "\n";
            printMatrix(G, i+1, 0, 0);
        }
    }
    else cout << "+–––––––+–––––––+–––––––+\n";
}

int isSafe(int G[][N], int x, int y, int num)
{
    for (int i = 0; i < N; i++)     //check col
        if (G[i][y] == num)
            return 0;
    for (int i = 0; i < N; i++)     //check row
        if (G[x][i] == num)
            return 0;
    
    pair<int, int> boxstart;
    if (x < 3)
        boxstart.first = 0;
    else if (x >= 3 && x < 6)
        boxstart.first = 3;
    else boxstart.first = 6;
    
    if (y < 3)
        boxstart.second = 0;
    else if (y >= 3 && y < 6)
        boxstart.second = 3;
    else boxstart.second = 6;
    
    for (int i = boxstart.first; i < boxstart.first + 3; i++)
        for (int j = boxstart.second; j < boxstart.second + 3; j++)
            if (G[i][j] == num)
                return 0;
    
    return 1;
}

int countZeros(int G[][N])
{
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (!G[i][j])
                count++;
    return count;
}

pair<int, int> findNext(int G[][N], int i, int j)
{
    for (; j < N; j++)
        if (!G[i][j])
            return {i, j};
    if (i != N-1)
        return findNext(G, i+1, 0);
    else return {-1, -1};
}

int solvePuzzle(int G[][N], int i, int j, int n, int count)
{
    if (count == n) {
        cout << "Solved! :)\n";
        printMatrix(G, 0, 0, 0);
        return 1;
    }
    else {
        pair<int, int> next = findNext(G, i, j);
        i = next.first;
        j = next.second;
        for (int num = 1; num <= 9; num++) {
            if (isSafe(G, i, j, num)) {
                G[i][j] = num;
                if (solvePuzzle(G, next.first, next.second, n, count+1))
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
    int grid[N][N] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    
    int n = countZeros(grid);
    solvePuzzle(grid, 0, 0, n, 0);
}
