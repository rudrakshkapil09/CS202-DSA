//checking if a tree is a BST
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

//special functions
int checkBST(BSTPTR T)
{
    if (T->lchild != NULL && T->rchild != NULL) {
        if (T->data > T->rchild->data || T->data < T->lchild->data)
            return 0;
        else return (checkBST(T->lchild) && checkBST(T->rchild));
    }
    else return 1;
}

void inputNotBST(BSTPTR &T)
{
    T = new(bstnode);
    T->data = 6;
    T->rchild = new(bstnode);
    T->rchild->data = 8;
    T->lchild = new(bstnode);
    T->lchild->data = 4;
    T->rchild->lchild = new(bstnode);
    T->rchild->lchild->data = 9;
    T->rchild->rchild = new(bstnode);
    T->rchild->rchild->data = 7;
}

//[MAIN]
// 6 8 9 7 4 2 5 3 -1
int main()
{
    BSTPTR T = NULL;
    //inputTree(T);
    inputNotBST(T);
    if (checkBST(T))
        cout << "Tree is a BST.\n";
    else
        cout << "Not a BST.\n";
}
