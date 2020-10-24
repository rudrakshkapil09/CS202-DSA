//Minimum spanning tree - Krushkal's algorith (reversed)
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
            if (edges[i][0] < edges[i+1][0])
                swap(edges[i], edges[i+1]);
        sortEdges(edges, n-1);
    }
}

void editUnion(int G[][nv], int S[], int actual, int first, int flag, int visited[], int flag2)
{
    if (visited[first] == 1 && !flag2) return;
    else visited[first] = 1;
    
    if (flag) {
        S[first] = -1;
        editUnion(G, S, actual, first, 0, visited, 1);
    }
    else {
        for (int j = 0; j < nv; j++)
            if (G[first][j] && j != actual) {
                S[j] = actual;
                editUnion(G, S, actual, j, 0, visited, 0);
            }
    }
}

int minSpanningTree(int G[][nv], int S[], int edges[][3], int n)
{
    int index = 0, cost = 0, org_n = n;
    
    while (n > nv-1) {
        int visited[nv];
        int prev = edges[index][1], next = edges[index][2];
        memset(visited, 0, sizeof(visited));
        
        G[prev][next] = G[next][prev] = 0;
        editUnion(G, S, next, next, 1, visited, 1);
        
        if (find(S, prev) != find(S, next)) {
            doUnion(S, prev, next);
            G[prev][next] = G[next][prev] = edges[index][0];
            cost += edges[index][0];
        }
        else n--;
        printMatrix(G, 0, 0);
        index++;
    }
    for (; index < org_n; index++)
        cost += edges[index][0];
    
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
    memset(S, 0, sizeof(S));
    S[0] = -1;
    cout << "Graph:\n";
    printMatrix(G, 0, 0);
    
    int edges[(nv*(nv-1))/2][3];
    memset(edges, 0, sizeof(edges));
    int n = storeEdges(G, edges);
    sortEdges(edges, n);
    
    cout << "\nMinimum spanning tree:\n";
    inputMatrix(G, 0, input, 0);
    int cost = minSpanningTree(G, S, edges, n);
    cout << "Cost => " << cost << endl;
    
}

