// Minor question 5 - plants pesticide question

#include <iostream>
using namespace std;

//structure definitions
typedef
struct plantnode {
    struct plantnode *left;
    int pesticide;
    int index;
    struct plantnode *right;
} *PPTR;

void addToEnd(PPTR &D, int x, int y)
{
    PPTR D1 = new(plantnode);
    PPTR D2 = D;
    D1->pesticide = x;
    D1->index = y;
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

void inputDList(PPTR &D)
{
    int n = 1, id;
    cout << "Enter elements (amt_id): ";
    while (1) {
        cin >> n;
        if (n == -1)
            break;
        cin >> id;
        addToEnd(D, n, id);
    }
}

//special functions
int checkSort(PPTR P)
{
    while (P != NULL) {
        if (P->pesticide > P->left->pesticide) {
            return 0; break;
        }
        P = P->right;
    }
    return 1;
}

int countPlants(PPTR P)
{
    if (P == NULL)
        return 0;
    else return 1 + countPlants(P->right);
}

void rprintPlants(PPTR P)
{
    if (P != NULL) {
        cout << "(" << P->pesticide << "." << P->index << ")  ";
        rprintPlants(P->right);
    }
}

void rkillPlants(PPTR P)
{
    if (P != NULL) {
        if (P->pesticide > P->left->pesticide) { //delete
            if (P->right == NULL) {
                P->left->right = NULL;
                P->left = NULL;
                rkillPlants(P->right);
            }
            else {
                P->left->right = P->right;
                P->right->left = P->left;
                rkillPlants(P->right->right);
            }
        }
        else rkillPlants(P->right);
    }
}

void checkDays(PPTR P)
{
    int count = 0;
    while (!checkSort(P->right)) {
        cout << "After day " << count << " " << countPlants(P) << " plants are alive:\n";
        rprintPlants(P);
        cout << endl;
        rkillPlants(P->right);
        count++;
    }
    cout << "After day " << count << " the plants stop dying.\n";
}


//6 1 5 2 8 3 4 4 7 5 10 6 9 7 -1

int main()
{
    PPTR P = NULL;
    inputDList(P);
    checkDays(P);
    return 0;
}

