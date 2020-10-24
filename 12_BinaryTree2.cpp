//Deserialising and Serialising a binary tree
#include <iostream>
using namespace std;

//tree defintion
typedef
struct btnode {
    struct btnode *lchild;
    char data;
    int inn;                    //in order number
    struct btnode *rchild;
} *BTPTR;

//singly linked list as a queue definitions
typedef
struct lnode {
    BTPTR BTPTR;
    struct lnode *next;
} *LPTR;

struct LQueue {
    LPTR f;
    LPTR r;
};

//LQueue functions
void LaddAfter(LPTR &L, BTPTR B)
{
    LPTR T = new(lnode);
    T->BTPTR = B;
    if (L == NULL) L = T;
    else {
        L->next = T;
        L = T;
    }
}

void Lenqueue(LQueue &LQ, BTPTR B)
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

BTPTR LdeleteFirst(LPTR &L)
{
    BTPTR B = L->BTPTR;
    L = L->next;
    return B;
}

BTPTR Ldequeue(LQueue &LQ)
{
    if (LqueueIsEmpty(LQ)) {
        cout << "Queue empty.";
        return NULL;
    }
    else {
        int is_one_element = 0;
        if (LQ.f == LQ.r)
            is_one_element = 1;
        BTPTR B = LdeleteFirst(LQ.f);
        if (is_one_element) LQ.f = LQ.r = NULL;
        return B;
    }
}

//tree functions
void insertNode(BTPTR &T, int k)
{
    if (T != NULL) {
        if (k < T->data) insertNode(T->lchild, k);
        else if (k > T->data) insertNode(T->rchild, k);
        else cout << "Error: Duplicate data.\n";
    }
    else {
        T = new(btnode);
        T->inn = 0;
        T->data = k;
        T->rchild = T->lchild = NULL;
    }
}

int getMid(int low, int high)
{
    return (high + low)/2;
}

void setTree(BTPTR &T, int low, int high, int a[])
{
    if (low <= high) {
        int j = getMid(low, high);
        insertNode(T, a[j]);
        setTree(T, low, j-1, a);
        setTree(T, j+1, high, a);
    }
}

int innindex = 1;
void setInorderIndex(BTPTR T)
{
    if (T != NULL) {
        setInorderIndex(T->lchild);
        T->inn = innindex++;
        setInorderIndex(T->rchild);
    }
}

void setSpaces(int n1, int n2)
{
    for (int i = n2 + 1; i < n1; i++)
        cout << " ";
}

int previnn = 0;
void printAsItIs(LQueue Q)
{
    if (!LqueueIsEmpty(Q)) {
        BTPTR T = Ldequeue(Q);
        if (T->data == -1 && !LqueueIsEmpty(Q)) {
            cout << "\n";
            Lenqueue(Q, T);
            previnn = 0;
        }
        else {
            if (T->data != -1) {
                setSpaces(T->inn, previnn);
                cout << T->data;
                previnn = T->inn;
            }
            if (T->lchild) Lenqueue(Q, T->lchild);
            if (T->rchild) Lenqueue(Q, T->rchild);
        }
        printAsItIs(Q);
    }
}

void printTree(BTPTR T)
{
    LQueue Q1;
    Q1.f = Q1.r = NULL;
    BTPTR D = new(btnode);        //Dummy
    D->lchild = D->rchild = NULL;
    D->data = -1;
    
    setInorderIndex(T);
    Lenqueue(Q1, T);
    Lenqueue(Q1, D);
    printAsItIs(Q1);
    previnn = 0;
    innindex = 1;
}

//special functions
int deserialise(BTPTR &T, char data[])
{
    static int dataindex = 0;
    char ch = data[dataindex++];
    if (ch != '.') {
        T = new(btnode);
        T->data = ch;
        T->lchild = T->rchild = NULL;
        deserialise(T->lchild, data);
        deserialise(T->rchild, data);
    }
    return dataindex;
}

void serialise(BTPTR T, char data[])
{
    static int dataindex = 0;
    if (T != NULL) {
        data[dataindex++] = T->data;
        serialise(T->lchild, data);
        serialise(T->rchild, data);
    }
    else data[dataindex++] = '.';
}

//[MAIN]
// 6 8 9 7 4 2 5 3 -1
// 18 12 27 5 15 20 45 10 36 81 50 -1
int main()
{
    BTPTR T = NULL;
    char serial[30] = "APML..J..R..BD.N..EF..S..";
    char output[30] = {};
    cout << "Deserialised order as a tree =>\n";
    int j = deserialise(T, serial);
    printTree(T);
    cout << "\n\nSerialised:\n";
    serialise(T, output);
    for (int i = 0; i < j; i++)
        cout << output[i];
    cout << endl;
}
