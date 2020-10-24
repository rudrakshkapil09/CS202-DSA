//quick sort on singly linked list
#include <iostream>
using namespace std;

//struct definition
typedef
struct lnode {
    int data;
    struct lnode *next = NULL;
} *LPTR;


//functions
void rprint(LPTR L)
{
    if (L != NULL) {
        cout << int(L->data) << ", ";
        rprint(L->next);
    }
}

void addToEnd(LPTR &L, int x)
{
    LPTR D1 = new(lnode);
    LPTR D2 = L;
    D1->data = x;
    D1->next = NULL;
    if (L == NULL)
        L = D1;
    else {
        while (D2->next != NULL)
            D2 = D2->next;
        D2->next = D1;
    }
}

void inputDList(LPTR &L)
{
    int n = 1;
    cout << "Enter elements: ";
    while (1) {
        cin >> n;
        if (n == -1)
            break;
        addToEnd(L, n);
    }
}

//special functions
LPTR getLeft(LPTR L, LPTR N)
{
    if (L == N) return L;
    while (L->next != N)
        L = L->next;
    return L;
}

void swap(int &x, int &y)
{
    int t = x;
    x = y;
    y = t;
}

LPTR partition(LPTR D, LPTR S)
{
    int p = D->data;
    LPTR L = NULL;
    L = D->next;
    LPTR H = S;
    LPTR H2 = NULL;
    while (L != NULL && L != H) {
        LPTR L2 = getLeft(D, L);
        if (H == L2) break;
        while (L->data < p && L->next) L = L->next;
        while (H->data > p) {
            H2 = getLeft(D, H);
            H = H2;
        }
        if (H->next != L)
            swap(L->data, H->data);
    }
    swap(D->data, H->data);
    return H;
}

void quickSortDL(LPTR L, LPTR S)
{
    LPTR J = NULL, JL = NULL;
    if (L != NULL && L != S && S->next != L) {
        J = partition(L, S);
        JL = getLeft(L, J);
        quickSortDL(L, JL);        //left function
        quickSortDL(J->next, S);
    }
}

//MAIN
/*
 30 2 4 20 5 6 1 -1
 */
int main()
{
    LPTR L = NULL, LAST = NULL;
    inputDList(L);
    LAST = L;
    while (LAST != NULL && LAST->next != NULL)
        LAST = LAST->next;
    quickSortDL(L, LAST);
    rprint(L);
}
