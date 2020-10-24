//deleting a bstnode and making it the head of the tree
#include <iostream>
#include <iomanip>
using namespace std;

//struct defintions
typedef
struct bstnode {
    struct bstnode *lchild;
    int data;
    int inn = 0;
    struct bstnode *rchild;
} *BSTPTR;

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


//printing functions
void insertNode(BSTPTR &T, int k)
{
    if (T != NULL) {
        if (k < T->data) insertNode(T->lchild, k);
        else if (k > T->data) insertNode(T->rchild, k);
        else cout << "Error: Duplicate data.\n";
    }
    else {
        T = new(bstnode);
        T->inn = 0;
        T->data = k;
        T->rchild = T->lchild = NULL;
    }
}

int innindex = 1;
void setInorderIndex(BSTPTR T)
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
        cout << "  ";
}

int previnn = 0;
void printAsItIs(LQueue Q)
{
    if (!LqueueIsEmpty(Q)) {
        BSTPTR T = Ldequeue(Q);
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

void printTree(BSTPTR T)
{
    LQueue Q1;
    Q1.f = Q1.r = NULL;
    BSTPTR D = new(bstnode);        //Dummy
    D->lchild = D->rchild = NULL;
    D->data = -1;
    
    setInorderIndex(T);
    Lenqueue(Q1, T);
    Lenqueue(Q1, D);
    printAsItIs(Q1);
    previnn = 0;
    innindex = 1;
}

void setTree(BSTPTR &T, int input[], int n)
{
    for (int i = 0; i < n; i++)
        insertNode(T, input[i]);
}

//special functions
BSTPTR findMin(BSTPTR T) {
    if (T)
        findMin(T->lchild);
    return T;
}

BSTPTR deleteNode(BSTPTR H, int k)
{
    if (H == NULL) return H;
    if (H->data > k)
        H->lchild = deleteNode(H->lchild, k);
    else if (H->data < k)
        H->rchild = deleteNode(H->rchild, k);
    else {
        if (!H->rchild || !H->lchild) {
            BSTPTR T1 = (H->lchild) ? H->lchild : H->rchild;
            if (!T1) {
                T1 = H;
                H = NULL;
            }
            else
                *H = *T1;
        }
        else {
            BSTPTR T1 = findMin(H->rchild);
            H->data = T1->data;
            H->rchild = deleteNode(H->rchild, T1->data);
        }
    }
    return H;
}

BSTPTR makeHead(BSTPTR T, BSTPTR P, int key)
{
    if (T) {
        if (key > T->data) return makeHead(T->rchild, P, key);
        else if (key < T->data) return makeHead(T->lchild, P, key);
        else {
            deleteNode(T, key);
            BSTPTR T1 = new bstnode;
            T1->data = key;
            if (T1->data > P->data) {
                T1->lchild = P;
                if (T1->data < P->rchild->data) {
                    T1->rchild = P->rchild;
                    P->rchild = NULL;
                }
            }
            else if (T1->data < P->data) {
                T1->rchild = P;
                if (T1->data > P->lchild->data) {
                    T1->lchild = P->lchild;
                    P->lchild = NULL;
                }
            }
            return T1;
        }
    }
    return T;
}

//MAIN
int main()
{
    BSTPTR T = NULL;
    int input[] = {25, 18, 10, 15, 21, 19, 23, 22, 45, 37, 85};
    setTree(T, input, 11);
    printTree(T);
    
    T = makeHead(T, T, 21);
    cout << endl << endl;
    printTree(T);
    cout << endl;
}
