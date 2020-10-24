//quick sort on doubly linked list
#include <iostream>
using namespace std;

//struct definition
typedef
struct dnode {
    struct dnode *left;
    int data;
    struct dnode *right;
} *DPTR;

//functions
void rprint(DPTR D)
{
    if (D != NULL) {
        cout << int(D->data) << ", ";
        rprint(D->right);
    }
}

void addToEnd(DPTR &D, int x)
{
    DPTR D1 = new(dnode);
    DPTR D2 = D;
    D1->data = x;
    D1->right = NULL;
    D1->left = NULL;
    if (D == NULL)
        D = D1;
    else {
        while (D2->right != NULL)
            D2 = D2->right;
        D2->right = D1;
        D1->left = D2;
    }
}

void inputDList(DPTR &D)
{
    int n = 1;
    cout << "Enter elements: ";
    while (1) {
        cin >> n;
        if (n == -1)
            break;
        addToEnd(D, n);
    }
}

//special functions
void swap(int &x, int &y)
{
    int t = x;
    x = y;
    y = t;
}

DPTR partition(DPTR D, DPTR S)
{
    int p = D->data;
    DPTR L = D->right;
    DPTR H = S;
    while (L != NULL && L != H && H != L->left) {
        while (L->data < p && L->right != NULL) L = L->right;
        while (H->data > p) H = H->left;
        if (H->right != L)
            swap(L->data, H->data);
    }
    swap(D->data, H->data);
    return H;
}

void quickSortDL(DPTR D, DPTR S)
{
    DPTR J = NULL;
    if (D != NULL && D != S && S != D->left) {
        J = partition(D, S);
        quickSortDL(D, J->left);
        quickSortDL(J->right, S);
    }
}

int main()
{
    DPTR D = NULL, LAST = NULL;
    inputDList(D);
    LAST = D;
    while (LAST != NULL && LAST->right != NULL)
        LAST = LAST->right;
    quickSortDL(D, LAST);
    rprint(D);
}
