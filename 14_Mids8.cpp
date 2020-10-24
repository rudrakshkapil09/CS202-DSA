//5.c) Interleaving first half of queue with second half
#include <iostream>
using namespace std;

//stack & queue definitions
typedef
struct lnode {
    int data;
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
void addToFront(LPTR &L, int B)
{
    LPTR T = new(lnode);
    T->data = B;
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

void Lpush(LST &s1, int B)
{
    addToFront(s1.top, B);
}

int Lpop(LST &s1)
{
    if (LstackIsEmpty(s1)) {
        cout << "Stack empty.";
        return NULL;
    }
    else {
        int B = s1.top->data;
        s1.top = deleteFirst(s1.top);
        return B;
    }
}

int LTop(LST s1)
{
    if (LstackIsEmpty(s1)) {
        return NULL;
    }
    else return s1.top->data;
}


//LQueue functions
void LaddAfter(LPTR &L, int B)
{
    LPTR T = new(lnode);
    T->data = B;
    if (L == NULL) L = T;
    else {
        L->next = T;
        L = T;
    }
}

void Lenqueue(LQueue &LQ, int B)
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

int LdeleteFirst(LPTR &L)
{
    int B = L->data;
    L = L->next;
    return B;
}

int Ldequeue(LQueue &LQ)
{
    if (LqueueIsEmpty(LQ)) {
        cout << "Queue empty.";
        return NULL;
    }
    else {
        int is_one_element = 0;
        if (LQ.f == LQ.r)
            is_one_element = 1;
        int B = LdeleteFirst(LQ.f);
        if (is_one_element) LQ.f = LQ.r = NULL;
        return B;
    }
}

//special function
void interLeave(LQueue Q, LST S, int mid)
{
    int i = 0;
    for (i = 0; i < mid; i++)
        Lpush(S, Ldequeue(Q));
    while (!LstackIsEmpty(S))
        Lenqueue(Q, Lpop(S));
    for (i = 0; i < mid; i++)
        Lenqueue(Q, Ldequeue(Q));
    for (i = 0; i < mid; i++)
        Lpush(S, Ldequeue(Q));
    while (!LstackIsEmpty(S)) {
        Lenqueue(Q, Lpop(S));
        Lenqueue(Q, Ldequeue(Q));
    }
    
    cout << "Output => ";
    while (!LqueueIsEmpty(Q))
        cout << Ldequeue(Q) << " ";
}

//MAIN
int main()
{
    LQueue Q;
    LST S;
    S.top = Q.f = Q.r = NULL;
    
    int size = 0, i = 11;
    for (;i <= 20; i++, size++)
        Lenqueue(Q, i);
    
    interLeave(Q, S, size/2);
    cout << endl;
}
