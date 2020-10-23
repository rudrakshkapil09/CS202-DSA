//largest BST subtree in a binary tree
#include <iostream>
#include <queue>
using namespace std;

//tree defintion
typedef
struct btnode {
    struct btnode *lchild;
    int data;
    int inn;                    //in order number
    struct btnode *rchild;
} *BTPTR;

struct subtree {
    int max;
    int min;
    int is_BST;
    BTPTR T;
};

//tree printing
int innindex = 1;
void setInorderIndex(BTPTR T)
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
void printAsItIs(queue<BTPTR> Q)
{
    if (!Q.empty()) {
        BTPTR T = Q.front();
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

void printTree(BTPTR T)
{
    queue<BTPTR> Q;
    BTPTR D = new(btnode);        //Dummy
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

//creating tree
int deserialise(BTPTR &T, int data[])
{
    static int dataindex = 0;
    int ch = data[dataindex++];
    if (ch != -1) {
        T = new(btnode);
        T->data = ch;
        T->lchild = T->rchild = NULL;
        deserialise(T->lchild, data);
        deserialise(T->rchild, data);
    }
    return dataindex;
}

//special functions
subtree solution;
struct subtree checkBST(BTPTR T)
{
    if (!T)
        return {INT_MIN, INT_MAX, true, NULL};
    if (!T->lchild && !T->rchild)
        return {T->data, T->data, true, T};
    
    subtree l = checkBST(T->lchild);
    subtree r = checkBST(T->rchild);
    
    subtree ret;
    if (l.is_BST && r.is_BST && l.max < T->data && r.min > T->data) {
        ret.min = min(l.min, min(T->data, r.min));
        ret.max = max(r.max, max(T->data, l.max));
        
        ret.is_BST = 1;
        solution.T = T;
        return ret;
    }
    
    ret.is_BST = 0;
    return ret;
}

//MAIN
int main()
{
    BTPTR T = NULL;
    int input[] = {50, 10, 5, -1, -1, 20, -1, -1, 60, 55, 45, -1, -1, -1, 70, 65, -1, -1, 80, -1, -1};
    deserialise(T, input);
    printTree(T);
    
    checkBST(T);
    printTree(solution.T);
    
}

