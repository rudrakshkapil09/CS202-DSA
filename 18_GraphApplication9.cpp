  //Strongly connected components -> single DFS
#include <iostream>
using namespace std;
const int nv = 10;

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
int num[nv], low[nv], visited[nv], num_count = 0;
void arc(int G[][nv], int v, int prev)
{
    visited[v] = 1;
    low[v] = num[v] = num_count++;
    
    for (int w = 0; w < nv; w++) {
        if (!G[v][w] || w == prev) continue;    //no edge
        
        if (visited[w])                         //back edge
            low[v] = min(low[v], num[w]);
        else {                                  //tree edge
            arc(G, w, v);
            low[v] = min(low[v], low[w]);
            
            if (low[w] >= num[v]) {
                cout << char(v+65) << " ";
                for (int i = num[v]+1; i < nv; i++)
                    if (low[i] == num[v])
                        cout << char(i+65) << " ";
                cout << endl;
            }
        }
    }
}

//MAIN
int main()
{
    cout << "Graph:\n";
    string input = "BCD,AC,ABDEG,AC,CFG,EGHIJ,CEF,FI,FHJ,FI,";
    inputMatrix(G, 0, input, 0);
    printMatrix(G, 0, 0);
    
    cout << "\nStrongly Connected Components:\n";
    arc(G, 0, 0);
    return 0;
}


