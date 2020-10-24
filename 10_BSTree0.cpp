//basic operations - BST
#include <iostream>
using namespace std;

typedef
struct bstnode {
    struct bstnode *lchild;
    int data;
    int inn;                    //in order number
    struct bstnode *rchild;
} *BSTPTR;

//tree functions
void insertNode(BSTPTR &T, int k)
{
    if (T != NULL) {
        if (k < T->data) insertNode(T->lchild, k);
        else if (k > T->data) insertNode(T->rchild, k);
        else cout << "Error: Duplicate data.\n";
    }
    else {
        T = new(bstnode);
        T->inn = 0;
        T->data = k;
        T->rchild = T->lchild = NULL;
    }
}

void inputTree(BSTPTR &T)
{
    int num;
    cout << "Enter elements of tree (end -> -1):\n";
    while (1) {
        cin >> num;
        if (num == -1) break;
        insertNode(T, num);
    }
}

int innindex = 1;
void setInorderIndex(BSTPTR T)
{
    if (T != NULL) {
        setInorderIndex(T->lchild);
        T->inn = innindex++;
        setInorderIndex(T->rchild);
    }
}

int getMax(BSTPTR T)                //not working
{
    if (T->rchild) return getMax(T->rchild);
    else return T->data;
}

int getMin(BSTPTR T)                //not working
{
    if (T->lchild) return getMin(T->lchild);
    else return T->data;
}

void printSort(BSTPTR T)
{
    if (T != NULL) {
        printSort(T->lchild);
        cout << T->data << ".";
        printSort(T->rchild);
    }
}

int nodeIsFound(BSTPTR T, int k)
{
    if (T != NULL) {
        if (T->data == k)
            return 1;
        else if (T->data < k)
            return nodeIsFound(T->rchild, k);
        else
            return nodeIsFound(T->lchild, k);
    }
    else return 0;
}

//[MAIN]
// 6 8 9 7 4 2 5 3 -1
int main()
{
    BSTPTR T = NULL;
    inputTree(T);
    printSort(T);
    cout << endl;
    if (nodeIsFound(T, 8))
        cout << "8 Found.\n";
    else cout << "8 Not found.\n";
    cout << "Min: " << getMin(T) << endl << "Max: " << getMax(T);
    cout << endl;
    return 0;
}
