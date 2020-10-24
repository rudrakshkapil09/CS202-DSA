//merging 2 BSTs
#include <iostream>
using namespace std;

//tree definition
typedef
struct bstnode {
    struct bstnode *lchild;
    int data;
    int inn;                    //in order number
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

void getTraversal(BSTPTR T, int a[], int &arrayindex)
{
    if (T != NULL) {
        getTraversal(T->lchild, a, arrayindex);
        a[arrayindex++] = T->data;
        getTraversal(T->rchild, a, arrayindex);
    }
}

void mergeArrays(int a[], int b[], int sizea, int sizeb, int out[])
{
    int i = 0, j = 0, k = 0;
    while (i < sizea && j < sizeb) {
        if (a[i] < b[j])
            out[k++] = a[i++];
        else
            out[k++] = b[j++];
    }
    while (i < sizea)
        out[k++] = a[i++];
    while (j < sizeb) {
        out[k++] = a[j++];
    }
}

void mergeTrees(BSTPTR T1, BSTPTR T2, BSTPTR &T3)
{
    int trav1[50], trav2[50], trav3[100];
    int size1 = 0, size2 = 0;
    getTraversal(T1, trav1, size1);
    getTraversal(T2, trav2, size2);
    mergeArrays(trav1, trav2, size1, size2, trav3);
    setTree(T3, 0, size2+size1-1, trav3);
}

int main()
{
    BSTPTR T1 = NULL, T2 = NULL, T3 = NULL;
    int tree1[10] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int tree2[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18};
    
    setTree(T1, 0, 9, tree1);
    setTree(T2, 0, 8, tree2);
    cout << "Tree 1:\n";
    printTree(T1);
    cout << "\nTree 2:\n";
    printTree(T2);
    
    cout << "\nMerged Tree:\n";
    mergeTrees(T1, T2, T3);
    printTree(T3);
    cout << endl;
}
