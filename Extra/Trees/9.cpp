//Find the maximum sum leaf to root path in a Binary Tree
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
void printArray(vector<int> path)
{
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        (i == path.size()-1) ? cout << "\n" : cout << " -> ";
    }
}

int maxsum = 0;
vector<int> maxpath;
void printPaths(BTPTR T, vector<int> path, int sum)
{
    if (T) {
        path.push_back(T->data);
        if (!T->lchild && !T->rchild) {
            if (maxsum < sum) {
                maxsum = sum;
                maxpath = path;
            }
        }
        printPaths(T->lchild, path, sum+T->data);
        printPaths(T->rchild, path, sum+T->data);
        path.resize(path.size()-1);
    }
}

//MAIN
int main()
{
    BTPTR T = NULL;
    //int input[] = {8,5,9,-1,-1,7,1,-1,-1,12,-1,2,-1,-1,4,-1,11,3,-1,-1,-1};
    int input[] = {10, -2, 8, -1, -1, -4, -1, -1, 7, -1, -1};
    deserialise(T, input);
    printTree(T);
    
    vector<int> path;
    printPaths(T, path, 0);
    cout << "Maximum sum => " << maxsum;
    cout << "\nPath => ";
    printArray(maxpath);
}
