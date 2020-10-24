//5.d) Checking if a string is a valid preorder serialisation of a binary tree
//use a stack
#include <iostream>
using namespace std;

struct stack {
    int top;
    int size;
    int elements[50];
};

int stackIsEmpty(stack s)
{
    if (s.top < 0) return 1;
    else return 0;
}

int stackIsFull(stack s)
{
    if (s.top >= s.size-1) return 1;
    else return 0;
}

int Top(stack s)
{
    if (stackIsEmpty(s))
        return -1;
    else return s.elements[s.top];
}

int pop(stack &s)
{
    if (stackIsEmpty(s))
        return -1;
    else return s.elements[s.top--];
}

void push(stack &s, int x)
{
    if (stackIsFull(s))
        cout << "Stack Overflow.\n";
    else s.elements[++s.top] = x;
}

//special function
int checkString(stack &s, char input[], int n) {
    static int index = 0;
    char ch = input[index++];
    
    
    if (ch == '#' && index == n-1)
        return 1;
    else if (ch != '#' && index == n-1)
        return 0;
    
    if (isdigit(ch))
        push(s, ch-'0');
    else {
        if (stackIsEmpty(s))
            return 0;
        else pop(s);
    }
    return checkString(s, input, n);
}

//main
int main()
{
    stack s;
    s.top = -1; s.size = 50;
    char input[] = "934##1##2#6##";
    int n = sizeof(input)/sizeof(input[0]);
    
    int check = checkString(s, input, n);
    check = stackIsEmpty(s) ? check : 0;
    
    if (check)
        cout << "The string is a valid serialisation.\n";
    else cout << "The string is not a valid serialisation.\n";
    return 0;
}
