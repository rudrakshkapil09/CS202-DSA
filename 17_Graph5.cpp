//BFT
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

//creation functions
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
        cout << "\n--+---------";
        printMatrix(G, i, j, 0);
    }
    else {
        cout << endl << G->key << " |";
        printLine(G->dtlink, 0);
        printMatrix(G->hdlink, i, 0, 0);
    }
}

//BFT
void enqueueAdjacent(LQueue &Q, hdnode::DTPTR D, int visited[], int &count, int &was_added)
{
    if (D) {
        if (visited[D->key->key-65] == 0) {
            Lenqueue(Q, D->key->key);
            visited[D->key->key-65] = 1;
            count++;
            was_added = 1;
        }
        enqueueAdjacent(Q, D->next, visited, count, was_added);
    }
    else Lenqueue(Q, '0');
}

char findUnvisited(int visited[], int i)
{
    if (visited[i] == 0) {
        visited[i] = 1;
        return i+65;
    }
    else return findUnvisited(visited, i+1);
}

void addToEnd(char arr[], char ch, int i)
{
    if (arr[i] == '\0')
        arr[i] = ch;
    else addToEnd(arr, ch, i+1);
}

void BFT(HDPTR G, int visited[], LQueue &Q, int count, char starts[], int startsindex)
{
    if (count <= nv) {
        if (!LqueueIsEmpty(Q)) {
            char ch = Ldequeue(Q);
            int was_added = 0;
            
            if (ch != '0') {
                visited[ch-65] = 1;
                if (G->dtlink)
                    enqueueAdjacent(Q, findHead(G, ch)->dtlink, visited, count, was_added);
                if (was_added && ch != starts[startsindex])
                    addToEnd(starts, ch, 0);
                if (!was_added && ch == starts[startsindex])
                    cout << ch << "\n";
                else
                    (ch != starts[startsindex]) ? ((starts[startsindex] != '\0') ? cout << starts[startsindex] << "->"<< ch << "\n": cout << ch << "\n") : cout << "";
            }
            else startsindex++;
            BFT(G, visited, Q, count, starts, startsindex);
        }
        else {
            Lenqueue(Q, findUnvisited(visited, 0));
            BFT(G, visited, Q, count+1, starts, startsindex);
        }
    }
}

//MAIN
int main()
{
    string input_UG = "BCD0AC0ABD0AC00";
    string input_DG = "BD0CE0AD0E00";   //BD0CE0AD0E00  //CD0AE0BD0E00 //D0CE0AD0E00
    //B0C0D0E0B0
    
    HDPTR UG = NULL, DG = NULL;
    LQueue Q;
    Q.f = Q.r = NULL;
    createHeaders(UG, 0);
    createHeaders(DG, 0);
    
    inputList(UG, UG, input_UG, 0, 0);
    inputList(DG, DG, input_DG, 0, 0);
    
    cout << "Undirected:\n";
    printMatrix(UG, 0, 0, 1);
    
    cout << "\n\nDirected:\n";
    printMatrix(DG, 0, 0, 1);
    cout << endl;
    
    cout << "\nBFT of Undirected:\n";
    char start_UG = 'A';
    int visited_UG[nv] = {0}, count_UG = 1, startindex_UG = 0;
    char starts_UG[nv] = {'\0'};
    starts_UG[0] = start_UG;
    Lenqueue(Q, start_UG);
    BFT(UG, visited_UG, Q, count_UG, starts_UG, startindex_UG);
    cout << endl;
    
    cout << "\nBFT of Directed:\n";
    Q.f = Q.r = NULL;
    char start_DG = 'E';
    int visited_DG[nv] = {0}, count_DG = 1, startindex_DG = 0;
    char starts_DG[nv] = {'\0'};
    starts_DG[0] = start_DG;
    Lenqueue(Q, start_DG);
    BFT(DG, visited_DG, Q, count_DG, starts_DG, startindex_DG);
    cout << endl;
    
    
    return 0;
}


