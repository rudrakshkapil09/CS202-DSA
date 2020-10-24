//first application -> printing the courses thing
//Topological sort
#include <iostream>
using namespace std;
const int nv = 7;

//struct defintion
typedef
struct hdnode {
    char key;
    struct hdnode *hdlink;
    typedef
    struct dtnode {
        struct hdnode *key;
        struct dtnode *next;
    } *DTPTR ;
    hdnode::DTPTR dtlink;
} *HDPTR;

//singly linked list as a queue structs
typedef
struct lnode {
    char key;
    struct lnode *next;
} *LPTR;

struct LQueue {
    LPTR f;
    LPTR r;
};

//LQueue functions
void LaddAfter(LPTR &L, char B)
{
    LPTR T = new(lnode);
    T->key = B;
    if (L == NULL) L = T;
    else {
        L->next = T;
        L = T;
    }
}

void Lenqueue(LQueue &LQ, char B)
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

char LdeleteFirst(LPTR &L)
{
    char B = L->key;
    L = L->next;
    return B;
}

char Ldequeue(LQueue &LQ)
{
    if (LqueueIsEmpty(LQ)) {
        cout << "Queue empty.";
        return NULL;
    }
    else {
        int is_one_element = 0;
        if (LQ.f == LQ.r)
            is_one_element = 1;
        char B = LdeleteFirst(LQ.f);
        if (is_one_element) LQ.f = LQ.r = NULL;
        return B;
    }
}

/*creation functions*/
void createHeaders(HDPTR &G, int i)
{
    if (i < nv) {
        if (!G) {
            G = new (hdnode);
            G->hdlink = NULL;
            G->dtlink = NULL;
            G->key = i + 65;
        }
        createHeaders(G->hdlink, i+1);
    }
}

HDPTR findHead(HDPTR G, char ch)
{
    if (G->key == ch) return G;
    else return findHead(G->hdlink, ch);
}

hdnode::DTPTR newNode(HDPTR G)
{
    hdnode::hdnode::DTPTR D = new (hdnode::dtnode);
    D->next = NULL;
    D->key = G;
    return  D;
}

void addData(hdnode::DTPTR &D, HDPTR G)
{
    if (!D)
        D = newNode(G);
    else addData(D->next, G);
}

void inputList(HDPTR orG, HDPTR &G, string input, int i, int inputindex)
{
    if (i < nv) {
        while (1) {
            char ch = input[inputindex++];
            if (ch == '0') break;
            else addData(G->dtlink, findHead(orG, ch));
        }
        inputList(orG, G->hdlink, input, i+1, inputindex);
    }
}

void printLine(hdnode::DTPTR D, int i)
{
    if (!D) return;
    else {
        if (D->key->key-65 == i) {
            cout << "1 ";
            printLine(D->next, i+1);
        }
        else {
            cout << "  ";
            printLine(D, i+1);
        }
    }
}

void printMatrix(HDPTR G, int i, int j, int start_flag)
{
    if (i >= nv || !G) return;
    if (start_flag) {
        cout << "  |";
        for (char k = 'A'; k < nv+65; k++)
            cout << k << " ";
        cout << "\n--+-------------------";
        printMatrix(G, i, j, 0);
    }
    else {
        cout << endl << G->key << " |";
        printLine(G->dtlink, 0);
        printMatrix(G->hdlink, i, 0, 0);
    }
}

int rcountIn(hdnode::DTPTR D, char ch)
{
    if (!D) return 0;
    if (D->key->key == ch) return 1;
    return rcountIn(D->next, ch);
}

int vertexInDegree(HDPTR G, int &deg, int ch) {
    if (G) {
        deg += rcountIn(G->dtlink, ch);
        return vertexInDegree(G->hdlink, deg, ch);
    }
    else return deg;
}

void setIndegrees(HDPTR G, int degrees[])
{
    for (int i = 65; i < nv+65; i++) {
        int deg = 0;
        degrees[i-65] = vertexInDegree(G, deg, i);
    }
}

/*actual function*/
void enqueueAdjacent(HDPTR G, LQueue &Q, int visited[], int degrees[])
{
    for (int i = 0; i < nv; i++) {
        if (degrees[G->key-65] == 0 && visited[G->key-65] == 0)
            Lenqueue(Q, G->key);
        G = G->hdlink;
    }
}

void reduceAdjacent(HDPTR G, int degrees[])
{
    while (G->dtlink) {
        degrees[G->dtlink->key->key-65]--;
        G->dtlink = G->dtlink->next;
    }
}

void printOutput(HDPTR G, LQueue Q, int visited[], int degrees[])
{
    if (!LqueueIsEmpty(Q)) {
        char ch = Ldequeue(Q);
        if (visited[ch-65] == 0) {
            visited[ch-65] = 1;
            cout << ch;
            if (ch-64 < nv) cout << "->";
        }
        enqueueAdjacent(G, Q, visited, degrees);
        reduceAdjacent(findHead(G, ch), degrees);
        printOutput(G, Q, visited, degrees);
    }
    else cout << endl;
}


//MAIN
int main()
{
    LQueue Q;
    Q.f = Q.r = NULL;
    HDPTR G = NULL;
    string input = "DE0E0D0F0G0G00";
    int degrees[nv] = {0};
    
    createHeaders(G, 0);
    inputList(G, G, input, 0, 0);
    setIndegrees(G, degrees);
    
    cout << "Matrix:\n";
    printMatrix(G, 0, 0, 1);
    cout << endl << endl;
    
    Lenqueue(Q, 'A');
    int visited[nv] = {0};
    printOutput(G, Q, visited, degrees);
    
    return 0;
}


