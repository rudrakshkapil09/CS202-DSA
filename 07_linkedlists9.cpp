//loop
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
void makeLoop(LPTR L)
{
    LPTR P = L->next->next->next;
    LPTR T2 = L;
    while (T2->next != NULL)
        T2 = T2->next;
    T2->next = P;
}

int checkLoop(LPTR F, LPTR S)
{
    while (F != S && F->next != NULL && S != NULL) {
        F = F->next->next;
        S = S->next;
        if (F == S)
            return 1;
    }
    return 0;
}

int findStart(LPTR F, LPTR S)
{
    LPTR T = S;         //T is at start of list
    while (F != S) {
        F = F->next->next;
        S = S->next;
    }
    S = T;                  //reset S
    while (F->next != S) {      //move till this condition
        F = F->next;
        S = S->next;
    }
    return S->data;
}

int getLength(LPTR F, LPTR S)
{
    int count = 1;
    while (F != S) {
        F = F->next->next;
        S = S->next;
    }
    S = S->next;
    while (F != S) {
        S = S->next;
        count++;
    }
    return count;
}

int main()
{
    LPTR L = NULL;
    inputLList(L);
    makeLoop(L);
    LPTR F = L->next, S = L;
    
    if (checkLoop(F, S))
        cout << "Loop is present at node " << findStart(F,S) << ". Length => " << getLength(F, S) << endl;
    else
        cout << "No loop.\n";
}
