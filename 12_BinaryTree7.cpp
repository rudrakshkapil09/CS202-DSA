//setting tree using Level Order and LDR
#include <iostream>
using namespace std;

//tree defintion
typedef
struct btnode {
    struct btnode *lchild;
    char data;
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

//tree functions
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
        if (T->data == -1 && !LqueueIsEmpty(Q)) {
            cout << "\n";
            Lenqueue(Q, T);
            previnn = 0;
        }
        else {
            if (T->data != -1) {
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

void printTree(BTPTR T)
{
    LQueue Q1;
    Q1.f = Q1.r = NULL;
    BTPTR D = new(btnode);        //Dummy
    D->lchild = D->rchild = NULL;
    D->data = -1;
    
    setInorderIndex(T);
    Lenqueue(Q1, T);
    Lenqueue(Q1, D);
    printAsItIs(Q1);
    previnn = 0;
    innindex = 1;
}

//special functions
int getRoot(char LDR[], char key, int low, int high)
{
    int i = 0;
    for (i = low; i <= high; i++)
        if (LDR[i] == key)
            return i;
    return -1;
}

char *getNewLO(char LDR[], char LO[], int low, int high)
{
    if (low > high) return NULL;
    char *newarray = new char[high-low], j = 0;
    for (int i = 0; i < sizeof(LDR)/sizeof(LDR[0])*2; i++) {
        if (getRoot(LDR, LO[i], low, high) != -1)
            newarray[j++] = LO[i];
    }
    return newarray;
}

BTPTR setTree(char LDR[], char LO[], int low, int high)
{
    BTPTR T = new(btnode);
    T->lchild = T->rchild = NULL;
    if (low > high) return NULL;
    T->data = LO[0];
    if (low == high) return T;
    else {
        int j = getRoot(LDR, T->data, low, high);
        char *leftLO = getNewLO(LDR, LO, low, j-1);
        char *rightLO = getNewLO(LDR, LO, j+1, high);
        T->lchild = setTree(LDR, leftLO, low, j-1);
        T->rchild = setTree(LDR, rightLO, j+1, high);
        return T;
    }
}

//[MAIN]
int main()
{
    BTPTR T = NULL;
    char LevelOrder[30] = "APBMRDELJNFS";
    char LDR[30] = "LMJPRADNBFES";
    T = setTree(LDR, LevelOrder, 0, 11);
    cout << "Tree:\n";
    printTree(T);
    cout << endl;
}


