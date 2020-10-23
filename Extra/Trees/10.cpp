//Closest leaf to a given node in Binary Tree
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
void traverseSubTree(BTPTR T, int dist, int &mindist)
{
    if (T) {
        if (!T->lchild && !T->rchild) {
            mindist = dist;
            return;
        }
        traverseSubTree(T->lchild, dist+1, mindist);
        traverseSubTree(T->rchild, dist+1, mindist);
    }
}

int traverseTree(BTPTR T, BTPTR X, int &mindist)
{
    if (!T) return -1;
    if (T == X) return 0;
    
    int l = traverseTree(T->lchild, X, mindist);
    if (l != -1) {  //left side has X
        traverseSubTree(T->rchild, l+2, mindist);
        return l+1;
    }
    
    int r = traverseTree(T->rchild, X, mindist);
    if (r != -1) {  //right side has X
        traverseSubTree(T->lchild, r+2, mindist);
        return r+2;
    }
    
    return -1;
}

int findMin(BTPTR T, BTPTR X)
{
    int mindist1 = 0, mindist2 = 0;
    traverseSubTree(X, 0, mindist1);
    traverseTree(T, X, mindist2);
    
    return (mindist1 < mindist2) ? mindist1 : mindist2;
}

//MAIN
int main()
{
    BTPTR T = NULL, X;
    int input[] = {10, 12, -1, -1, 13, 14, 21, 1, -1, -1, 2, -1, -1, 22, 3, -1, -1, 4, -1, -1, 15, 23, 5, -1, -1, 6, -1, -1, 24, 7, -1, -1, 8, -1, -1};
    deserialise(T, input);
    printTree(T);
    X = T->rchild;
    
    cout << "Shortest distance to " << X->data << " => " << findMin(T, X) << "\n";
}
