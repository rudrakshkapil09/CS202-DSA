//program to segregate even and odd numbers
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

//[MAIN]
int main()
{
    LPTR L1 = nullptr, T, T2;
    cout << "Enter the list (end with -1)\n";
    inputLList(L1);
    int x;
    T2 = L1;
    T = L1;
    
    while (T->next != nullptr)    //T is last node
        T = T->next;
    
    while (T2 != T) {       //move T2 till T
        if (T2->data % 2 != 0) {
            x = T2->data;
            addToEnd(T2, x);
            deleteNode(L1, x);
        }
        T2 = T2->next;
    }
    
    rprint(L1);
}
