//Detecting a cycle in an undirected graph using Disjoint Sets
#include <iostream>
#include <vector>
using namespace std;
const int nv = 5;

//structs
struct edge {
    int u;
    int v;
};

//disjoint set functions
int find(int S[], int i)
{
    if (S[i] == -1)
        return i;
    else return find(S, S[i]);
}

void doUnion(int S[], int i, int j)
{
    int posx = find(S, i);
    int posy = find(S, j);
    if (posx != posy)
        S[posy] = posx;
}

//graph functions
void printMatrix(int G[][nv], int i, int j)
{
    if (i < nv) {
        if (!i && !j) {
            cout << "  |";
            for (char k = 'A'; k < 'A' + nv; k++)
                cout << k << " ";
            cout << "\n--+---------";
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
            if (ch == '0') break;
            else G[i][ch-65] = 1;
        }
        inputMatrix(G, i+1, input, inputindex);
    }
}

//special functions
void getEdges(int G[][nv], vector<edge> &edges)
{
    for (int i = 0; i < nv; i++) {
        for (int j = 0; j < nv; j++) {
            if (G[i][j] == 1) {
                G[j][i] = 2;
                edge e;
                e.u = i; e.v = j;
                edges.push_back(e);
            }
        }
    }
}

int checkCyle(vector<edge> edges)
{
    int S[nv];
    for (int i = 0; i < nv; i++)
        S[i] = -1;
    
    int i = 0;
    while (i < edges.size()) {
        edge e = edges[i++];
        
        if (find(S, e.u) == find(S, e.v))
            return 1;
        else doUnion(S, e.u, e.v);
    }
    return 0;
}

//MAIN
int G[nv][nv];
int main()
{
    vector<edge> edges;
    string input_UG = "B0C0D0E00";
    
    inputMatrix(G, 0, input_UG, 0);
    printMatrix(G, 0, 0);
    getEdges(G, edges);
    
    (checkCyle(edges)) ? cout << "\nCycle found.\n" : cout << "\nNo cycle present.\n";
    return 0;
}
