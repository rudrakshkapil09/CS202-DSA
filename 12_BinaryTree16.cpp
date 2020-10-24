//Expression tree creation & evaluation
#include <iostream>
using namespace std;

//tree defintion
union u {
    int opnd;           //0
    char optr;          //1
};

typedef
struct etnode {
    struct etnode *lchild;
    union u data;
    int tag;
    int inn;                    //in order number
    struct etnode *rchild;
} *ETPTR;

//singly linked list as a queue definitions
typedef
struct lnode {
    ETPTR ETPTR;
    struct lnode *next;
} *LPTR;

struct LQueue {
    LPTR f;
    LPTR r;
};

struct LST {
    LPTR top;
};

//LST functions
void addToFront(LPTR &L, ETPTR B)
{
    LPTR T = new(lnode);
    T->ETPTR = B;
    if (L == NULL) {
        T->next = NULL;
    }
    else T->next = L;
    L = T;
}

LPTR deleteFirst(LPTR &L)
{
    if (L->next != NULL)
        return L->next;
    else return NULL;
}

int LstackIsEmpty(LST s1)
{
    if (s1.top == NULL)
        return 1;
    else return 0;
}

void Lpush(LST &s1, ETPTR B)
{
    addToFront(s1.top, B);
}

ETPTR Lpop(LST &s1)
{
    if (LstackIsEmpty(s1)) {
        cout << "Stack empty.";
        return NULL;
    }
    else {
        ETPTR B = s1.top->ETPTR;
        s1.top = deleteFirst(s1.top);
        return B;
    }
}

ETPTR LTop(LST s1)
{
    if (LstackIsEmpty(s1)) {
        return NULL;
    }
    else return s1.top->ETPTR;
}


//LQueue functions
void LaddAfter(LPTR &L, ETPTR B)
{
    LPTR T = new(lnode);
    T->ETPTR = B;
    if (L == NULL) L = T;
    else {
        L->next = T;
        L = T;
    }
}

void Lenqueue(LQueue &LQ, ETPTR B)
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

ETPTR LdeleteFirst(LPTR &L)
{
    ETPTR B = L->ETPTR;
    L = L->next;
    return B;
}

ETPTR Ldequeue(LQueue &LQ)
{
    if (LqueueIsEmpty(LQ)) {
        cout << "Queue empty.";
        return NULL;
    }
    else {
        int is_one_element = 0;
        if (LQ.f == LQ.r)
            is_one_element = 1;
        ETPTR B = LdeleteFirst(LQ.f);
        if (is_one_element) LQ.f = LQ.r = NULL;
        return B;
    }
}

//tree functions
int innindex = 1;
void setInorderIndex(ETPTR T)
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
        ETPTR T = Ldequeue(Q);
        if ((T->tag == 0 && T->data.opnd == -1) && !LqueueIsEmpty(Q)) {
            cout << "\n";
            Lenqueue(Q, T);
            previnn = 0;
        }
        else {
            if ((T->data.opnd != -1 && T->tag == 0) || T->tag == 1) {
                setSpaces(T->inn, previnn);
                (T->tag == 1) ? cout << T->data.optr : cout << T->data.opnd;
                previnn = T->inn;
            }
            if (T->lchild) Lenqueue(Q, T->lchild);
            if (T->rchild) Lenqueue(Q, T->rchild);
        }
        printAsItIs(Q);
    }
}

void printTree(ETPTR T)
{
    LQueue Q1;
    Q1.f = Q1.r = NULL;
    ETPTR D = new(etnode);        //Dummy
    D->lchild = D->rchild = NULL;
    D->tag = 0;
    D->data.opnd = -1;
    
    setInorderIndex(T);
    Lenqueue(Q1, T);
    Lenqueue(Q1, D);
    printAsItIs(Q1);
    previnn = 0;
    innindex = 1;
}

//special functions
void creation(ETPTR &T, LST S, char postOrder[])
{
    static int po_index = 0;
    char ch = postOrder[po_index++];
    if (ch == '\0') return;
    
    T = new(etnode);
    if (isdigit(ch)) {
        T->tag = 0;
        T->data.opnd = ch - '0';
        T->lchild = T->rchild = NULL;
    }
    else {
        T->rchild = Lpop(S);
        T->lchild = Lpop(S);
        T->tag = 1;
        T->data.optr = ch;
    }
    Lpush(S, T);
    creation(T, S, postOrder);
}

int calculate(char opt, int op2, int op1)
{
    switch (opt) {
        case '+': return (op2 + op1);
        case '-': return (op2 - op1);
        case '*': return (op2 * op1);
        case '/': return (op2 / op1);
        default: return 0;
    }
}

int evalPostET(ETPTR T)
{
    if (T) {
        if (!T->lchild && !T->rchild)       //leaf node -> digit
            return T->data.opnd;
        else                                //non leaf node -> operator
            return calculate(T->data.optr, evalPostET(T->lchild), evalPostET(T->rchild));
    }
    return 0;
}

//[MAIN]
int main()
{
    ETPTR T = NULL;
    LST S;
    S.top = NULL;
    char postOrder[30] = "12+3*6+23+/";
    
    creation(T, S, postOrder);
    cout << "Expression tree:\n";
    printTree(T);
    cout << endl;
    
    cout << "Answer => " << evalPostET(T) << endl;
    return 0;
}


