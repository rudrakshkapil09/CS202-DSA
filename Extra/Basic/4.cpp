//Knight's tour problem
#include <iostream>
#include <iomanip>
using namespace std;
const int nv = 7;

int Board[nv][nv];

//special functions
void printMatrix(int G[][nv], int i, int j)
{
    if (i < nv) {
        if (!i && !j) {
            cout << "  |" << setw(3);
            for (char k = '1'; k < '1' + nv; k++)
                cout << k << "   ";
            cout << "\n––+–––––––––––––––––––––––––––––––";
        }
        
        if (j < nv) {
            if (!j) cout << "\n" << char(i + '1') << " |" << setw(3);
            (G[i][j] > 0) ? cout << G[i][j] << setw(4) : cout << "" << setw(4) ;
            printMatrix(G, i, j+1);
        }
        else printMatrix(G, i+1, 0);
    }
    else cout << "\n";
}

int findNext(int G[][nv], int &i, int &j, int skip)
{
    int xMoves[8] = {2, 1, -1, -2, -2, -1,  1,  2};
    int yMoves[8] = {1, 2,  2,  1, -1, -2, -2, -1};
    
    for (int k = 0; k < nv; k++) {
        int x = xMoves[k];
        int y = yMoves[k];
        if (i+x < 0 || i+x >= nv || j+y < 0 || j+y >= nv) continue;
        
        if (!G[i+x][j+y] && !skip) {
            i += x;
            j += y;
            return 1;
        }
        else if (!G[i+x][j+y]) skip--;
    }
    return 0;
}

int knightsTour(int G[][nv], int i, int j, int moves)
{
    if (moves > nv*nv) {
        cout << "Solution found!\n";
        printMatrix(G, 0, 0);
        return 1;
    }
    else {
        int skip = 0;
        int oldx = i, oldy = j;
        while (findNext(G, i, j, skip)) {
            G[i][j] = moves;
            if (knightsTour(G, i, j, moves+1))
                return 1;
            G[i][j] = 0;
            i = oldx;
            j = oldy;
            skip++;
        }
    }
    return 0;
}

//MAIN
int main()
{
    Board[0][0] = 1;
    if (!knightsTour(Board, 0, 0, 2))
        cout << "No tour :(\n";
    return 0;
}
