//from DLL to BST
#include <iostream>
using namespace std;

//tree defintion
typedef
struct bstnode {
    struct bstnode *lchild;
    int data;
    int inn;                    //in order number
    struct bstnode *rchild;
} *BSTPTR;

//DLL defintion
typedef
struct dnode {
    struct dnode *left;
    int data;
    struct dnode *right;
} *DPTR;

//singly linked list as a queue & stack definitions
typedef
struct lnode {
    BSTPTR bstptr;
    struct lnode *next;
} *LPTR;

struct LQueue {
    LPTR f;
    LPTR r;
};

//DLL functions
void rprint(DPTR D)
{
    if (D != NULL) {
        cout << int(D->data) << ", ";
        rprint(D->right);
    }
}

void addToEnd(DPTR &D, int x)
{
    DPTR D1 = new(dnode);
    DPTR D2 = D;
    D1->data = x;
    D1->right = NULL;
    D1->left = NULL;
    if (D == NULL)
        D = D1;
    else {
        while (D2->right != NULL)
            D2 = D2->right;
        D2->right = D1;
        D1->left = D2;
    }
}

void inputDList(DPTR &D)
{
    int n = 1;
    cout << "Enter elements: ";
    while (1) {
        cin >> n;
        if (n == -1)
            break;
        addToEnd(D, n);
    }
}

//LQueue functions
void LaddAfter(LPTR &L, BSTPTR B)
{
    LPTR T = new(lnode);
    T->bstptr = B;
    if (L == NULL) L = T;
    else {
        L->next = T;
        L = T;
    }
}

void Lenqueue(LQueue &LQ, BSTPTR B)
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

BSTPTR LdeleteFirst(LPTR &L)
{
    BSTPTR B = L->bstptr;
    L = L->next;
    return B;
}

BSTPTR Ldequeue(LQueue &LQ)
{
    if (LqueueIsEmpty(LQ)) {
        cout << "Queue empty.";
        return NULL;
    }
    else {
        int is_one_element = 0;
        if (LQ.f == LQ.r)
            is_one_element = 1;
        BSTPTR B = LdeleteFirst(LQ.f);
        if (is_one_element) LQ.f = LQ.r = NULL;
        return B;
    }
}

//tree functions
void insertNode(BSTPTR &T, int k)
{
    if (T != NULL) {
        if (k < T->data) insertNode(T->lchild, k);
        else if (k > T->data) insertNode(T->rchild, k);
        else cout << "Error: Duplicate data.\n" << T->data;
    }
    else {
        T = new(bstnode);
        T->inn = 0;
        T->data = k;
        T->rchild = T->lchild = NULL;
    }
}

void setInorderIndex(BSTPTR T)
{
    static int innindex = 1;
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

void printAsItIs(LQueue Q)
{
    static int prev = 0;
    if (!LqueueIsEmpty(Q)) {
        BSTPTR T = Ldequeue(Q);
        if (T->data == -1 && !LqueueIsEmpty(Q)) {
            cout << "\n";
            Lenqueue(Q, T);
            prev = 0;
        }
        else {
            if (T->data != -1) {
                setSpaces(T->inn, prev);
                cout << T->data;
                prev = T->inn;
            }
            if (T->lchild) Lenqueue(Q, T->lchild);
            if (T->rchild) Lenqueue(Q, T->rchild);
        }
        printAsItIs(Q);
    }
}

//main print tree function
void printTree(LQueue Q, BSTPTR T, BSTPTR D)
{
    setInorderIndex(T);
    Lenqueue(Q, T);
    Lenqueue(Q, D);
    printAsItIs(Q);
}


//special functions
DPTR getMid(DPTR D, DPTR S)
{
    DPTR F = D;      //fast
    while (F != S && F->right != S) {
        F = F->right->right;
        D = D->right;
    }
    return D;
}

void setTree(BSTPTR &T, DPTR D, DPTR S)
{
    if (D != S && D != NULL && D->left != S) {
        DPTR J = getMid(D, S);
        insertNode(T, J->data);
        setTree(T, D, J->left);
        setTree(T, J->right, S);
    }
    else if (D == S) insertNode(T, D->data);
}

//[MAIN]
/*
 6 8 9 7 4 2 5 3 -1
 1 6 7 9 21 24 27 32 45 53 69 78 -1
 */
int main()
{
    BSTPTR T = NULL;
    
    BSTPTR DUM = new(bstnode);        //Dummy
    DUM->lchild = DUM->rchild = NULL;
    DUM->data = -1;
    
    LQueue LQ;
    LQ.f = LQ.r = NULL;
    
    DPTR D = NULL, S = NULL;
    inputDList(D);
    rprint(D);
    S = D;
    while (S->right != NULL)
        S = S->right;
    setTree(T, D, S);
    
    cout << endl;
    printTree(LQ, T, DUM);
    cout << endl;
    return 0;
}
