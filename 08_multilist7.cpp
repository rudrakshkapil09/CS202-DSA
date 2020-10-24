//deleting duplicates - unsorted
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
        cout << int(L->data) << " ";
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

int isFound(LPTR L, int x)
{
    while (L != NULL) {
        if (L->data == x)
            return 1;
        else L = L->next;
    }
    return 0;
}

void deleteNode(LPTR &L, int x)
{
    if (L->next->data != x) {
        deleteNode(L->next, x);
    }
    else {
        LPTR T = L->next->next;
        L->next = T;
    }
}

//special functions

int rcompare(LPTR L1, LPTR L2, int &data)
{
    while (L2 != NULL) {
        if (L1->data == L2->data) {
            data = L1->data;
            return 1;
        }
        else L2 = L2->next;
    }
    return 0;
}

void rdeleteDuplicates(LPTR &L)
{
    int data = 0;
    if (L == NULL)
        return;
    else {
        if (rcompare(L, L->next, data)) {
            deleteNode(L, data);
            rdeleteDuplicates(L);
        }
        rdeleteDuplicates(L->next);
    }
}



//[MAIN]
int main()
{
    LPTR L1 = NULL;
    
    cout << "Enter the lists (end with -1)\n";
    inputLList(L1);
    rdeleteDuplicates(L1);
    cout << "Duplicates deleted:\n";
    rprint(L1);
    cout << endl;
}
