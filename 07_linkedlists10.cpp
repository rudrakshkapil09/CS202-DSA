//intersecting lists
#include <iostream>
using namespace std;

//Linked List definition
typedef
struct lnode {
    int data;
    struct lnode *next;
} *LPTR;

//function definitions
void rprint(LPTR L)
{
    if (L != NULL) {
        cout << int(L->data) << ".";
        rprint(L->next);
    }
}

int rcount(LPTR L)
{
    if (L == NULL)
        return 0;
    else
        return 1 + rcount(L->next);
}

void addToEnd(LPTR &L, int x)
{
    LPTR T = new(lnode);
    LPTR T2 = L;
    T->data = x;
    T->next = NULL;
    if (L == NULL)
        L = T;
    else {
        while (T2->next != NULL)
            T2 = T2->next;
        T2->next = T;
    }
}

void addToFront(LPTR &L, int x)
{
    LPTR T = new(lnode);
    LPTR T2 = T;
    T->data = x;
    T->next = L;
    if (L != NULL)
        L = T2;
    else
        L = T;
}

void inputLList(LPTR &L)
{
    int n = 1;
    cout << "Enter elements: ";
    while (n != -1) {
        cin >> n;
        if (n == -1)
            break;
        addToEnd(L, n);
    }
}

void raddAfter(LPTR L, int x, int y)
{
    if (L->data != x)
        raddAfter(L->next, x, y);
    else {
        LPTR T = new(lnode);
        LPTR T2 = T;
        T->data = y;
        T->next = L->next;
        L->next = T2;
    }
}

void raddBefore(LPTR &L, int x, int y)
{
    if (L->next->data != x) {
        if (L->data == x) {
            addToFront(L, y);
            return;
        }
        raddBefore(L->next, x, y);
    }
    else {
        LPTR T = new(lnode);
        LPTR T2 = T;
        T->data = y;
        T->next = L->next;
        L->next = T2;
    }
}

int rfindNode(LPTR L, int x)
{
    if (L->data == x)
        return 1;
    else
        return 0 + rfindNode(L->next, x);
}

void deleteNode(LPTR &L, int x)
{
    if (L->next->data != x) {
        if (L->data == x) {
            //delete first node
            LPTR T = L->next;
            L = T;
            return;
        }
        deleteNode(L->next, x);
    }
    else {
        LPTR T = L->next->next;
        L->next = T;
    }
}

//special functions
void makeIntersection(LPTR L1, LPTR L2)
{
    LPTR P = L1->next->next->next;
    LPTR T2 = L2;
    while (T2->next != NULL)
        T2 = T2->next;
    T2->next = P;
}

int findIntersection(LPTR F, LPTR S) {
    int count = 0;
    LPTR TS = S, TF = F;
    while (F->next != NULL && S->next != NULL) {
        F = F->next;
        S = S->next;
    }
    
    while (F != S) {
        (S->next != NULL) ? S = S->next : F = F->next;
        count++;
    }
    S = TS;
    while (count > 0) {
        (S->next != NULL) ? S = S->next : F = F->next;
        count--;
    }
    
    F = TF;
    while (F != S) {
        F = F->next;
        S = S->next;
    }
    return S->data;
    
}

int main()
{
    LPTR L1 = NULL, L2 = NULL;
    inputLList(L1);
    inputLList(L2);
    LPTR F = L1, S = L2;
    makeIntersection(L1,L2);
    cout << "Intersection node => " << findIntersection(F, S) << endl;
}
