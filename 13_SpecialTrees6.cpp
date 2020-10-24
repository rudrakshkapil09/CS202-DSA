//Treap
#include <iostream>
#include <iomanip>
using namespace std;

typedef
struct tpnode {
    struct tpnode *lchild;
    char k1;
    int k2;
    int inn = -1;
    struct tpnode *rchild;
} *TPPTR;

//singly linked list as a queue & stack definitions
typedef
struct lnode {
    TPPTR TPPTR;
    struct lnode *next;
} *LPTR;

struct LQueue {
    LPTR f;
    LPTR r;
};

//LQueue functions
void LaddAfter(LPTR &L, TPPTR B)
{
    LPTR T = new(lnode);
    T->TPPTR = B;
    if (L == NULL) L = T;
    else {
        L->next = T;
        L = T;
    }
}

void Lenqueue(LQueue &LQ, TPPTR B)
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

TPPTR LdeleteFirst(LPTR &L)
{
    TPPTR B = L->TPPTR;
    L = L->next;
    return B;
}

TPPTR Ldequeue(LQueue &LQ)
{
    if (LqueueIsEmpty(LQ)) {
        cout << "Queue empty.";
        return NULL;
    }
    else {
        int is_one_element = 0;
        if (LQ.f == LQ.r)
            is_one_element = 1;
        TPPTR B = LdeleteFirst(LQ.f);
        if (is_one_element) LQ.f = LQ.r = NULL;
        return B;
    }
}


//printing functions
int innindex = 1;
void setInorderIndex(TPPTR T)
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
        cout << "" << setw(5);
}

int previnn = 0;
void printAsItIs(LQueue Q)
{
    if (!LqueueIsEmpty(Q)) {
        TPPTR T = Ldequeue(Q);
        if (T->inn == -1 && !LqueueIsEmpty(Q)) {
            cout << "\n";
            Lenqueue(Q, T);
            previnn = 0;
        }
        else {
            if (T->inn != -1) {
                setSpaces(T->inn, previnn);
                cout << T->k1 << " " << T->k2;
                previnn = T->inn;
            }
            if (T->lchild) Lenqueue(Q, T->lchild);
            if (T->rchild) Lenqueue(Q, T->rchild);
        }
        printAsItIs(Q);
    }
}

void printTree(TPPTR T)
{
    LQueue Q1;
    Q1.f = Q1.r = NULL;
    TPPTR D = new(tpnode);        //Dummy
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
int checkTreap(TPPTR T)
{
    if (T) {
        if ((T->lchild && (T->lchild->k2 < T->k2 || T->k1 < T->lchild->k1)) || (T->rchild && (T->rchild->k2 < T->k2 || T->rchild->k1 < T->k1)))
            return 0;
        int l = checkTreap(T->lchild);
        if (l) return checkTreap(T->rchild);    //changed from !l
        else return l;
    }
    else return 1;
}


TPPTR singleLeftRotate(TPPTR &K1, TPPTR &K2)
{
    K1->rchild = K2->lchild;
    K2->lchild = K1;
    cout << "[Single Left]\n";
    return K2;
}

TPPTR singleRightRotate(TPPTR &K1, TPPTR &K2)
{
    K1->lchild = K2->rchild;
    K2->rchild = K1;
    cout << "[Single Right]\n";
    return K2;
}

TPPTR checkTree(TPPTR &T)
{
    if (!checkTreap(T)) {
        TPPTR K1 = T, K2 = NULL;
        if (T->lchild && T->k2 > T->lchild->k2) {
            K2 = K1->lchild;
            return singleRightRotate(K1, K2);
        }
        if (T->rchild && T->rchild->k2 < T->k2){
            K2 = K1->rchild;
            return singleLeftRotate(K1, K2);
        }
    }
    return T;
}

TPPTR insertNode(TPPTR &T, int k1, int k2)
{
    if (T != NULL) {
        if (k1 < T->k1) T->lchild = insertNode(T->lchild, k1, k2);
        else if (k1 > T->k1) T->rchild = insertNode(T->rchild, k1, k2);
        else if (k2 == T->k2)
            cout << "Error: Duplicate data.\n";
        else {
            cout << "Repeated K1.\n";
            if (!T->lchild) T->lchild = insertNode(T->lchild, k1, k2);
            else if (!T->rchild) T->rchild = insertNode(T->rchild, k1, k2);
        }
        return checkTree(T);
    }
    else {
        T = new(tpnode);
        T->k1 = k1;
        T->k2 = k2;
        T->rchild = T->lchild = NULL;
    }
    return T;
}

TPPTR findMin(TPPTR T) {
    if (T->lchild) return findMin(T->lchild);
    else return T;
}

TPPTR findMax(TPPTR T) {
    if (T->rchild) return findMax(T->rchild);
    else return T;
}

TPPTR deleteNode(TPPTR H, int k1)
{
    if (!H) return NULL;
    if (H->k1 > k1)
        H->lchild = deleteNode(H->lchild, k1);
    else if (H->k1 < k1)
        H->rchild = deleteNode(H->rchild, k1);
    else {
        TPPTR T1;
        if ((H->rchild && H->lchild) || H->rchild) {
            T1 = findMin(H->rchild);
            H->k1 = T1->k1;
            H->k2 = T1->k2;
            H->rchild = deleteNode(H->rchild, T1->k1);
        }
        else if (H->lchild) {
            T1 = findMax(H->lchild);
            H->k1 = T1->k1;
            H->k2 = T1->k2;
            H->lchild = deleteNode(H->lchild, T1->k1);
        }
        else H = NULL;
    }
    H = checkTree(H);
    if (H) {
        H->lchild = checkTree(H->lchild);
        H->rchild = checkTree(H->rchild);
    }
    return H;
}

//MAIN
int main()
{
    TPPTR T = NULL;
    T = insertNode(T, 'H', 22);
    printTree(T);
    cout << "\n––––––––––––––––––\n";
    T = insertNode(T, 'K', 27);
    printTree(T);
    cout << "\n––––––––––––––––––\n";
    T = insertNode(T, 'R', 52);
    printTree(T);
    cout << "\n––––––––––––––––––\n";
    T = insertNode(T, 'S', 51);
    printTree(T);
    cout << "\n––––––––––––––––––\n";
    T = insertNode(T, 'N', 5);
    printTree(T);
    cout << "\n––––––––––––––––––\n";
    T = insertNode(T, 'N', 5);
    printTree(T);
    cout << "\n––––––––––––––––––\n";
    T = insertNode(T, 'Q', 4);
    printTree(T);
    cout << "\n––––––––––––––––––\n";
    T = insertNode(T, 'M', 2);
    printTree(T);
    cout << "\n––––––––––––––––––\n";
    
    T = deleteNode(T, 'Q');
    printTree(T);
    cout << "\n––––––––––––––––––\n";
    
}
