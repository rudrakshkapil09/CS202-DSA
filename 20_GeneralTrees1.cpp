//General Tree
#include <iostream>
using namespace std;

//struct defintion
typedef
struct tnode {
    char data;
    int inn;
    struct tnode *fc;
    struct tnode *ns;
} *TPTR;

//singly linked list as a queue definitions
typedef
struct lnode {
    TPTR TPTR;
    struct lnode *next;
} *LPTR;

struct LQueue {
    LPTR f;
    LPTR r;
};

//LQueue functions
void LaddAfter(LPTR &L, TPTR B)
{
    LPTR T = new(lnode);
    T->TPTR = B;
    if (L == NULL) L = T;
    else {
        L->next = T;
        L = T;
    }
}

void Lenqueue(LQueue &LQ, TPTR B)
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

TPTR LdeleteFirst(LPTR &L)
{
    TPTR B = L->TPTR;
    L = L->next;
    return B;
}

TPTR Ldequeue(LQueue &LQ)
{
    if (LqueueIsEmpty(LQ)) {
        cout << "Queue empty.";
        return NULL;
    }
    else {
        int is_one_element = 0;
        if (LQ.f == LQ.r)
            is_one_element = 1;
        TPTR B = LdeleteFirst(LQ.f);
        if (is_one_element) LQ.f = LQ.r = NULL;
        return B;
    }
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

void serialise(TPTR T, string &out)
{
    if (T) {
        out += T->data;
        serialise(T->fc, out);
        serialise(T->ns, out);
    }
    else out += ".";
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

//Tree printing level order
int lvlcount = 0;
void printAsItIs(LQueue Q)
{
    if (!LqueueIsEmpty(Q)) {
        TPTR T = Ldequeue(Q);
        if (T->data == -1 && !LqueueIsEmpty(Q)) {
            cout << "\n" << lvlcount++ << " => ";
            Lenqueue(Q, T);
        }
        else {
            if (T->data != -1)
                cout << T->data << " ";
            if (T->fc) {
                Lenqueue(Q, T->fc);
                TPTR T2 = T->fc;
                while (T2->ns) {
                    Lenqueue(Q, T2->ns);
                    T2 = T2->ns;
                }
            }
        }
        printAsItIs(Q);
    }
}

void printTree(TPTR T)
{
    LQueue Q1;
    Q1.f = Q1.r = NULL;
    TPTR D = new(tnode);        //Dummy
    D->fc = D->ns = NULL;
    D->data = -1;
    
    Lenqueue(Q1, D);
    Lenqueue(Q1, T);
    printAsItIs(Q1);
}

//MAIN
int main()
{
    TPTR T = NULL;
    string input = "AMPE.F..Q.RG.H.I...J.KS.DNL....O...";
    string out = "";
    
    deserialise(T, input);
    serialise(T, out);
    if (input == out)
        cout << "Correct serialisation:\n";
    cout << out << "\n";
    
    cout << "\nPrinting with brackets:\n";
    print(T);
    
    cout << "\n\nPrinting vertical order with spacing:\n";
    VRT(T, 0, 0);
    
    cout << "\nPrinting tree in level order:";
    printTree(T);
    cout << endl;
    return 0;
}








