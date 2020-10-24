//DFT - with stack iteratively
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

//LST definiton
typedef
struct lnode {
    char data;
    struct lnode *next;
} *LPTR;

struct LST {
    LPTR top;
};

//LST functions
void addToFront(LPTR &L, char B)
{
    LPTR T = new(lnode);
    T->data = B;
    if (L == NULL) {
        T->next = NULL;
    }
    else T->next = L;
    L = T;
}

LPTR deleteFirst(LPTR &L)
{
    if (L->next != NULL)
        return L->next;
    else return NULL;
}

int LstackIsEmpty(LST s1)
{
    if (s1.top == NULL)
        return 1;
    else return 0;
}

void Lpush(LST &s1, char B)
{
    addToFront(s1.top, B);
}

char Lpop(LST &s1)
{
    if (LstackIsEmpty(s1)) {
        cout << "Stack empty.";
        return NULL;
    }
    else {
        char B = s1.top->data;
        s1.top = deleteFirst(s1.top);
        return B;
    }
}

char LTop(LST s1)
{
    if (LstackIsEmpty(s1)) {
        return NULL;
    }
    else return s1.top->data;
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
        cout << "\n--+---------";
        printMatrix(G, i, j, 0);
    }
    else {
        cout << endl << G->key << " |";
        printLine(G->dtlink, 0);
        printMatrix(G->hdlink, i, 0, 0);
    }
}

/*DFT*/
char findNextAdjacent(hdnode::DTPTR D, int visited[])
{
    if (!D) return '\0';
    else {
        if (visited[D->key->key-65] == 0)
            return D->key->key;
        else return findNextAdjacent(D->next, visited);
    }
}

char findUnvisited(int visited[], int i)
{
    if (i >= nv) return '\0';
    if (visited[i] == 0) {
        visited[i] = 1;
        return i+65;
    }
    else return findUnvisited(visited, i+1);
}

void DFT(HDPTR orG, LST S, int visited[])
{
    int count = 0, only_one = 0;
    int flag = 0;
    char prev = '\0';
    while (count < nv) {
        while (!LstackIsEmpty(S)) {
            char ch = LTop(S);
            visited[ch-65] = 1;
            char next = findNextAdjacent(findHead(orG, ch)->dtlink, visited);
            only_one = (next == '\0') ? 1 : 0;
            
            if (!flag) {
                count++;
                if (prev == '\0' && only_one)
                    cout << ch << "\n";
                else if (prev != '\0')
                    cout << prev << "->" << ch << endl;
            }
            flag = 0;
            
            if (next != '\0') {
                prev = ch;
                Lpush(S, next);
            }
            else {
                flag = 1;
                Lpop(S);
            }
        }
        if (LstackIsEmpty(S)) {
            flag = 0;
            char cont = findUnvisited(visited, 0);
            if  (cont != '\0')
                Lpush(S, cont);
            prev = '\0';
        }
    }
}


//MAIN
int main()
{
    string input_UG = "BC0AC0AB000";    //BCD0ACE0ABD0ACE0BD0 //BC0AC0AB0E0D0   //BC0AC0AB000
    string input_DG = "BC0CE00A00";  //BD0CE0AD0E00 //CD0AE0BD0E00 //D0CE0AD0E00    //BC0CE00A0D0    //CB0CE00A0D0 //B0C0D0E0B0
    
    HDPTR UG = NULL, DG = NULL;
    LST S;
    S.top = NULL;
    createHeaders(UG, 0);
    createHeaders(DG, 0);
    
    inputList(UG, UG, input_UG, 0, 0);
    inputList(DG, DG, input_DG, 0, 0);
    
    cout << "Undirected:\n";
    printMatrix(UG, 0, 0, 1);
    
    cout << "\n\nDirected:\n";
    printMatrix(DG, 0, 0, 1);
    cout << endl;
    
    cout << "\nDFT of Undirected:\n";
    int visited_UG[nv] = {0};
    char ch = 'E';
    Lpush(S, ch);
    DFT(UG, S, visited_UG);
    
    cout << "\nDFT of Directed:\n";
    int visited_DG[nv] = {0};
    S.top = NULL;
    ch = 'A';
    Lpush(S, ch);
    DFT(DG, S, visited_DG);
    
    return 0;
}


