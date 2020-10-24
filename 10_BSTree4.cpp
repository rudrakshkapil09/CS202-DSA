//finding highest level sum - doesn't print at which level the highest is
#include <iostream>
using namespace std;

//tree defintion
typedef
struct bstnode {
    struct bstnode *lchild;
    int data;
    int inn;                    //in order number
    struct bstnode *rchild;
} *BSTPTR;

//singly linked list as a queue definitions
typedef
struct lnode {
    BSTPTR bstptr;
    struct lnode *next;
} *LPTR;

struct LQueue {
    LPTR f;
    LPTR r;
};

//LQueue functions
void LaddAfter(LPTR &L, BSTPTR B)
{
    LPTR T = new(lnode);
    T->bstptr = B;
    if (L == NULL) L = T;
    else {
        L->next = T;
        L = T;
    }
}

void Lenqueue(LQueue &LQ, BSTPTR B)
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

BSTPTR LdeleteFirst(LPTR &L)
{
    BSTPTR B = L->bstptr;
    L = L->next;
    return B;
}

BSTPTR Ldequeue(LQueue &LQ)
{
    if (LqueueIsEmpty(LQ)) {
        cout << "Queue empty.";
        return NULL;
    }
    else {
        int is_one_element = 0;
        if (LQ.f == LQ.r)
            is_one_element = 1;
        BSTPTR B = LdeleteFirst(LQ.f);
        if (is_one_element) LQ.f = LQ.r = NULL;
        return B;
    }
}

//tree functions
void insertNode(BSTPTR &T, int k)
{
    if (T != NULL) {
        if (k < T->data) insertNode(T->lchild, k);
        else if (k > T->data) insertNode(T->rchild, k);
        else cout << "Error: Duplicate data.\n";
    }
    else {
        T = new(bstnode);
        T->inn = 0;
        T->data = k;
        T->rchild = T->lchild = NULL;
    }
}

void inputTree(BSTPTR &T)
{
    int num;
    cout << "Enter elements of tree (end -> -1):\n";
    while (1) {
        cin >> num;
        if (num == -1) break;
        insertNode(T, num);
    }
}

//special functions
void findMax(LQueue Q, BSTPTR D, int &max)
{
    static int count = 0;
    if (!LqueueIsEmpty(Q)) {
        BSTPTR T = Ldequeue(Q);
        if (T->data == -1 && !LqueueIsEmpty(Q)) {
            //if (Q.f->bstptr->data != -1)
                Lenqueue(Q, D);
            max = (max > count) ? max : count;
            count = 0;
        }
        else {
            if (T->data != -1) {
                count += T->data;
            }
            if (T->lchild) Lenqueue(Q, T->lchild);
            if (T->rchild) Lenqueue(Q, T->rchild);
        }
        findMax(Q, D, max);
    }
}


//[MAIN]
// 6 8 9 7 4 2 5 3 -1
// 18 12 27 5 15 20 45 10 36 81 50 -1
int main()
{
    BSTPTR T = NULL;
    BSTPTR D = new(bstnode);        //Dummy
    D->lchild = D->rchild = NULL;
    D->data = -1;
    LQueue LQ;
    LQ.f = NULL;
    LQ.r = NULL;
    int max = 0;
    
    inputTree(T);
    Lenqueue(LQ, T);            //to get first pointer
    Lenqueue(LQ, D);
    findMax(LQ, D, max);
    cout << endl << "Max: " << max << endl;
}
