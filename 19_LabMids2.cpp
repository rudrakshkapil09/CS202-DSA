//Locating a mother vertex in a graph efficiently
#include <iostream>
using namespace std;

const int nv = 7;
int G[nv][nv];

//special functions
void printMatrix(int G[][nv], int i, int j)
{
    if (i < nv) {
        if (!i && !j) {
            cout << "  |";
            for (int k = 0; k < nv; k++)
                cout << k << " ";
            cout << "\n--+--------------";
        }
        
        if (j < nv) {
            if (!j) cout << "\n" << i << " |";
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
            else G[i][ch-'0'] = 1;
        }
        inputMatrix(G, i+1, input, inputindex);
    }
}

//special functions
void DFS(int G[][nv], int current, int visited[])
{
    visited[current] = 1;
    for (int i = 0; i < nv; i++)
        if (G[current][i] && !visited[i])
            DFS(G, i, visited);
}

int findMother(int G[][nv])
{
    int v = 0, visited[nv] = {0};
    for (int i = 0; i < nv; i++)
        if (!visited[i]) {
            DFS(G, i, visited);
            v = i;
        }
    
    memset(visited, 0, sizeof(visited));
    DFS(G, v, visited);
    for (int i = 0; i < nv; i++)
        if (!visited[i])
            return -1;
    return v;
}

//MAIN
int main()
{
    string input = "12,3,,,1,26,04,";
    inputMatrix(G, 0, input, 0);
    printMatrix(G, 0, 0);
    cout << "\nMother vertex => " << findMother(G) << endl;
}




