 //all possible paths from one vertex to another
#include <iostream>
using namespace std;
const int nv = 5;

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
    if (!D || i > nv) return;
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
        cout << "\n--+---------";
        printMatrix(G, i, j, 0);
    }
    else {
        cout << endl << G->key << " |";
        printLine(G->dtlink, 0);
        printMatrix(G->hdlink, i, 0, 0);
    }
}

/*Special functions*/
char findNextAdjacent(hdnode::DTPTR D, int visited[])
{
    if (!D) return '\0';
    else {
        if (visited[D->key->key-65] == 0) {
            visited[D->key->key-65] = 1;
            return D->key->key;
        }
        else return findNextAdjacent(D->next, visited);
    }
}

int printPaths(HDPTR G, char first, char end)
{
    if (first != end) {
        char next_vertex = 'a';
        int *visited = new int[nv];
        for (int i = 0; i < nv; i++)
            visited[i] = 0;
        
        while (1) {
            next_vertex = findNextAdjacent(findHead(G, first)->dtlink, visited);
            if (next_vertex == '\0') break;
            cout << first << "->";
            if (!printPaths(G, next_vertex, end)) {
                cout << "\b \b\b \b\b \b";
            }
        }
        return 0;
    }
    else {
        cout << end << endl;
        return 1;
    }
    
}


//MAIN
int main()
{
    string input_DG = "BCD0CE00C0D0";   //BD0CE0AD0E00  //CD0AE0BD0E00 //D0CE0AD0E00
    //B0C0D0E0B0    //BC0CE00A0D0   //CB0CE00A0D0   //BC0CE00A00
    
    HDPTR DG = NULL;
    createHeaders(DG, 0);
    inputList(DG, DG, input_DG, 0, 0);
    
    cout << "Directed:\n";
    printMatrix(DG, 0, 0, 1);
    cout << endl;
    
    char first = 'A', end = 'D';
    cout << "\nAll paths from " << first << " to " << end << ":\n";
    printPaths(DG, first, end);
    
    
    return 0;
}


