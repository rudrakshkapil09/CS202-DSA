//printing in level order with 5 extra variations
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

void inputTree(BSTPTR &T)
{
    int num;
    cout << "Enter elements of tree (end -> -1):\n";
    while (1) {
        cin >> num;
        if (num == -1) break;
        insertNode(T, num);
    }
}

//special functions
//1. level order - linear
void printLevelOrder1(LQueue Q)
{
    if (!LqueueIsEmpty(Q)) {
        BSTPTR T = Ldequeue(Q);
        cout << T->data;
        if (T->lchild) Lenqueue(Q, T->lchild);
        if (T->rchild) Lenqueue(Q, T->rchild);
        printLevelOrder1(Q);
    }
}

//2. level order - hierarchy
void printLevelOrder2(LQueue Q)
{
    if (!LqueueIsEmpty(Q)) {
        BSTPTR T = Ldequeue(Q);
        if (T->data == -1 && !LqueueIsEmpty(Q)) {
            cout << "\n";
            Lenqueue(Q, T);
        }
        else {
            if (T->data != -1) cout << T->data;
            if (T->lchild) Lenqueue(Q, T->lchild);
            if (T->rchild) Lenqueue(Q, T->rchild);
        }
        printLevelOrder2(Q);
    }
}

//3. level order - hierarchy mirrored
void printLevelOrder3(LQueue Q)
{
    if (!LqueueIsEmpty(Q)) {
        BSTPTR T = Ldequeue(Q);
        if (T->data == -1 && !LqueueIsEmpty(Q)) {
            cout << "\n";
            Lenqueue(Q, T);
        }
        else {
            if (T->data != -1) cout << T->data;
            if (T->rchild) Lenqueue(Q, T->rchild);
            if (T->lchild) Lenqueue(Q, T->lchild);
        }
        printLevelOrder3(Q);
    }
}

//4. level order - hierarchy spiral - use 2 stacks
void printLevelOrder4(LST S1, LST S2, BSTPTR T)
{
    if (T == NULL) return;
    else {
        Lpush(S1, T);
        while (!LstackIsEmpty(S1) || !LstackIsEmpty(S2)) {
            while (!LstackIsEmpty(S1)) {
                BSTPTR T1 = Lpop(S1);
                cout << T1->data;
                if (T1->rchild) Lpush(S2, T1->rchild);
                if (T1->lchild) Lpush(S2, T1->lchild);
            }
            cout << "\n";
            while (!LstackIsEmpty(S2)) {
                BSTPTR T1 = Lpop(S2);
                cout << T1->data;
                if (T1->lchild) Lpush(S1, T1->lchild);
                if (T1->rchild) Lpush(S1, T1->rchild);
            }
            cout << "\n";
        }
    }
}

//5. level order - hierarchy upside down
void printLevelOrder5(LQueue Q, LST &L)
{
    if (!LqueueIsEmpty(Q)) {
        BSTPTR T = Ldequeue(Q);
        if (T->data == -1 && !LqueueIsEmpty(Q)) {
            Lenqueue(Q, T);
            Lpush(L, T);
        }
        else {
            if (T->data != -1) Lpush(L, T);
            if (T->rchild) Lenqueue(Q, T->rchild);
            if (T->lchild) Lenqueue(Q, T->lchild);
        }
        printLevelOrder5(Q, L);
    }
    else {
        while (!LstackIsEmpty(L)) {
            BSTPTR T2 = Lpop(L);
            (T2->data != -1) ? cout << T2->data : cout << "\n";
        }
    }
}

//6. level order - hierarchy spiral upside down
void printLevelOrder6(LST S1, LST S2, LST S3, BSTPTR T, BSTPTR D)
{
    if (T == NULL) return;
    else {
        Lpush(S1, T);
        while (!LstackIsEmpty(S1) || !LstackIsEmpty(S2)) {
            while (!LstackIsEmpty(S1)) {
                BSTPTR T1 = Lpop(S1);
                Lpush(S3, T1);
                if (T1->rchild) Lpush(S2, T1->rchild);
                if (T1->lchild) Lpush(S2, T1->lchild);
            }
            Lpush(S3, D);
            while (!LstackIsEmpty(S2)) {
                BSTPTR T1 = Lpop(S2);
                Lpush(S3, T1);
                if (T1->lchild) Lpush(S1, T1->lchild);
                if (T1->rchild) Lpush(S1, T1->rchild);
            }
            Lpush(S3, D);
        }
    }
    while (!LstackIsEmpty(S3)) {
        BSTPTR T2 = Lpop(S3);
        (T2->data != -1) ? cout << T2->data : cout << "\n";
    }
}

//[MAIN]
/*
 6 8 9 7 4 2 5 3 -1
 */
int main()
{
    BSTPTR T = NULL;
    BSTPTR D = new(bstnode);        //Dummy
    D->lchild = D->rchild = NULL;
    D->data = -1;
    LQueue LQ;
    LQ.f = NULL;
    LQ.r = NULL;
    LST LS1, LS2, LS3;
    LS1.top = LS2.top = LS3.top = NULL;
    
    inputTree(T);
    cout << "\n\nLevel order 1 - linear:\n";
    Lenqueue(LQ, T);            //to get first pointer
    printLevelOrder1(LQ);
    
    Lenqueue(LQ, D);
    cout << "\n\nLevel order 2 - hierarchy:\n";
    printLevelOrder2(LQ);
    
    cout << "\n\nLevel order 3 - hierarchy mirrored:\n";
    printLevelOrder3(LQ);
    
    cout << "\n\nLevel order 4 - hierarchy spiral:\n";
    printLevelOrder4(LS1, LS2, T);
    
    cout << "\nLevel order 5 - hierarchy upside down:\n";
    printLevelOrder5(LQ, LS1);
    
    cout << "\n\nLevel order 6 - hierarchy upside down spiral:";
    printLevelOrder6(LS1, LS2, LS3, T, D);
    
    cout << endl << endl;
    return 0;
}
