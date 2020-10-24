//Printing top view and bottom view of a tree
#include <iostream>
using namespace std;

//tree defintion
typedef
struct btnode {
    struct btnode *lchild;
    char data;
    int inn;                    //in order number
    int hd;
    struct btnode *rchild;
    struct btnode *lvptr;
} *BTPTR;

//singly linked list as a queue definitions
typedef
struct lnode {
    BTPTR BTPTR;
    struct lnode *next;
} *LPTR;

struct LQueue {
    LPTR f = NULL;
    LPTR r = NULL;
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

//creation
int getRoot(char LDR[], char root, int low, int high)
{
    int i = 0;
    for (i = low; i <= high; i++)
        if (LDR[i] == root) break;
    return i;
}

void setTree(BTPTR &T, char LDR[], char DLR[], int low, int high)
{
    static int index = 0;
    if (low <= high && DLR[index] != '\0') {
        int j = getRoot(LDR, DLR[index++], low, high);
        T = new(btnode);
        T->data = LDR[j];
        T->lchild = T->rchild = T->lvptr = NULL;
        setTree(T->lchild, LDR, DLR, low, j-1);
        setTree(T->rchild, LDR, DLR, j+1, high);
    }
}

//special functions
void createLevelLink(BTPTR T)
{
    if (T) {
        BTPTR T2 = T->lvptr;
        while (T2 && (!T2->lchild && !T2->rchild))
            T2 = T2->lvptr;
        
        if (T->lchild && T->rchild) {
            T->lchild->lvptr = T->rchild;
            if (T2)
                T->rchild->lvptr = (T2->lchild) ? T2->lchild : T2->rchild;
        }
        else if (T->lchild && T2)
            T->lchild->lvptr = (T2->lchild) ? T2->lchild : T2->rchild;
        else if (T->rchild && T2)
            T->rchild->lvptr = (T2->lchild) ? T2->lchild : T2->rchild;
        
        createLevelLink(T->lchild);
        createLevelLink(T->rchild);
    }
}

//special functions
void setHD(BTPTR T)
{
    if (T) {
        if (T->lchild) T->lchild->hd = T->hd - 1;
        if (T->rchild) T->rchild->hd = T->hd + 1;
        setHD(T->lchild);
        setHD(T->rchild);
    }
}

void arrangeInQueues(BTPTR T, LQueue Q[])
{
    static BTPTR P = T;
    if (T) {
        Lenqueue(Q[T->hd+5], T);
        arrangeInQueues(T->lvptr, Q);
    }
    else if (P) {
        if (!P->lchild && !P->rchild) {
            BTPTR T2 = P;
            P = (P->lvptr) ? P->lvptr : T2;
        }
        P = (P->lchild) ? P->lchild : P->rchild;
        arrangeInQueues(P, Q);
    }
}

void printTV(LQueue Q[])
{
    for (int i = 0; i < 10; i++) {
        if (!LqueueIsEmpty(Q[i]))
            cout << Q[i].f->BTPTR->data;
    }
}

void printBV(LQueue Q[])
{
    for (int i = 0; i < 10; i++) {
        if (!LqueueIsEmpty(Q[i]))
            cout << Q[i].r->BTPTR->data;
    }
}

//[MAIN]
int main()
{
    //simple trees
    char DLR[30] = "ADEGHIJFMPNLS";
    char LDR[30] = "GIHJEFDMAPLNS";
    //more complicated trees
    char DLR2[30] = "ABCDEFGHIJL"/*MN*/"K";    //MN removed to check RV if left subtree is larger
    char LDR2[30] = "DCGFEBAH"/*MN*/"LJIK";
    
    LQueue vertical_elements[10];
    BTPTR T = NULL;
    T = new(btnode);
    T->data = DLR[0];
    T->lchild = T->rchild = NULL;
    
    setTree(T, LDR, DLR, 0, 13);
    createLevelLink(T);
    T->hd = 0;
    setHD(T);
    arrangeInQueues(T, vertical_elements);
    printTree(T);
    
    cout << "\n\nTop view => ";
    printTV(vertical_elements);
    cout << "\nBottom view => ";
    printBV(vertical_elements);
    
    cout << endl;
}



