//converting n-ary (general) to binary and back
#include <iostream>
using namespace std;

//struct defintion
typedef
struct tnode {
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

//special functions
BTPTR newBTNode(char ch)
{
    BTPTR T = new btnode;
    T->lchild = T->rchild = NULL;
    T->data = ch;
    return T;
}

void convertGT(TPTR T, BTPTR &B)
{
    if (T) {
        B = newBTNode(T->data);
        convertGT(T->fc, B->lchild);
        convertGT(T->ns, B->rchild);
    }
}

void convertBT(TPTR &T, BTPTR B)
{
    if (B) {
        T = newNode(B->data);
        convertBT(T->fc, B->lchild);
        convertBT(T->ns, B->rchild);
    }
}

//MAIN
int main()
{
    TPTR T = NULL;
    BTPTR B = NULL;
    
    //string input = "AMPE.F..Q.RG.H.I...J.KS.DNL....O...";
    string input = "ABK..CH.I.J..DE.FG.....";
    string out = "";
    deserialise(T, input);
    
    cout << "Original General Tree:\n";
    VRT(T, 0, 1);
    
    cout << "\nBinary Tree Conversion:\n";
    convertGT(T, B);
    printTree(B);
    
    cout << "\n\nConverting Back:\n";
    convertBT(T, B);
    VRT(T, 0, 1);
}








