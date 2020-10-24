//finding nodes k1 and k2 in 2 BSTs that add up to a number s
#include <iostream>
using namespace std;
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

struct LST {
    LPTR top;
};

//LST functions
void addToFront(LPTR &L, BSTPTR B)
{
    LPTR T = new(lnode);
    T->bstptr = B;
    if (L == NULL) {
        T->next = NULL;
    }
    else T->next = L;
    L = T;
}

LPTR deleteFirst(LPTR &L)
{
    if (L->next != NULL)
        return L->next;
    else return NULL;
}

int LstackIsEmpty(LST s1)
{
    if (s1.top == NULL)
        return 1;
    else return 0;
}

void Lpush(LST &s1, BSTPTR B)
{
    addToFront(s1.top, B);
}

BSTPTR Lpop(LST &s1)
{
    if (LstackIsEmpty(s1)) {
        cout << "Stack empty.";
        return NULL;
    }
    else {
        BSTPTR B = s1.top->bstptr;
        s1.top = deleteFirst(s1.top);
        return B;
    }
}

BSTPTR LTop(LST s1)
{
    if (LstackIsEmpty(s1)) {
        cout << "Stack empty.";
        return NULL;
    }
    else return s1.top->bstptr;
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
    return (high+low)/2;
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
void findCommon(BSTPTR T1, BSTPTR T2, LST S1, LST S2, int sum)
{
    while (1) {
        if (T1) {
            Lpush(S1 ,T1);
            T1 = T1->lchild;
        }
        else if (T2) {
            Lpush(S2, T2);
            T2 = T2->rchild;
        }
        else if (!LstackIsEmpty(S1) && !LstackIsEmpty(S2)) {
            T1 = LTop(S1);
            T2 = LTop(S2);
            if (T1->data + T2->data < sum) {
                Lpop(S1);
                T1 = T1->rchild;
                T2 = NULL;
            }
            else if (T1->data + T2->data > sum) {
                Lpop(S2);
                T2 = T2->lchild;
                T1 = NULL;
            }
            else if (T1->data + T2->data == sum){
                Lpop(S1);
                Lpop(S2);
                cout << T1->data << " + " << T2->data << " = " << sum << endl;;
                T1 = T1->rchild;
                T2 = T2->lchild;
            }
        }
        else break;
    }
}


//[MAIN]
int main()
{
    LST S1, S2;
    S1.top = S2.top = NULL;
    
    BSTPTR T1 = NULL, T2 = NULL;
    
    int list1[12] = {5, 10, 15, 18, 25, 29, 35, 40, 41, 75, 85, 90};
    int list2[10] = {2, 5, 29, 32, 38, 40, 41, 65, 75, 90};
    //int list2[10] = {5, 10, 15, 18, 25, 29, 35, 40, 41, 75};
    setTree(T1, 0, 11, list1);
    setTree(T2, 0, 9, list2);
    
    cout << "Tree 1:\n";
    printTree(T1);
    cout << "\n\nTree 2:\n";
    printTree(T2);
    cout << endl << endl;
    
    findCommon(T1, T2, S1, S2, 100);
    return 0;
}
