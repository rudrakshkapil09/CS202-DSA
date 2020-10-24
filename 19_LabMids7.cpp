//Max flow problem
#include <iostream>
using namespace std;
const int nv = 6;

//singly linked list as a queue definitions
int G[nv][nv];
typedef
struct lnode {
    int data;
    struct lnode *next;
} *LPTR;

struct LQueue {
    LPTR f;
    LPTR r;
};

//LQueue functions
void LaddAfter(LPTR &L, int B)
{
    LPTR T = new(lnode);
    T->data = B;
    if (L == NULL) L = T;
    else {
        L->next = T;
        L = T;
    }
}

void Lenqueue(LQueue &LQ, int B)
{
    int was_empty = 0;
    if (LQ.r == NULL) was_empty = 1;
    LaddAfter(LQ.r, B);
    if (was_empty) LQ.f = LQ.r;
}

int LqueueIsEmpty(LQueue LQ)
{
    if (LQ.f == NULL)
        return 1;
    else return 0;
}

int LdeleteFirst(LPTR &L)
{
    int B = L->data;
    L = L->next;
    return B;
}

int Ldequeue(LQueue &LQ)
{
    if (LqueueIsEmpty(LQ)) {
        cout << "Queue empty.";
        return NULL;
    }
    else {
        int is_one_element = 0;
        if (LQ.f == LQ.r)
            is_one_element = 1;
        int B = LdeleteFirst(LQ.f);
        if (is_one_element) LQ.f = LQ.r = NULL;
        return B;
    }
}

//special functions
void printMatrix(int G[][nv], int i, int j)
{
    if (i < nv) {
        if (!i && !j) {
            cout << "  |";
            for (char k = '0'; k < '0' + nv; k++)
                cout << k << " ";
            cout << "\n--+---------";
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

void inputMatrix(int G[][nv], int i, int input[], int inputindex)
{
    if (i < nv) {
        while (1) {
            int ch = input[inputindex++];
            if (ch == -1) break;
            else G[i][ch] = input[inputindex++];
        }
        inputMatrix(G, i+1, input, inputindex);
    }
}

//special functions
int BFS(int R[][nv], int start, int end, int prev[])
{
    LQueue Q;
    Q.f = Q.r = NULL;
    int visited[nv];
    memset(visited, 0, sizeof(visited));
    
    Lenqueue(Q, start);
    visited[start] = 1;
    
    while (!LqueueIsEmpty(Q)) {
        int current = Ldequeue(Q);
        for (int i = 0; i < nv; i++)
            if (R[current][i] && !visited[i]) {
                Lenqueue(Q, i);
                prev[i] = current;
                visited[i] = 1;
            }
    }
    
    return visited[end];
}

int getMaxFlow(int G[][nv], int start, int end)
{
    int prev[nv], max_flow = 0;
    memset(prev, -1, sizeof(prev));
    
    while (BFS(G, start, end, prev)) {
        int path_flow = 999;
        for (int j = end; j != start; j = prev[j]) {
            int i = prev[j];
            path_flow = (path_flow < G[i][j]) ? path_flow : G[i][j];
        }
        for (int j = end; j != start; j = prev[j]) {
            int i = prev[j];
            G[i][j] -= path_flow;
            G[j][i] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}

//MAIN
int main()
{
    int input[] = {1, 16, 2, 13, -1, 2, 10, 3, 12, -1, 1, 4, 4, 14, -1, 2, 9, 5, 20, -1, 3, 7, 5, 4, -1, -1};
    inputMatrix(G, 0, input, 0);
    printMatrix(G, 0, 0);
    
    cout << "\nMax flow to vertex 5 => " << getMaxFlow(G, 0, 5) << endl;
    
    
}
