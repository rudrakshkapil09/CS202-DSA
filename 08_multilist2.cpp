//target problem
#include <iostream>
using namespace std;

//Linked List & struct definition
typedef
struct lnode {
    int data;
    int count;
    struct lnode *next[10] = {NULL};
} *LPTR;

struct stack {
    LPTR data[30] = {NULL};
    int top = -1;
    int size = 100;
};

//stack functions
int stackIsEmpty(stack s1)
{
    if (s1.top == -1)
        return 1;
    else return 0;
}

int stackIsFull(stack s1)
{
    if (s1.top >= s1.size - 1)
        return 1;
    else return 0;
}

void push(stack &s1, LPTR x) {
    if (stackIsFull(s1))
        cout << "Stack Overflow.\n";
    else
        s1.data[++s1.top] = x;
}

LPTR pop(stack s1)
{
    if (stackIsEmpty(s1)) {
        cout << "Stack empty.";
        return NULL;
    }
    else {
        LPTR B = s1.data[s1.top];
        return B;
    }
}

LPTR Top(stack s1)
{
    if (stackIsEmpty(s1)) {
        cout << "Stack empty.";
        return NULL;
    }
    else {
        LPTR B = s1.data[s1.top];
        return B;
    }
}

//special functions
LPTR addNode(int x)
{
    LPTR T = new(lnode);
    T->data = x;
    T->count = 1;
    for (int i = 0; i < 10; i++)
        T->next[i] = NULL;
    return T;
}

void inputNetwork(LPTR &L, int input[])
{
    static int inputindex = 0;
    int num = input[inputindex++];
    
    if (num == -1) return;
    else if (num == -2) {
        num = input[inputindex++];
        L = addNode(num);
        
        int count = input[inputindex++];
        L->count = count;
        
        for (int i = 0; i < L->count; i++) {
            inputNetwork(L->next[i], input);
        }
    }
    else {
        L = addNode(num);
        inputNetwork(L->next[0], input);
    }
    
}

void printPath(LPTR L, stack s1, int key)
{
    if (L) {
        if (L->data == key) {
            cout << "Path to " << key << " => ";
            cout << key << " <- ";
            while (!stackIsEmpty(s1)) {
                LPTR T = pop(s1);
                s1.top--;
                cout << T->data;
                if (s1.top != -1)
                    cout << " <- ";
            }
        }
        else {
            push(s1, L);
            printPath(L->next[L->count-1], s1, key);
        }
    }
    else {
        while (!stackIsEmpty(s1) && (Top(s1)->count == 1)) {
            pop(s1);
            s1.top--;
        }
        L = pop(s1);
        L->count--;
        s1.top--;
        printPath(L, s1, key);
    }
}

//[MAIN]
int main()
{
    LPTR L = NULL;
    stack s1;
    int input[25] = {5, 3, -2, 2, 3, 8, 9, 15, -1, 3, 6, -1, -2, 4, 2, 12, 14, -1, 1, 10, -1};
    inputNetwork(L, input);
    cout << "Network successfully input.\n";
    printPath(L, s1, 14);
    
    cout << endl;
    return 0;
}

