//checking if a list is a palindrome
#include <iostream>
using namespace std;

//Linked List definition
typedef
struct lnode {
    int data;
    struct lnode *next;
} *LPTR;

//stack definition
class Stack {
private:
    int size;
    int top;
    int elements[50];
    
public:
    //definitions should be outside class
    //constructor
    Stack(int s, int t)
    {
        size = s;
        top = t;
    }
    
    void push(int x)
    {
        if (stackIsFull())
            cout << "Stack Overflow.\n";
        else
            elements[++top] = x;
        //(isStackFull()) ? cout << "Stack Overflow.\n" : elements[++top] = x;
    }
    
    int pop()
    {
        if (stackIsEmpty()) {
            cout << "Stack Empty.\n";
            return -1;
        }
        return elements[top--];
        //(stackIsEmpty()) ? cout << "Stack empty.\n" : return elements[top--];
    }
    
    int Top()
    {
        if (stackIsEmpty()) {
            cout << "Stack Empty.\n";
            return -1;
        }
        else
            return elements[top];
        //(stackIsEmpty()) ? cout << "Stack empty.\n" : return elements[top];
    }
    
    int stackIsEmpty()
    {
        if (top < 0) return 1;
        else return 0;
    }
    
    int stackIsFull()
    {
        if (top >= size - 1) return 1;
        else return 0;
    }
    
};


//function definitions
void rprint(LPTR L)
{
    if (L != NULL) {
        cout << int(L->data) << " ";
        rprint(L->next);
    }
}

void addToEnd(LPTR &L, int x)
{
    LPTR T = new(lnode);
    LPTR T2 = L;
    T->data = x;
    T->next = NULL;
    if (L == NULL)
        L = T;
    else {
        while (T2->next != NULL)
            T2 = T2->next;
        T2->next = T;
    }
}

void inputLList(LPTR &L)
{
    int n = 1;
    cout << "Enter elements: ";
    while (n != -1) {
        cin >> n;
        if (n == -1)
            break;
        addToEnd(L, n);
    }
}

//special functions
Stack s1(50, -1);
void rinputInStack(LPTR L)
{
    if (L != nullptr) {
        s1.push(L->data);
        rinputInStack(L->next);
    }
}

int flag = 1;
void checkPalindrome(LPTR L)
{
    if (L != nullptr) {
        if (L->data != s1.Top()) {
            flag = 0;
        }
        s1.pop();
        checkPalindrome(L->next);
    }
}

//[MAIN]
int main()
{
    LPTR L1 = nullptr;
    cout << "Enter the list (end with -1)\n";
    inputLList(L1);
    rinputInStack(L1);
    checkPalindrome(L1);
    if (flag)
        cout << "Palindrome.\n";
    else cout << "Not palindrome.\n";
    return 0;
}
