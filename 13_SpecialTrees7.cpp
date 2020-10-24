//Digital Trees
#include <iostream>
#include <iomanip>
using namespace std;

//tree node definition
typedef
struct dtnode {
    struct dtnode *lchild;
    string data;
    int inn = 0;
    struct dtnode *rchild;
} *DTPTR;

//singly linked list as a queue & stack definitions
typedef
struct lnode {
    DTPTR bstptr;
    struct lnode *next;
} *LPTR;

struct LQueue {
    LPTR f;
    LPTR r;
};

//LQueue functions
void LaddAfter(LPTR &L, DTPTR B)
{
    LPTR T = new(lnode);
    T->bstptr = B;
    if (L == NULL) L = T;
    else {
        L->next = T;
        L = T;
    }
}

void Lenqueue(LQueue &LQ, DTPTR B)
{
    int was_empty = 0;
    if (LQ.r == NULL) was_empty = 1;
    LaddAfter(LQ.r, B);
    if (was_empty) LQ.f = LQ.r;
}

int LqueueIsEmpty(LQueue LQ)
{
    if (LQ.f == NULL)
        return 1;
    else return 0;
}

DTPTR LdeleteFirst(LPTR &L)
{
    DTPTR B = L->bstptr;
    L = L->next;
    return B;
}

DTPTR Ldequeue(LQueue &LQ)
{
    if (LqueueIsEmpty(LQ)) {
        cout << "Queue empty.";
        return NULL;
    }
    else {
        int is_one_element = 0;
        if (LQ.f == LQ.r)
            is_one_element = 1;
        DTPTR B = LdeleteFirst(LQ.f);
        if (is_one_element) LQ.f = LQ.r = NULL;
        return B;
    }
}

//printing
int innindex = 1;
void setInorderIndex(DTPTR T)
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
        cout << "" << setw(7);
}

int previnn = 0;
void printAsItIs(LQueue Q)
{
    if (!LqueueIsEmpty(Q)) {
        DTPTR T = Ldequeue(Q);
        if (T->inn == -1 && !LqueueIsEmpty(Q)) {
            cout << "\n";
            Lenqueue(Q, T);
            previnn = 0;
        }
        else {
            if (T->inn != -1) {
                setSpaces(T->inn, previnn);
                cout << T->data;
                previnn = T->inn;
            }
            if (T->lchild) Lenqueue(Q, T->lchild);
            if (T->rchild) Lenqueue(Q, T->rchild);
        }
        printAsItIs(Q);
    }
}

void printTree(DTPTR T)
{
    LQueue Q1;
    Q1.f = Q1.r = NULL;
    DTPTR D = new(dtnode);        //Dummy
    D->lchild = D->rchild = NULL;
    D->inn = -1;
    
    setInorderIndex(T);
    Lenqueue(Q1, T);
    Lenqueue(Q1, D);
    printAsItIs(Q1);
    previnn = 0;
    innindex = 1;
}

//special functions
DTPTR addNode(string s)
{
    DTPTR T = new(dtnode);
    T->rchild = T->lchild = NULL;
    T->data = s;
    return T;
}

void insertNode(DTPTR &T, string key, int i)
{
    if(!T)
        T = addNode(key);
    else if(key[i] == '0')
        insertNode(T->lchild, key, ((i+1) % key.size()));
    else if(key[i] == '1')
        insertNode(T->rchild, key, ((i+1) % key.size()));
}

int searchKey(DTPTR T, string key, int i)
{
    if (T) {
        if (T->data[i] == key[i]) {
            int found = 1;
            for(int j = 0; j < key.size(); j++) {
                if(T->data[j] != key[j]) {
                    found = 0;
                    break;
                }
            }
            if (found && T->data.size() == key.size()) return 1;
        }
        if(key[i] == '0')
            return searchKey(T->lchild, key, (i+1) % key.size());
        else return searchKey(T->rchild, key, (i+1) % key.size());
        
    }
    else return 0;
}

//MAIN
int main()
{
    DTPTR T = NULL;
    insertNode(T, "10110", 0);
    printTree(T);
    cout << endl << "––––––––––––––––––" << endl;
    insertNode(T, "01101", 0);
    printTree(T);
    cout << endl << "––––––––––––––––––" << endl;
    insertNode(T, "1101", 0);
    printTree(T);
    cout << endl << "––––––––––––––––––" << endl;
    insertNode(T, "1011", 0);
    printTree(T);
    cout << endl << "––––––––––––––––––" << endl;
    insertNode(T, "10111", 0);
    printTree(T);
    cout << endl << "––––––––––––––––––" << endl;
    insertNode(T, "0001", 0);
    printTree(T);
    cout << endl << "––––––––––––––––––" << endl;
    insertNode(T, "10000", 0);
    printTree(T);
    cout << endl << "––––––––––––––––––" << endl;
    
    string s = "0001";
    cout << s;
    if (searchKey(T, s, 0))
        cout << " found.\n";
    else cout << " not found.\n";
}

