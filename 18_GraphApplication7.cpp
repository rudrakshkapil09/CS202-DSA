//Dijkstra's shortest path - using BFT
#include <iostream>
using namespace std;
const int nv = 7;

//struct defintion
int G[nv][nv];

//singly linked list as a queue structs
typedef
struct lnode {
    int key;
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
    T->key = B;
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
    int B = L->key;
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

//creation & printing functions
void printMatrix(int G[][nv], int i, int j)
{
    if (i < nv) {
        if (!i && !j) {
            cout << "  |";
            for (char k = 'A'; k < 'A' + nv; k++)
                cout << k << " ";
            cout << "\n––+–––––––––––––––––––––––––";
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

//BFT
void printOutput(char prev[], char goal, char last)
{
    if (goal != '\0') {
        printOutput(prev, prev[goal-65], last);
        (goal != last) ? cout << goal << "->" : cout << goal << endl;
    }
}

void shortestPath(int G[][nv], int current, int goal)
{
    LQueue Q;
    Q.f = Q.r = NULL;
    
    int vist[nv] = {0}, dist[nv] = {999,999,999,999,999,999,999};
    char prev[nv] = {'\0'};
    dist[current] = 0;
    Lenqueue(Q, current);
    
    while (!LqueueIsEmpty(Q)) {
        current = Ldequeue(Q);
        if (current == goal)
            continue;
        else {
            for (int j = 0; j < nv; j++) {
                if (G[current][j] > 0 && vist[j] != 1) {
                    Lenqueue(Q, j);
                    if (G[current][j] + dist[current] < dist[j] && vist[j] == 0) {
                        dist[j] = G[current][j] + dist[current];
                        prev[j] = char(current+65);
                    }
                }
            }
        }
        vist[current] = 1;
    }
    
    printOutput(prev, goal+65, goal+65);
    cout << "Distance => " << dist[goal] << endl;
}


//MAIN
int main()
{
    string input = "B2D1,D3E9,A4F5,C2E2F8G4,G6,,F1,"; //"B2D1,D3E9,A4F5,C2E2F8G4,G6,,F1,"
    inputMatrix(G, 0, input, 0);
    G[1][4] = 10;
    cout << "Graph:\n";
    printMatrix(G, 0, 0);
    
    char goal = 'F', start = 'A';
    cout << "\nShortest Path from " << start << " to " << goal << ":\n";
    shortestPath(G, start-65, goal-65);
}


