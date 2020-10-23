//Print the longest leaf to leaf path in a Binary tree
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
int height(BTPTR T, BTPTR &K, int &ans, int &lh, int &rh)
{
    if (!T) return 0;
    
    int left = height(T->lchild, K, ans, lh, rh);
    int right = height(T->rchild, K, ans, lh, rh);
    
    if (ans < 1+left+right) {
        ans = 1+left+right;
        K = T;
        lh = left;
        rh = right;
    }
    
    return 1 + max(left, right);
}

void printArray(vector<int> path, int f)
{
    if (!f) {
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i != path.size()-1)
                cout << " -> ";
        }
    }
    else {
        for (int i = path.size()-1; i >= 0; i--) {
            cout << path[i];
            if (i != 0)
                cout << " -> ";
        }
    }
}

void printPaths(BTPTR T, vector<int> path, int max, int &f)
{
    if (T) {
        path.push_back(T->data);
        if (!T->lchild && !T->rchild) {
            if (path.size() == max && f >= 0) {
                printArray(path, f);
                f = -1;
            }
        }
        else {
            printPaths(T->lchild, path, max, f);
            printPaths(T->rchild, path, max, f);
        }
    }
}

int diameter(BTPTR T)
{
    int ans = 0, lh = 0, rh = 0, f = 1;
    BTPTR K;
    height(T, K, ans, lh, rh);
    
    vector<int> path;
    printPaths(K->lchild, path, lh, f);
    cout << " -> " << K->data << " -> ";
    f = 0;
    path.clear();
    printPaths(K->rchild, path, rh, f);
    cout << "\n";
    return ans;
}

//MAIN
int main()
{
    BTPTR T = NULL, X;
    int input[] = {1,2,4,-1,8,9,-1,-1,-1,5,6,-1,-1,7,-1,-1,3,-1,11,-1,-1};
    deserialise(T, input);
    printTree(T);
    
    int ans = diameter(T);
    cout << "Diameter = " << ans << "\n";
}
