//counting leaf & non-leaf nodes
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

int inputTree(BSTPTR &T)
{
    int num, i = 0;
    cout << "Enter elements of tree (end -> -1):\n";
    while (1) {
        cin >> num;
        if (num == -1) break;
        insertNode(T, num);
        i++;
    }
    return i;
}

//special functions
int countLeaf(BSTPTR T)
{
    if (T) {
        if (T->lchild == NULL && T->rchild == NULL)
            return 1;
        else
            return countLeaf(T->lchild) + countLeaf(T->rchild);
    }
    else return 0;
}

//[MAIN]
// 6 8 9 7 4 2 5 3 -1
int main()
{
    BSTPTR T = NULL;
    int total = inputTree(T);
    int leaf = countLeaf(T);
    cout << "Number of leaf nodes => " << leaf << endl;
    cout << "Number of non-leaf nodes => " << total-leaf << endl;
    return 0;
}
