//Longest path with same values in binary tree
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

//Special Functions
int checkLongest(BTPTR T, int &len)
{
    if (T) {
        int left = checkLongest(T->lchild, len);
        int right = checkLongest(T->rchild, len);
        
        pair<int, int> maxes;
        if (T->lchild && T->data == T->lchild->data)
            maxes.first += left + 1;
        if (T->rchild && T->data == T->rchild->data)
            maxes.second += right + 1;
        
        len = max(len, maxes.first+maxes.second);
        return max(maxes.first, maxes.second);
    }
    return 0;
}


//MAIN
int main()
{
    BTPTR T = NULL;
    vector<int> sequence;
    //int input[] = {2, 7, 1, -1, -1, 1, -1, -1, 2, -1, 2, -1, -1};
    int input[] = {4, 4, 4, -1, -1, 9, -1, -1, 4, -1, 5, -1, -1};
    deserialise(T, input);
    printTree(T);
    
    int max = 0;
    checkLongest(T, max);
    cout << "Maximum => " << max << "\n";
}

