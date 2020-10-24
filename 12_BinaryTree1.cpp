//Making a BST from a BT
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

//singly linked list as a queue definitions
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

//tree functions
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

int getMid(int low, int high)
{
    return (high + low)/2;
}

void setTree(BSTPTR &T, int low, int high, int a[])
{
    if (low <= high) {
        int j = getMid(low, high);
        insertNode(T, a[j]);
        setTree(T, low, j-1, a);
        setTree(T, j+1, high, a);
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
        cout << " ";
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

//special functions
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i-1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = key;
    }
}

void getTraversal(BSTPTR T, int a[], int &arrayindex)
{
    if (T != NULL) {
        getTraversal(T->lchild, a, arrayindex);
        a[arrayindex++] = T->data;
        getTraversal(T->rchild, a, arrayindex);
    }
}

void setBTree(BSTPTR &BT)
{
    BT = new(bstnode);
    BT->data = 30;
    BT->rchild = new(bstnode);
    BT->rchild->data = 18;
    BT->rchild->lchild = NULL;
    BT->rchild->rchild = new(bstnode);
    BT->rchild->rchild->data = 3;
    BT->rchild->rchild->rchild = NULL;
    BT->rchild->rchild->lchild = NULL;
    
    BT->lchild = new(bstnode);
    BT->lchild->data = 20;
    BT->lchild->rchild = new(bstnode);
    BT->lchild->rchild->data = 45;
    BT->lchild->rchild->lchild = NULL;
    BT->lchild->rchild->rchild = NULL;
    BT->lchild->lchild = new(bstnode);
    BT->lchild->lchild->data = 9;
    BT->lchild->lchild->lchild = NULL;
    BT->lchild->lchild->rchild = new(bstnode);
    BT->lchild->lchild->rchild->data = 5;
    BT->lchild->lchild->rchild->lchild = NULL;
    BT->lchild->lchild->rchild->rchild = NULL;
}

void convertBT(BSTPTR BT, BSTPTR &BST)
{
    int trav[10], count = 0;
    getTraversal(BT, trav, count);
    insertionSort(trav, count);
    setTree(BST, 0, count-1, trav);
}

//[MAIN]
// 6 8 9 7 4 2 5 3 -1
// 18 12 27 5 15 20 45 10 36 81 50 -1
int main()
{
    BSTPTR BT = NULL, BST = NULL;
    setBTree(BT);
    cout << "Binary Tree: \n";
    printTree(BT);
    
    convertBT(BT, BST);
    cout << "\n\nBinary Search Tree: \n";
    printTree(BST);
    cout << endl;
}

