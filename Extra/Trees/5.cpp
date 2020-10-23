//Sum of leaf nodes at minimum level
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
void printMinLevel(BTPTR T)
{
    queue<BTPTR> Q;
    BTPTR D = new btnode;
    D->data = -1;
    D->lchild = D->rchild = NULL;
    Q.push(T);
    Q.push(D);
    int sum = 0;
    
    while (!Q.empty()) {
        T = Q.front();
        Q.pop();
        if (T->data == -1) {
            Q.push(D);
            continue;
        }
        
        if (!T->lchild && !T->rchild) {
            sum = T->data;
            while (1) {
                BTPTR T2 = Q.front();
                Q.pop();
                if (T2->data == -1 || Q.empty()) {
                    cout << "\nSum => " << sum << "\n";
                    return;
                }
                else if (!T2->rchild && !T2->lchild)
                    sum += T2->data;
            }
        }
        else {
            if (T->lchild) Q.push(T->lchild);
            if (T->rchild) Q.push(T->rchild);
        }
    }
}


//MAIN
int main()
{
    BTPTR T = NULL;
    int input[] = {1,2,4,-1,-1,5,8,-1,-1,-1,3,6,-1,9,-1,-1,7,-1,-1};
    deserialise(T, input);
    printTree(T);
    printMinLevel(T);
}
