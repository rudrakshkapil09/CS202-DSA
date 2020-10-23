//Identify different tree edges in a directed graph
#include <iostream>
using namespace std;
const int nv = 8;

//struct defintions
int G[nv][nv];

//creation functions
void printMatrix(int G[][nv], int i, int j)
{
    if (i < nv) {
        if (!i && !j) {
            cout << "  |";
            for (char k = 'A'; k < 'A' + nv; k++)
                cout << k << " ";
            cout << "\n––+–––––––––––––––––––";
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
            else G[i][ch-65] = 1;
        }
        inputMatrix(G, i+1, input, inputindex);
    }
}

//special functions
int num_count = 0;
int tree = 0, back = 0, cross = 0, fedge = 0;
void arc(int G[][nv], int v, int prev, int num[], int low[], int visited[])
{
    visited[v] = 1;
    low[v] = num[v] = num_count++;
    
    for (int w = 0; w < nv; w++) {
        if (!G[v][w]) continue;    //no edge
        
        if (visited[w]) { //back edge or cross or forward
            low[v] = min(low[v], num[w]);
            if (low[v] > low[w])
                cross++;
            else if (low[v] < low[w])
                fedge++;
            else back++;
        }
        else {                                  //tree edge
            arc(G, w, v, num, low, visited);
            tree++;
            low[v] = min(low[v], low[w]);
        }
    }
}

//MAIN
int main()
{
    cout << "Graph:\n";
    string input = "BEH,C,D,B,F,CGH,,,";
    inputMatrix(G, 0, input, 0);
    printMatrix(G, 0, 0);
    
    cout << "\nArticulation point(s):\n";
    int num[nv] = {0}, low[nv] = {0}, visited[nv] = {0};
    arc(G, 0, 0, num, low, visited);
    
    cout << "tree " << tree << "\nback " << back << "\nforward " << fedge << "\ncross " << cross << "\n" ;
}


