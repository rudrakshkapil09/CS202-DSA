//Checking if a tree is a mirror or the same
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
int dataindex = 0;
int deserialise(BTPTR &T, char data[])
{
    char ch = data[dataindex++];
    if (ch != '.') {
        T = new(btnode);
        T->data = ch;
        T->lchild = T->rchild = NULL;
        deserialise(T->lchild, data);
        deserialise(T->rchild, data);
    }
    return dataindex;
}

int checkSame(BTPTR T1, BTPTR T2)
{
    if (T1 != NULL && T2 != NULL) {
        if (T1->data == T2->data)
            return (checkSame(T1->lchild, T2->lchild) && checkSame(T1->rchild, T2->rchild));
        else return 0;
    }
    return 1;
}

int checkMirror(BTPTR T1, BTPTR T2)
{
    if (T1 != NULL && T2 != NULL) {
        if (T1->data == T2->data)
            return (checkMirror(T1->lchild, T2->rchild) && checkMirror(T1->rchild, T2->lchild));
        else return 0;
    }
    return 1;
}

//[MAIN]
int main()
{
    BTPTR T1, T2, T3, T4, T5;
    T1 = T2 = T3 = T4 = T5 = NULL;
    char serial1[30] = "APML..J..R..BD.N..EF..S..";     //original
    char serial2[30] = "APML..J..R..BD.N..EF..S..";     //same
    char serial3[30] = "APML..J..R..BD.Z..EQ..S..";     //not same
    char serial4[30] = "ABES..F..DN...PR..MJ..L..";     //mirror
    char serial5[30] = "ABES..F..DN...PR..MJ..LS...";   //not mirror
    
    deserialise(T1, serial1);
    dataindex = 0;
    deserialise(T2, serial2);
    dataindex = 0;
    deserialise(T3, serial3);
    dataindex = 0;
    deserialise(T4, serial4);
    dataindex = 0;
    deserialise(T5, serial5);
    dataindex = 0;
    
    cout << "Tree 1 =>\n";
    printTree(T1);
    cout << "\n\nTree 2 =>\n";
    printTree(T2);
    cout << "\n\nTree 3 =>\n";
    printTree(T3);
    cout << "\n\nTree 4 =>\n";
    printTree(T4);
    cout << "\n\nTree 5 =>\n";
    printTree(T5);
    cout << endl << endl;
    
    if (checkSame(T1, T2))
        cout << "T1 and T2 are the same trees.\n";
    else cout << "T1 and T2 are not the same tees.\n";
    if (checkSame(T1, T3))
        cout << "T1 and T3 are the same trees.\n";
    else cout << "T1 and T3 are not the same tees.\n";
    if (checkMirror(T1, T4))
        cout << "T1 and T4 are mirror images.\n";
    else cout << "T1 and T4 are not mirror images.\n";
    if (checkSame(T1, T3))
        cout << "T1 and T5 are mirror images.\n";
    else cout << "T1 and T5 are not mirror images.\n";
    cout << endl;
    return 0;
}
