//4.a) Constructing full binary tree from preorder and postorder - DLR & LRD
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
int getRoot(char LRD[], char key, int low, int high)
{
    int i = 0;
    for (i = low; i <= high; i++)
        if (LRD[i] == key)
            return i;
    return -1;
}

BTPTR setTree(char LRD[], char DLR[], int low, int high)
{
    static int index = 0;
    if (low > high) return NULL;
    
    BTPTR T = new(btnode);
    T->lchild = T->rchild = NULL;
    T->data = DLR[index++];
    
    if (low == high) return T;
    else {
        int j = getRoot(LRD, DLR[index], low, high);
        if (j <= high) {
            T->lchild = setTree(LRD, DLR, low, j);
            T->rchild = setTree(LRD, DLR, j+1, high-1);
        }
        return T;
    }
}


//[MAIN]
int main()
{
    char DLR[30] = "APMLJRBDNEFS";
    char LRD[30] = "LJMRPNDFSEBA";
    BTPTR T = setTree(LRD, DLR, 0, 11);
    printTree(T);
    cout << endl;
}
