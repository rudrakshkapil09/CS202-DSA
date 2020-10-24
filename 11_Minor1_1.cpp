//Minor question 1 - constructing BST from a given preorder & postorder traversal
//6 4 2 3 5 8 7 9
//3 2 5 4 8 7 9 6

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

//main print tree function
void printTree(LQueue Q, BSTPTR T, BSTPTR D)
{
    setInorderIndex(T);
    Lenqueue(Q, T);
    Lenqueue(Q, D);
    printAsItIs(Q);
    previnn = 0;
    innindex = 1;
}

//special functions
int getMidPre(int low, int high)
{
    return (low);
}

int getMidPost(int low, int high)
{
    return (high);
}

void setTreePre(BSTPTR &T, int low, int high, int a[])
{
    if (low <= high) {
        int j = getMidPre(low, high);
        insertNode(T, a[j]);
        setTreePre(T, low, j-1, a);
        setTreePre(T, j+1, high, a);
    }
}

void setTreePost(BSTPTR &T, int low, int high, int a[])
{
    if (low <= high) {
        int j = getMidPost(low, high);
        insertNode(T, a[j]);
        setTreePost(T, low, j-1, a);
        setTreePost(T, j+1, high, a);
    }
}


int main()
{
    LQueue Q1;
    Q1.f = Q1.r = NULL;
    BSTPTR D = new(bstnode);        //Dummy
    D->lchild = D->rchild = NULL;
    D->data = -1;
    BSTPTR TPre = NULL, Tpost = NULL;
    int list_pre[8] = {6, 4, 2, 3, 5, 8, 7, 9};
    int list_post[8] = {3, 2, 5, 4, 7, 9, 8, 6};
    setTreePre(TPre, 0, 7, list_pre);
    setTreePost(Tpost, 0, 7, list_post);
    
    printTree(Q1, Tpost, D);
    cout << endl;
    
    printTree(Q1, TPre, D);
    cout << endl;
    
}






