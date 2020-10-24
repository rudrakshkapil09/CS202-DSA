//Minor question 2 - cousins
#include <iostream>
using namespace std;

//tree defintion
typedef
struct bstnode {
    struct bstnode *lchild;
    int data;
    int inn;                    //in order number
    struct bstnode *rchild;
    struct bstnode *lvptr;
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
        T->lvptr = NULL;
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

//special functions
int getLevel(BSTPTR T, int x, int level)
{
    if (T) {
        if (T->data != x) {
            int t = getLevel(T->lchild, x, level+1);
            if (t) return t;
            else {
                t = getLevel(T->rchild, x, level+1);
                return t;
            }
        }
        else return level;
    }
    else return 0;
}

int sum = 0;
void printCousins(BSTPTR T, int key, int level)
{
    static BSTPTR P = T;
    if (T) {
        if (getLevel(P, T->data, 0) != level-1) {
            printCousins(T->lchild, key, level);
            printCousins(T->rchild, key, level);
        }
        else {
            if (T->lchild->data == key || T->rchild->data == key)
                return;
            if (T->lchild) {
                cout << T->lchild->data << " ";
                sum += T->lchild->data;
            }
            if (T->rchild) {
                cout << T->rchild->data << " ";
                sum += T->rchild->data;
            }
        }
    }
}


//[MAIN]
// 6 8 9 7 4 2 5 3 -1
// 18 12 27 5 15 20 45 10 36 81 50 -1
int main()
{
    BSTPTR T = NULL;
    LQueue Q;
    Q.f = Q.r = NULL;
    int list[15] = {3, 5, 10, 12, 13, 15, 18, 19, 20, 27, 36, 45, 50, 81, 90};
    setTree(T, 0, 14, list);
    cout << "Tree:\n";
    printTree(T);
    
    int node;
    cout << "\n\nEnter node to find its cousins: ";
    cin >> node;
    cout << "Cousins of " << node << " => ";
    printCousins(T, node, getLevel(T, node, 0));
    cout << "\nSum => " << sum;
    
    cout << endl;
}
