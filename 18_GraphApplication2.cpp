//Euler's path
#include <iostream>
using namespace std;
const int nv = 6;

//struct defintions
int G[nv][nv];
typedef
struct lnode {
    char key;
    struct lnode *next;
} *LPTR;

//linked list functions
int rcount(LPTR L)
{
    if (L == NULL)
        return 0;
    else return 1 + rcount(L->next);
}

void rprint(LPTR L)
{
    if (L != NULL) {
        if (L->next != NULL) cout << L->key << "->";
        else cout << L->key << endl;
        rprint(L->next);
    }
}

void addToEnd(LPTR &L, char x)
{
    LPTR T = new(lnode);
    LPTR T2 = L;
    T->key = x;
    T->next = NULL;
    if (L == NULL)
        L = T;
    else {
        while (T2->next != NULL)
            T2 = T2->next;
        T2->next = T;
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
            else G[i][ch-65] = 1;
        }
        inputMatrix(G, i+1, input, inputindex);
    }
}

//Euler's path
int vertexOutDegree(int G[][nv], int i, char v)
{
    if (i < nv)
        return G[v-65][i] + vertexOutDegree(G, i+1, v);
    else return 0;
}

void storeDegrees(int G[][nv], int degrees[])
{
    for (int i = 'A'; i < nv+65; i++)
        degrees[i-65] = vertexOutDegree(G, 0, i);
}

int notDone(int degrees[])
{
    for (int i = 0; i < nv; i++)
        if (degrees[i] > 0) return i;
    return -1;
}

char nextVertex(int degrees[], LPTR L, int i)
{
    if (degrees[L->key-65] > 0)
        return L->key;
    else return nextVertex(degrees, L->next, 0);
}

void splice(LPTR F, LPTR S)
{
    LPTR S2 = S;
    while (S->next)
        S = S->next;
    while (F->key != S->key)
        F = F->next;
    S->next= F->next;
    F->next = S2->next;
}

void storePath(int G[][nv], LPTR &L, int i, int j, char start, int degrees[])
{
    if (degrees[i] > 0) {
        if (G[i][j]) {
            G[i][j] = G[j][i] = 0;
            degrees[i]--; degrees[j]--;
            addToEnd(L, char(i+65));
            if (j+65 == start && degrees[j] == 0)
                addToEnd(L, char(j+65));
            storePath(G, L, j, 0, start, degrees);
        }
        else storePath(G, L, i, j+1, start, degrees);
    }
    else if (notDone(degrees) != -1) {
        char next = nextVertex(degrees, L, 0);
        LPTR L2 = NULL;
        storePath(G, L2, next-65, 0, next, degrees);
        splice(L, L2);
    }
}

//MAIN
int main()
{
    string input_complex = "CD,CH,ABDFGI,ACEGJK,DJ,CI,CDIJ,BI,CFGHJL,DEGIKL,DJ,IJ,";
    string input_easy = "BDEF,ACDE,BD,ABCE,ABDF,AE,";
    LPTR L = NULL;
    int degrees[nv] = {0};
    
    inputMatrix(G, 0, input_easy, 0);
    storeDegrees(G, degrees);
    
    cout << "Graph:\n";
    printMatrix(G, 0, 0);
    
    cout << "\nEuler's Path:\n";
    storePath(G, L, 'B'-65, 0, 'B', degrees);
    rprint(L);
    cout << "Edges => " << rcount(L)-1 << endl;
    return 0;
}



