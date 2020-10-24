//program to segregate then sort -ve and +ve numbers
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
LPTR sortedInsert(LPTR &L, int n)
{
    if (L == NULL) {                        //first node
        L = new(lnode);
        L->next = NULL;
        L->data = n;
    }
    
    else if (L->data >= n)   //add to front
        addToFront(L, n);
    
    else if (L->data < n) {  //add in the middle
        LPTR L1 = L;
        LPTR L2 = new(lnode);
        L2->data = n;
        L2->next = NULL;
        
        if (L1->next == NULL)
            return sortedInsert(L1->next, n);
        
        while (L1->next->data <= n) {
            L1 = L1->next;
            if (L1->next == NULL)
                return sortedInsert(L1->next, n);
        }
        L2->next = L1->next;
        L1->next = L2;
    }
    return L;
}

/*
 1 -2 -3 4 5 -6
 */
//[MAIN]
int main()
{
    LPTR L1 = nullptr, T, T2, S = NULL;
    cout << "Enter the list (end with -1)\n";
    inputLList(L1);
    int x;
    T2 = L1;
    T = L1;
    
    while (T->next != nullptr)    //T is last node
        T = T->next;
    
    while (T2 != T) {       //move T2 till T
        if (T2->data > 0) {
            x = T2->data;
            addToEnd(L1, x);
            deleteNode(L1, x);
        }
        T2 = T2->next;
    }
    
    //at this point -2 -3 1 4 5
    rprint(L1);
    cout << endl;
    
    addToEnd(S, L1->data);
    L1 = L1->next;
    while (L1 != NULL) {
        sortedInsert(S, L1->data);
        L1 = L1->next;
    }
    rprint(S);
}
