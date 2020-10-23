//Find if there is a pair in root to a leaf path with sum equals to root’s data
#include <iostream>
#include <queue>
#include <set>
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
int findPairs(BTPTR T, set<int> m, int root)
{
    if (T) {
        int rem = root - T->data;
        if (m.find(rem) != m.end()) {
            cout << rem << " + " << T->data << " = " << root << "\n";
            return 1;
        }
        
        m.insert(T->data);
        int res = findPairs(T->rchild, m, root) || findPairs(T->lchild, m, root);
        m.erase(T->data);
        return res;
    }
    return 0;
}

//MAIN
int main()
{
    BTPTR T = NULL;
    int input[] = {8,5,9,-1,-1,7,1,-1,-1,12,-1,2,-1,-1,4,-1,11,3,-1,-1,-1};
    deserialise(T, input);
    printTree(T);
    
    set<int> m;
    if(!findPairs(T->lchild, m, T->data) && !findPairs(T->rchild, m, T->data))
        cout << "No pairs :(\n";
    
}
