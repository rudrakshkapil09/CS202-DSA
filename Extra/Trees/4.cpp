//Convert a binary tree to its mirror
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
void mirror(BTPTR T)
{
    if (T) {
        mirror(T->lchild);
        mirror(T->rchild);
        swap(T->lchild, T->rchild);
    }
}

//MAIN
int main()
{
    BTPTR T = NULL;
    int input[] = {1, 3, -1, -1, 2, 5, -1, -1, 4, -1, -1};
    deserialise(T, input);
    cout << "Original:\n";
    printTree(T);
    mirror(T);
    cout << "Mirror:\n";
    printTree(T);
}

