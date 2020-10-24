//0/1 shortest path problem
#include <iostream>
using namespace std;
const int nv = 9;

//structs
int G[nv][nv];

typedef
struct dnode {
    struct dnode *left;
    int data;
    struct dnode *right;
} *DPTR;

struct DQ {
    DPTR fl;
    DPTR fr;
};

//DQ functions
void enqueueLeft(DQ &Q, int x) {
    if (!Q.fl) {
        DPTR D = new (dnode);
        D->data = x;
        D->left = D->right = NULL;
        Q.fl = Q.fr = D;
    }
    else {
        DPTR D = new (dnode);
        D->data = x;
        D->right = Q.fl;
        D->left = NULL;
        Q.fl->left = D;
        Q.fl = Q.fl->left;
    }
}

void enqueueRight(DQ &Q, int x) {
    if (!Q.fr) {
        DPTR D = new (dnode);
        D->data = x;
        D->left = D->right = NULL;
        Q.fl = Q.fr = D;
    }
    else {
        DPTR D = new (dnode);
        D->data = x;
        D->left = Q.fr;
        D->right = NULL;
        Q.fr->right = D;
        Q.fr = Q.fr->right;
    }
}

int dequeueLeft(DQ &Q) {
    if (!Q.fl) {
        cout << "Queue empty.\n";
        return -1;
    }
    else {
        int t = Q.fl->data;
        Q.fl = Q.fl->right;
        if (Q.fl)
            Q.fl->left = NULL;
        return t;
    }
}

int dequeueRight(DQ &Q) {
    if (!Q.fr) {
        cout << "Queue empty.\n";
        return -1;
    }
    else {
        int t = Q.fr->data;
        Q.fr = Q.fr->left;
        if (Q.fr) Q.fr->right = NULL;
        return t;
    }
}

int isEmpty(DQ Q)
{
    if (!Q.fl)
        return 1;
    else return 0;
}

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
            else G[i][ch-'0'] = input[inputindex++]-'0';
        }
        inputMatrix(G, i+1, input, inputindex);
    }
}

//special functions
void printPath(int prev[], int goal, int last)
{
    if (goal != -1) {
        printPath(prev, prev[goal], last);
        (goal != last) ? cout << goal << "->" : cout << goal << endl;
    }
}

void printOutput(int G[][nv], int start)
{
    DQ Q;
    Q.fl = Q.fr = NULL;
    int dist[nv], prev[nv];
    for (int i = 0; i < nv; i++) {
        dist[i] = 999;
        prev[i] = -1;
    }
    
    dist[start] = 0;
    enqueueLeft(Q, start);
    while (!isEmpty(Q)) {
        int current = dequeueLeft(Q);
        for (int i = 0; i < nv; i++)
            if (G[current][i] && (dist[i] > dist[current] + G[current][i])) {
                dist[i] = dist[current] + G[current][i] -1;
                prev[i] = current;
                if (G[current][i] == 1)
                    enqueueLeft(Q, i);
                else enqueueRight(Q, i);
                G[current][i] = 0;
            }
    }
    
    cout << "Distances from vertex " << start << ":\n";
    for (int i = 0; i < nv; i++)
        if (start != i)
            cout << i << " -> " << dist[i] << endl;
    cout << "\nShortest Path from 0 to 5:\n";
    printPath(prev, 5, 5);
}


//MAIN
int main()
{
    string input = "1172,012272,12315182,214252,3252,21324262,527282,02128262,226272,";
    inputMatrix(G, 0, input, 0);
    printMatrix(G, 0, 0);
    printOutput(G, 0);
}




