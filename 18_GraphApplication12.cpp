//Maximum spanning tree - Prim's algorithm
#include <iostream>
using namespace std;
const int nv = 7;

//struct defintions
int G[nv][nv], T[nv][nv];

//creation & printing functions
void printMatrix(int G[][nv], int i, int j)
{
    if (i < nv) {
        if (!i && !j) {
            cout << "  |";
            for (char k = 'A'; k < 'A' + nv; k++)
                cout << k << " ";
            cout << "\n––+––––––––––––––";
        }
        if (j < nv) {
            if (!j) cout << "\n" << char(i+65) << " |";
            (G[i][j] > 0) ? cout << G[i][j] << " " : cout << "  ";
            printMatrix(G, i, j+1);
        }
        else printMatrix(G, i+1, 0);
    }
    else cout << "\n";
}

void inputMatrix(int G[][nv], int i, string input, int inputindex)
{
    if (i < nv) {
        while (1) {
            char ch = input[inputindex++];
            if (ch == ',') break;
            else G[i][ch-65] = input[inputindex++]-'0';
        }
        inputMatrix(G, i+1, input, inputindex);
    }
}

//Special functions
int minSpanningTree(int G[][nv], int T[][nv])
{
    int path[nv] = {0}, visited[nv] = {0};
    int current = 0, count = 1, cost = 0;
    path[0] = current;
    visited[current] = 1;
    
    while (count < nv) {
        int min = 999;
        int next = '\0', prev = '\0';
        for (int i = 0; i < count; i++) {
            for (int j = 0; j < nv; j++) {
                if (G[path[i]][j] && G[path[i]][j] < min && !visited[j]) {
                    min = G[path[i]][j];
                    next = j;
                    prev = path[i];
                }
            }
        }
        path[count++] = next;
        T[prev][next] = T[next][prev] = min*-1;    //remove for directed
        visited[next] = 1;
        cost += min*-1;
    }
    return cost;
}

void negateGraph(int G[][nv])
{
    for (int i = 0; i < nv; i++) {
        for (int j = 0; j < nv; j++) {
            G[i][j] *= -1;
        }
    }
}

//MAIN
int main()
{
    string input = "B2C4D1,A2D3E9,A4D2F5,A1B3C2E7F8G4,B9D7G6,C5D8G1,D4E6F1,"; //"B2D1,D3E9,A4F5,C2E2F8G4,G6,,F1,"
    inputMatrix(G, 0, input, 0);
    G[1][4] = G[4][1] = 10;
    cout << "Graph:\n";
    printMatrix(G, 0, 0);
    
    cout << "\nMaximum spanning tree:\n";
    negateGraph(G);
    int cost = minSpanningTree(G, T);
    printMatrix(T, 0, 0);
    cout << "Cost => " << cost << endl;
    
}
