//Splitting a general tree into binary trees
#include <iostream>
using namespace std;

//struct defintion
typedef
struct tnode {
    int done = 0;
    char data;
    struct tnode *fc;
    struct tnode *ns;
} *TPTR;

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

//Binary tree printing
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

//creation
TPTR newNode(char ch)
{
    TPTR T = new tnode;
    T->fc = T->ns = NULL;
    T->data = ch;
    T->done = 0;
    return T;
}

void deserialise(TPTR &T, string input)
{
    static int cindex = 0;
    if (cindex > input.size()) return;
    char ch = input[cindex++];
    if (ch != '.') {
        T = newNode(ch);
        deserialise(T->fc, input);
        deserialise(T->ns, input);
    }
    else T = NULL;
}

//printing with brackets
void print(TPTR T)
{
    if (T) {
        cout << T->data;
        if (T->fc) {
            cout << "{";
            print(T->fc);
            cout << "}";
        }
        print(T->ns);
    }
}

//printing vertical order
void printSpaces(int count)
{
    for (int i = 0; i < count; i++)
        cout << "  ";
}

int lastGen(TPTR T)
{
    if (T) {
        if (T->fc) return 0;
        else return lastGen(T->ns);
    }
    else return 1;
}

void VRT(TPTR T, int count, int downflag)
{
    if (T) {
        printSpaces(count);
        if (lastGen(T) && downflag) {
            while (T) {
                cout << T->data << " ";
                T = T->ns;
            }
            cout << "\n";
            return;
        }
        cout << T->data << endl;
        VRT(T->fc, count+1, 1);
        VRT(T->ns, count, 0);
    }
}

//splitting
int checkDone(TPTR T)
{
    if (!T) return 1;
    if (!T->done)
        return 0;
    else return checkDone(T->ns);
}

BTPTR getTree(TPTR T, int &count)
{
    if (T) {
        BTPTR B = new btnode;
        B->data = T->data;
        B->lchild = B->rchild = NULL;
        
        TPTR L = T->fc;
        if (L) {
            while (L && L->done)
                L = L->ns;
            TPTR R = L->ns;
            while (R && R->done)
                R = R->ns;
            
            if (!L && !R) {
                T->done = 1;
                count++;
            }
            else {
                B->lchild = getTree(L, count);
                B->rchild = getTree(R, count);
                if (checkDone(L)) {
                    T->done = 1;
                    count++;
                }
            }
        }
        else {
            T->done = 1;
            count++;
        }
        return B;
    }
    return NULL;
}

void printTrees(TPTR T, int n)
{
    int count = 0;
    while (count < n) {
        BTPTR B = getTree(T, count);
        printTree(B);
        cout << "\n–––––––––––––\n";
    }
}

//MAIN
int main()
{
    TPTR T = NULL;
    string input = "AMPE.F..Q.RG.H.I...J.KS.DNL....O...";
    string out = "";
    
    int n = 0;
    for (int i = 0; i < input.size(); i++)
        if (isalpha(input[i])) n++;
    
    deserialise(T, input);
    cout << "\n\nPrinting vertical order with spacing:\n";
    VRT(T, 0, 0);
    
    cout << "\n\nBinary Trees obtained from splitting:\n";
    printTrees(T, n);
}








