//Longest consecutive sequence in Binary tree
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
vector<int> largest = {};
void checkSequence(BTPTR T, vector<int> seq, int value)
{
    if (T) {
        if (T->data == value) {
            seq.push_back(T->data);
            if (largest.size() < seq.size())
                largest = seq;
        }
        else {
            seq.clear();
            seq.push_back(T->data);
        }
        checkSequence(T->lchild, seq, T->data+1);
        checkSequence(T->rchild, seq, T->data+1);
    }
}


//MAIN
int main()
{
    BTPTR T = NULL;
    vector<int> sequence;
    int input[] = {6, -1, 9, 7, -1, -1, 10, -1, 11, -1, -1};
    //int input[] = {1, 2, 3, -1, -1, -1, 4, 5, -1, -1, 6, 7, -1, -1, -1};
    deserialise(T, input);
    printTree(T);
    
    checkSequence(T, sequence, T->data);
    cout << "Longest sequence => ";
    for (int i = 0; i < largest.size(); i++)
        cout << largest[i] << " ";
    cout << "\n";
    return 0;
}

