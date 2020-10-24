//insertion sort
#include <iostream>
using namespace std;

//struct definition
typedef
struct lnode {
    int data;
    struct lnode *next;
} *LPTR;

//function defintions
void rprint(LPTR L)
{
    if (L != NULL) {
        cout << L->data << ".";
        rprint(L->next);
    }
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

void inputLList(LPTR &L)
{
    int n = 1;
    cout << "Enter elements: ";
    while (n) {
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

void raddBefore(LPTR L, int x, int y)
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
void sortedInsert(LPTR &L, int n)
{
    LPTR T = L;
    if (L->next) {
        if (n < T->data)
            raddBefore(L, T->data, n);
        else {
            while (n > T->next->data) {
                T = T->next;
                if (T->next == NULL)
                    break;
            }
            if (T->next == NULL)
                addToEnd(L, n);
            else raddAfter(L, T->data, n);
        }
        
    }
    else {
        if (n < L->data) {
            LPTR T2 = new(lnode);
            T2->data = n;
            T2->next = L;
            L = T2;
        }
        else if (n > L->data)
            addToEnd(L, n);
    }
}

//[MAIN]
int main ()
{
    LPTR L = NULL, S = NULL;
    inputLList(L);
    addToEnd(S, L->data);
    while (L != NULL)
    {
        sortedInsert(S, L->data);
        L = L->next;
    }
    rprint(S);
}
