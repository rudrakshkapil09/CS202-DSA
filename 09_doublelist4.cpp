//implementing queues as double and singly linked lists
#include <iostream>
using namespace std;

//structure definitions
typedef
struct lnode {
    int data;
    struct lnode *next;
} *LPTR;

struct LQueue {
    LPTR f;
    LPTR r;
};

typedef
struct dnode {
    int data;
    struct dnode *left;
    struct dnode *right;
} *DPTR;

struct DQueue {
    DPTR f;
    DPTR r;
};

//special functions - SLL
void LaddAfter(LPTR &L, int x)
{
    LPTR T = new(lnode);
    T->data = x;
    if (L == NULL)
        L = T;
    else {
        L->next = T;
        L = T;
    }
}

void Lenqueue(LQueue &LQ, int x)
{
    int was_empty = 0;
    if (LQ.r == NULL) was_empty = 1;
    LaddAfter(LQ.r, x);
    if (was_empty) LQ.f = LQ.r;
}

int LqueueIsEmpty(LQueue LQ)
{
    if (LQ.f == NULL)
        return 1;
    else return 0;
}

int LdeleteFirst(LPTR &L)
{
    int x = L->data;
    L = L->next;
    return x;
}

int Ldequeue(LQueue &LQ)
{
    if (LqueueIsEmpty(LQ)) {
        cout << "Queue empty.";
        return -1;
    }
    else {
        int is_one_element = 0;
        if (LQ.f == LQ.r)
            is_one_element = 1;
        int x = LdeleteFirst(LQ.f);
        if (is_one_element) LQ.f = LQ.r = NULL;
        return x;
    }
}

//special functions - DLL
void DaddAfter(DPTR &D, int x)
{
    DPTR T = new(dnode);
    T->data = x;
    if (D == NULL)
        D = T;
    else {
        D->right = T;
        T->left = D;
        D = T;
    }
}

void Denqueue(DQueue &DQ, int x)
{
    int was_empty = 0;
    if (DQ.r == NULL) was_empty = 1;
    DaddAfter(DQ.r, x);
    if (was_empty) DQ.f = DQ.r;
}

int DdeleteFirst(DPTR &D)
{
    int x = D->data;
    D = D->right;
    return x;
}

int DqueueIsEmpty(DQueue DQ)
{
    if (DQ.f == NULL)
        return 1;
    else return 0;
}

int Ddequeue(DQueue &DQ)
{
    if (DqueueIsEmpty(DQ)) {
        cout << "Queue empty.";
        return -1;
    }
    else {
        int is_one_element = 0;
        if (DQ.f == DQ.r)
            is_one_element = 1;
        int x = DdeleteFirst(DQ.f);
        if (is_one_element) DQ.f = DQ.r = NULL;
        return x;
    }
}


//[main]
int main()
{
    LQueue LQ;
    LQ.f = NULL;
    LQ.r = NULL;
    DQueue DQ;
    DQ.f = NULL;
    DQ.r = NULL;
    
    int n = 0;
    cout << "Enter: ";
    while (n != -1) {
        cin >> n;
        Denqueue(DQ, n);
    }
    while (!DqueueIsEmpty(DQ))
        cout << Ddequeue(DQ);
}
