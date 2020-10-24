//biotonic saga
#include <iostream>
using namespace std;

//struct definition
typedef
struct dnode {
    int data;
    struct dnode *right;
    struct dnode *left;
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

void raddAfter(DPTR D, int x, int y)
{
    if (D->data != x) {
        raddAfter(D->right, x, y);
    }
    else {
        if (D->right != NULL) {
            DPTR D1 = new(dnode);
            D1->data = y;
            D->right->left = D1;
            D1->right = D->right;
            D->right = D1;
            D1->left = D;
        }
        else addToEnd(D, y);
    }
}

void rdeleteFirst(DPTR &D)
{
    D->right->left = NULL;
    D = D->right;
}

//special function
void biotonicSaga(DPTR &D, DPTR S)
{
    if (D->left != S && D != S) {
        while (S->data > D->data)
            S = S->left;
        raddAfter(D, S->data, D->data);
        biotonicSaga(D->right, S);
    }
    while (D->data >= D->right->data) {
        rdeleteFirst(D);
    }
}

//dptr return D changed to void

//[MAIN]
int main()
{
    DPTR D = NULL, S = NULL;
    inputDList(D);
    S = D;
    while (S->right != NULL)
        S = S->right;
    D = biotonicSaga(D, S);
    rprint(D);
}
