//initial functions
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

void addToFront(DPTR &D, int x)
{
    DPTR D1 = new(dnode);
    DPTR D2 = D1;
    D1->data = x;
    D1->right = NULL;
    D1->left = NULL;
    if (D != NULL) {
        D->left = D1;
        D1->right = D;
        D = D2;
    }
    else
        D = D1;
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

void raddBefore(DPTR &D, int x, int y)
{
    if (D->data != x) {
        raddBefore(D->right, x, y);
    }
    else {
        if (D->left != NULL)
            raddAfter(D->left, D->left->data, y);
        else addToFront(D, y);
    }
}

void rdeleteNode(DPTR &D, int x)
{
    if (D->data != x)
        rdeleteNode(D->right, x);
    else {
        if (D->right && D->left) {
            D->left->right = D->right;
            D->right->left = D->left;
        }
        else if (!D->left) {
            D->right->left = NULL;
            D = D->right;
        }
        else if (!D->right) {
            D = D->left;
            D->right = NULL;
        }
    }
}

//MAIN
int main()
{
    DPTR D = NULL;
    inputDList(D);
    rprint(D);
    cout << endl;
    
    addToFront(D, 0);
    rprint(D);
    cout << endl;
    
    raddAfter(D, 8, 80);
    raddBefore(D, 5, 50);
    rprint(D);
    cout << endl;
    
    rdeleteNode(D, 3);
    rdeleteNode(D, 0);
    rdeleteNode(D, 10);
    rprint(D);
    cout << endl;
}
