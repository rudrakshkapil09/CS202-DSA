//All possible ways of forming a BST
#include <iostream>
#include <queue>
using namespace std;

//tree defintion
typedef
struct bstnode {
    struct bstnode *lchild;
    int data;
    int inn;                    //in order number
    struct bstnode *rchild;
} *BSTPTR;

//tree printing
int innindex = 1;
void setInorderIndex(BSTPTR T)
{
    if (T != NULL) {
        setInorderIndex(T->lchild);
        T->inn = innindex++;
        setInorderIndex(T->rchild);
    }
}

void setSpaces(int n1, int n2)
{
    for (int i = n2 + 1; i < n1; i++)
        cout << " ";
}

int previnn = 0;
void printAsItIs(queue<BSTPTR> Q)
{
    if (!Q.empty()) {
        BSTPTR T = Q.front();
        Q.pop();
        if (T->data == -1 && !Q.empty()) {
            cout << "\n";
            Q.push(T);
            previnn = 0;
        }
        else {
            if (T->data != -1) {
                setSpaces(T->inn, previnn);
                cout << T->data;
                previnn = T->inn;
            }
            if (T->lchild) Q.push(T->lchild);
            if (T->rchild) Q.push(T->rchild);
        }
        printAsItIs(Q);
    }
}

void printTree(BSTPTR T)
{
    queue<BSTPTR> Q;
    BSTPTR D = new(bstnode);        //Dummy
    D->lchild = D->rchild = NULL;
    D->data = -1;
    
    cout << "Tree:\n";
    setInorderIndex(T);
    Q.push(T);
    Q.push(D);
    printAsItIs(Q);
    previnn = 0;
    innindex = 1;
    cout << "\n–––––––––––––––\n";
}

//creation
int checkTree(BSTPTR T1, BSTPTR T2)
{
    if (T1 && T2) {
        if (T1->data == T2->data)
            return checkTree(T1->lchild, T2->lchild) && checkTree(T1->rchild, T2->rchild);
        else return 0;
    }
    return 1;
}

void printArray(int input[])
{
    for (int i = 0; i < 5; i++)
        cout << input[i] << " ";
    cout << "\n";
}

BSTPTR newNode(int x)
{
    BSTPTR T = new bstnode;
    T->lchild = T->rchild = NULL;
    T->data = x;
    return T;
}

void insertNode(BSTPTR &T, int x)
{
    if (T) {
        if (x < T->data)
            insertNode(T->lchild, x);
        else insertNode(T->rchild, x);
    }
    else T = newNode(x);
}

void createFromArray(BSTPTR O, int input[])
{
    BSTPTR T = NULL;
    for (int i = 0; i < 5; i++)
        insertNode(T, input[i]);
    
    if (checkTree(O, T)) {
        printArray(input);
    }
}

void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void permute(BSTPTR O, int *input, int l, int r)
{
    if (l == r)
        createFromArray(O, input);
    else {
        for (int i = l; i <= r; i++) {
            swap(input+l, input+i);
            permute(O, input, l+1, r);
            swap(input+l, input+i);
        }
    }
}

//MAIN
int main()
{
    BSTPTR O = NULL;
    int input[] = {9, 5, 7, 15, 12};
    
    O = newNode(9);
    O->lchild = newNode(5);
    O->lchild->rchild = newNode(7);
    O->rchild = newNode(15);
    O->rchild->lchild = newNode(12);
    
    printTree(O);
    
    cout << "All ways of formation: \n";
    permute(O, input, 1, 4);
}
