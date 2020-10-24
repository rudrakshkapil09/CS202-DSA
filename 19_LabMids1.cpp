/*Lowest common ancestor*/
//Counting number of turns from one node to another - binary tree
#include <iostream>
using namespace std;

//tree defintion
typedef
struct btnode {
    struct btnode *lchild;
    char key;
    int inn;                    //in order number
    struct btnode *rchild;
} *BTPTR;

//singly linked list as a queue definitions
typedef
struct lnode {
    BTPTR BTPTR;
    struct lnode *next;
} *LPTR;

struct LQueue {
    LPTR f;
    LPTR r;
};

//LQueue functions
void LaddAfter(LPTR &L, BTPTR B)
{
    LPTR T = new(lnode);
    T->BTPTR = B;
    if (L == NULL) L = T;
    else {
        L->next = T;
        L = T;
    }
}

void Lenqueue(LQueue &LQ, BTPTR B)
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

BTPTR LdeleteFirst(LPTR &L)
{
    BTPTR B = L->BTPTR;
    L = L->next;
    return B;
}

BTPTR Ldequeue(LQueue &LQ)
{
    if (LqueueIsEmpty(LQ)) {
        cout << "Queue empty.";
        return NULL;
    }
    else {
        int is_one_element = 0;
        if (LQ.f == LQ.r)
            is_one_element = 1;
        BTPTR B = LdeleteFirst(LQ.f);
        if (is_one_element) LQ.f = LQ.r = NULL;
        return B;
    }
}

//tree printing & setting
int deserialise(BTPTR &T, char key[])
{
    static int dataindex = 0;
    char ch = key[dataindex++];
    if (ch != '.') {
        T = new(btnode);
        T->key = ch;
        T->lchild = T->rchild = NULL;
        deserialise(T->lchild, key);
        deserialise(T->rchild, key);
    }
    return dataindex;
}

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
void printAsItIs(LQueue Q)
{
    if (!LqueueIsEmpty(Q)) {
        BTPTR T = Ldequeue(Q);
        if (T->key == -1 && !LqueueIsEmpty(Q)) {
            cout << "\n";
            Lenqueue(Q, T);
            previnn = 0;
        }
        else {
            if (T->key != -1) {
                setSpaces(T->inn, previnn);
                cout << T->key;
                previnn = T->inn;
            }
            if (T->lchild) Lenqueue(Q, T->lchild);
            if (T->rchild) Lenqueue(Q, T->rchild);
        }
        printAsItIs(Q);
    }
}

void printTree(BTPTR T)
{
    LQueue Q1;
    Q1.f = Q1.r = NULL;
    BTPTR D = new(btnode);        //Dummy
    D->lchild = D->rchild = NULL;
    D->key = -1;
    
    setInorderIndex(T);
    Lenqueue(Q1, T);
    Lenqueue(Q1, D);
    printAsItIs(Q1);
    previnn = 0;
    innindex = 1;
}

//special functions
BTPTR findLCA(BTPTR T, char k1, char k2)
{
    if (T) {
        if (T->key == k1 || T->key == k2)
            return T;
        
        BTPTR L = findLCA(T->lchild, k1, k2);
        BTPTR R = findLCA(T->rchild, k1, k2);
        if (L && R)
            return T;
        else return (L) ? L : R;
    }
    else return NULL;
}

int countTurns(BTPTR T, char k, int lflag, int &count)
{
    if (T) {
        if (T->key == k)
            return 1;
        
        if (lflag) {
            if (countTurns(T->lchild, k, 1, count))
                return 1;
            if (countTurns(T->rchild, k, 0, count)) {
                count++;
                return 1;
            }
        }
        else {
            if (countTurns(T->rchild, k, 0, count))
                return 1;
            if (countTurns(T->lchild, k, 1, count)) {
                count++;
                return 1;
            }
        }
    }
    return 0;
}

int findTurns(BTPTR T, char k1, char k2)
{
    BTPTR LCA = findLCA(T, k1, k2);
    int count = 0;
    
    if (LCA->key != k1 && LCA->key != k2) {
        if (!countTurns(LCA->rchild, k1, 0, count)) {
            count = 0;
            countTurns(LCA->lchild, k1, 1, count);
        }
        int k1count = count;
        count = 0;
        if (!countTurns(LCA->rchild, k2, 0, count)) {
            count = 0;
            countTurns(LCA->lchild, k2, 1, count);
        }
        count += k1count + 1;
    }
    else {
        char child = (LCA->key == k1) ? k2 : k1;
        if (!countTurns(LCA->rchild, child, 0, count)) {
            count = 0;
            countTurns(LCA->lchild, child, 1, count);
        }
    }
    return count;
}

//MAIN
int main()
{
    BTPTR T = NULL, LCA = NULL;
    char serial[30] = "APML..J..R..BD.N..EF..S..";
    deserialise(T, serial);
    printTree(T);
    cout << endl << endl;
    
    char node1, node2;
    cout << "Enter two nodes: ";
    cin >> node1 >> node2;
    LCA = findLCA(T, node2, node1);
    cout << "LCA => " << LCA->key << "\n";
    cout << "Number of turns => " << findTurns(T, node1, node2) << endl;
    
}


