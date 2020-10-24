/*Disjoint Sets*/
//Minimum spanning tree - Krushkal's algorithm
#include <iostream>
using namespace std;
const int nv = 7;

//structs
int G[nv][nv], T[nv][nv], S[nv];

//disjoint set functions
int find(int S[], int i)
{
    if (S[i] == -1)
        return i;
    else return find(S, S[i]);
}

void doUnion(int S[], int first, int second)
{
    int pos_f = find(S, first), pos_s = find(S, second);
    if (pos_f != pos_s)
        S[pos_s] = pos_f;
}

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

//Spanning tree functions
int storeEdges(int G[][nv], int edges[][3])    //0->cost || 1->prev || 2->next
{
    int index = 0, count = 0;
    for (int i = 0; i < nv; i++)
        for (int j = 0; j < nv; j++)
            if (G[i][j]) {
                edges[index][0] = G[i][j];
                edges[index][1] = i;
                edges[index++][2] = j;
                G[j][i] = 0;
                count++;
            }
    return count;
}

void sortEdges(int edges[][3], int n)
{
    if (n > 1) {
        for (int i = 0; i < n-1; i++)
            if (edges[i][0] > edges[i+1][0])
                swap(edges[i], edges[i+1]);
        sortEdges(edges, n-1);
    }
}

int minSpanningTree(int T[][nv], int S[], int edges[][3])
{
    int count = 0, index = 0, cost = 0;
    while (count < nv-1) {
        int prev = edges[index][1], next = edges[index][2];
        if (find(S, prev) != find(S, next)) {
            doUnion(S, next, prev);
            T[prev][next] = edges[index][0];
            cost += edges[index][0];
            count++;
        }
        index++;
    }
    return cost;
}

void print(int S[])
{
    for (int i = 0; i < nv; i++)
        cout << char(i+65) << "->" << S[i] << "  ";
}

//MAIN
int main()
{
    string input = "B2C4D1,A2D3E9,A4D2F5,A1B3C2E7F8G4,B9D7G6,C5D8G1,D4E6F1,"; //"B2D1,D3E9,A4F5,C2E2F8G4,G6,,F1,"
    inputMatrix(G, 0, input, 0);
    G[1][4] = G[4][1] = 10;
    memset(S, -1, sizeof(S));
    cout << "Graph:\n";
    printMatrix(G, 0, 0);
    
    int edges[(nv*(nv-1))/2][3];
    memset(edges, 0, sizeof(edges));
    int n = storeEdges(G, edges);
    sortEdges(edges, n);
    
    cout << "\nMinimum spanning tree:\n";
    int cost = minSpanningTree(T, S, edges);
    printMatrix(T, 0, 0);
    cout << "Cost => " << cost << endl;
    
}

