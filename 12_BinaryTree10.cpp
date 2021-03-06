//Printing left view and right view of a tree
#include <iostream>
using namespace std;

//tree defintion
typedef
struct btnode {
    struct btnode *lchild;
    char data;
    int inn;                    //in order number
    int vd;
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
void setVD(BTPTR T)
{
    static int vdindex = 0;
    if (T != NULL) {
        T->vd = vdindex--;
        setVD(T->lchild);
        setVD(T->rchild);
        vdindex = T->vd;
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

void printLevel(BTPTR T, int num)
{
    for (int i = 0; i < num; i++) {
        if (!T->lchild && !T->rchild) T = T->lvptr;
        if (T)
            T = (T->lchild) ? T->lchild : T->rchild;
    }
    cout << "\nElements in level " << num << " => ";
    while (T) {
        cout << T->data << " ";
        T = T->lvptr;
    }
}

//special functions
void printLV(BTPTR T)
{
    if (T != NULL) {
        cout << T->data;
        while (!T->lchild && !T->rchild && T->lvptr) {
            BTPTR T2 = T;
            T = (T->lvptr) ? T->lvptr : T2;
        }
        (T->lchild) ? printLV(T->lchild) : printLV(T->rchild);
    }
}

void printRV(BTPTR T)
{
    if (T != NULL) {
        BTPTR TR = T;
        while (TR->lvptr)
            TR = TR->lvptr;
        cout << TR->data;
        
        if (!T->lchild && !T->rchild) {
            BTPTR T2 = T;
            T = (T->lvptr) ? T->lvptr : T2;
        }
        (T->lchild) ? printRV(T->lchild) : printRV(T->rchild);
    }
}

//[MAIN]
int main()
{
    BTPTR T = NULL;
    //simple trees
    char DLR[30] = "ADEGHIJFMPNLS";
    char LDR[30] = "GIHJEFDMAPLNS";
    //more complicated trees
    char DLR2[30] = "ABCDEFGHIJL"/*MN*/"K";    //MN removed to check RV if left subtree is larger
    char LDR2[30] = "DCGFEBAH"/*MN*/"LJIK";
    
    T = new(btnode);
    T->data = DLR2[0];
    T->lchild = T->rchild = NULL;
    
    setTree(T, LDR2, DLR2, 0, 13);
    createLevelLink(T);
    setVD(T);
    printTree(T);
    
    cout << endl;
    for (int i = 0; i < 7; i++)
        printLevel(T, i);
    
    cout << "\n\nLeft view => ";
    printLV(T);
    cout << "\nRight view => ";
    printRV(T);
    cout << endl;
}



