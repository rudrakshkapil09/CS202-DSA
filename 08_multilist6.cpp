//Creating a cross connected linked lists
#include <iostream>
using namespace std;

//Linked List definition
typedef
struct lnode {
    int data;
    struct lnode *rptr;
    struct lnode *next;
} *LPTR;
//special functions

void connectNodes(LPTR F, LPTR S, int x, int y)     //connect x to y
{
    while (F->data != x)
        F = F->next;
    while (S->data != y)
        S = S->next;
    F->rptr = S;
}

void addToEnd(LPTR &L, int x)
{
    LPTR T = new(lnode);
    LPTR T2 = L;
    T->data = x;
    T->rptr = NULL;
    T->next = NULL;
    if (L == NULL)
        L = T;
    else {
        while (T2->next != NULL)
            T2 = T2->next;
        T2->next = T;
    }
}

void rprint(LPTR L)
{
    if (L != NULL) {
        cout << int(L->data) << " ";
        if (L->rptr != NULL)
            cout << "(" << L->rptr->data << ") ";
        rprint(L->next);
    }
}

//[MAIN]
int main()
{
    LPTR L = NULL, F = NULL, S = NULL;
    int x = 0, y = 0;
    char choice = '0';
    while (choice != 'Q' && choice != 'q') {
        cout << "\nA) Add to end of list.\nR) Add a random pointer\nP) Print network\nQ) Quit\nEnter choice => ";
        cin >> choice;
        switch (choice) {
            case 'A': case 'a':
                cout << "Enter element to add to end: ";
                cin >> x;
                addToEnd(L, x);
                F = L; S = L;
                break;
            case 'R': case 'r':
                cout << "Enter elements to connect (x to y): ";
                cin >> x >> y;
                connectNodes(F, S, x, y);
                break;
            case 'P': case 'p':
                rprint(L);
                cout << endl;
                break;
            case 'Q': case 'q':
                break;
        }
    }
}
