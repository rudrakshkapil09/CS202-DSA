//postfix evaluation using stacks as linked lists
#include <iostream>
using namespace std;

//struct definition
typedef
struct lnode {
    int data;
    struct lnode *next;
} *LPTR;

struct LST {
    LPTR top;
};

//special LST functions
void addToFront(LPTR &L, int x)
{
    LPTR T = new(lnode);
    T->data = x;
    if (L == NULL) {
        T->next = NULL;
    }
    else T->next = L;
    L = T;
}

LPTR deleteFirst(LPTR L)
{
    return L->next;
}

int LstackIsEmpty(LST s1)
{
    if (s1.top == NULL)
        return 1;
    else return 0;
}

void Lpush(LST &s1, int x)
{
    addToFront(s1.top, x);
}

int Lpop(LST &s1)
{
    if (LstackIsEmpty(s1)) {
        cout << "Stack empty.";
        return -1;
    }
    else {
        int x = s1.top->data;
        s1.top = deleteFirst(s1.top);
        return x;
    }
}

int LTop(LST s1)
{
    if (LstackIsEmpty(s1)) {
        cout << "Stack empty.";
        return -1;
    }
    else return s1.top->data;
}

//other functions
int eval(int op1, int op2, char opt)
{
    switch (opt) {
        case '+': return (op2 + op1);
        case '-': return (op2 - op1);
        case '*': return (op2 * op1);
        case '/': return (op2 / op1);
        default: return 0;
    }
}

//[MAIN]
int main()
{
    LST S;
    S.top = NULL;
    int i, op1, op2;
    char input[50];
    cout << "Enter postfix:\n";
    cin.getline(input, 50);
    
    i = 0;
    while (i < strlen(input)) {
        if (isdigit(input[i])) {
            Lpush(S, input[i] - '0');
        }
        else {
            op1 = Lpop(S);
            op2 = Lpop(S);
            Lpush(S, eval(op1, op2, input[i]));
        }
        i++;
    }
    cout << "Answer = " << Lpop(S) << endl;
    return 0;
}
