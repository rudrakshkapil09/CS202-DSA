/*Heaps*/
//Minimum spanning tree - Prim's algorithm
#include <iostream>
using namespace std;
const int nv = 7;

//structs
int G[nv][nv], T[nv][nv];
struct edge {
    int cost = 0;
    int prev = -1;
    int next = -1;
};

//heap functions
void heapify(struct edge edges[], int n)
{
    if (n > 0) {
        if (edges[n].cost < edges[(n-1)/2].cost) {
            swap(edges[n], edges[(n-1)/2]);
            heapify(edges, (n-1)/2);
        }
    }
}

void insertEdge(struct edge edges[], struct edge extra[], int &n, int &e)
{
    int i = 0;
    while (extra[i].cost != 0) {
        edges[n] = extra[i++];
        extra[i-1].cost = 0;
        extra[i-1].next = extra[i-1].prev = -1;
        e--;
        heapify(edges, n++);
    }
}

struct edge heapSort(struct edge edges[], int &n)
{
    struct edge minimum = edges[0];
    edges[0] = edges[n-1];
    edges[n-1].cost = 0;
    edges[n-1].prev = edges[n-1].next = -1;
    
    int i = 0;
    while (edges[i].cost > min(edges[2*i+1].cost, edges[2*i+2].cost) && i < (n-1)/2) {
        int k = (edges[2*i+1].cost < edges[2*i+2].cost) ? 2*i+1 : 2*i+2;
        swap(edges[k], edges[i]);
        i = k;
    }
    n--;
    return minimum;
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
int storeEdges(int G[][nv], struct edge edges[])    //0->cost || 1->prev || 2->next
{
    int index = 0, count = 0;
    for (int i = 0; i < nv; i++)
        for (int j = 0; j < nv; j++)
            if (G[i][j]) {
                edges[index].cost = G[i][j];
                edges[index].prev = i;
                edges[index].next = j;
                heapify(edges, index++);
                G[j][i] = 0;
                count++;
            }
    return count;
}

int isAdjacent(struct edge e, int path[], int visited[], int count)
{
    for (int i = 0; i < count; i++) {
        if (path[i] == e.prev && !visited[e.next])
            return 1;   //add next to path
        if (path[i] == e.next && !visited[e.prev])
            return 2;
    }
    return 0;
    
}

int minSpanningTree(int G[][nv], int T[][nv], struct edge edges[], int n)
{
    struct edge extras[10];
    int path[nv] = {0}, visited[nv] = {0};
    int current = 0, count = 1, cost = 0, flag = 0, e_count = 0;
    path[0] = current;
    visited[current] = 1;
    
    while (count < nv) {
        printMatrix(T, 0, 0);
        struct edge e = heapSort(edges, n);
        int is_adjacent = isAdjacent(e, path, visited, count);
        
        switch (is_adjacent) {
            case 1:
                T[e.prev][e.next] = e.cost;
                visited[e.next] = 1;
                cost += e.cost;
                path[count++] = e.next;
                flag = 1;
                break;
            case 2:
                T[e.prev][e.next] = e.cost;
                visited[e.prev] = 1;
                cost += e.cost;
                path[count++] = e.prev;
                flag = 1;
                break;
            case 0:
                flag = 0;
                extras[e_count++] = e;
                break;
        }
        if (flag && extras[0].cost > 0)
            insertEdge(edges, extras, n, e_count);
    }
    return cost;
}

//MAIN
int main()
{
    string input = "B2C4D1,A2D3E9,A4D2F5,A1B3C2E7F8G4,B9D7G6,C5D8G1,D4E6F1,"; //"B2D1,D3E9,A4F5,C2E2F8G4,G6,,F1,"
    inputMatrix(G, 0, input, 0);
    G[1][4] = G[4][1] = 10;
    cout << "Graph:\n";
    printMatrix(G, 0, 0);
    
    struct edge edges[(nv*(nv-1))/2];
    int n = storeEdges(G, edges);
    
    cout << "\nMinimum spanning tree:\n";
    int cost = minSpanningTree(G, T, edges, n);
    printMatrix(T, 0, 0);
    cout << "Cost => " << cost << endl;
    return 0;
    
}

