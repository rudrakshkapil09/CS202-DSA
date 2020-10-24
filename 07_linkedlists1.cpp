//find union and intersection of 2 sorted lists
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
int isFound(LPTR L, int x)
{
    while (L != NULL) {
        if (L->data == x)
            return 1;
        else L = L->next;
    }
    return 0;
}


void setUnion(LPTR L1, LPTR L2, LPTR &U)
{
    while (L1 != NULL) {
        if (!isFound(U, L1->data))
            addToEnd(U, L1->data);
        L1 = L1->next;
    }
    while (L2 != NULL) {
        if (!isFound(U, L2->data))
            addToEnd(U, L2->data);
        L2 = L2->next;
    }
}

void rsetInter(LPTR L1, LPTR L2, LPTR &I)
{
    if (L1 != NULL) {
        if (isFound(L2, L1->data) && !isFound(I, L1->data)) {
            addToEnd(I, L1->data);
        }
        rsetInter(L1->next, L2, I);
    }
    return;
}

//[MAIN]
int main()
{
    LPTR L1 = NULL, L2 = NULL, U = NULL, I = NULL;
    int n = 1;
    
    cout << "Enter first sorted list (end with -1): ";
    while (n) {
        cin >> n;
        if (n == -1)
            break;
        addToEnd(L1, n);
    }
    n = 1;
    cout << "Enter second sorted list (end with -1): ";
    while (n) {
        cin >> n;
        if (n == -1)
            break;
        addToEnd(L2, n);
    }
    
    cout << "\nIntersection => ";
    rsetInter(L1, L2, I);           //not setting anything - done
    rprint(I);                      //not printing - done with pass by ref
    
    cout << "\nUnion => ";
    setUnion(L1, L2, U);
    rprint(U);
    
    cout << endl;
}
