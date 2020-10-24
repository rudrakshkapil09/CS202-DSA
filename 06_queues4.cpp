//converting prefix to postfix
#include <iostream>
#include <string>
using namespace std;

//struct defintion & functions
struct stack {
    string elements[50];
    int top;
    int size;
};

int stackIsFull(stack s)
{
    if (s.top >= s.size - 1) return 1;
    else return 0;
}

int stackIsEmpty(stack s)
{
    if (s.top < 0) return 1;
    else return 0;
}

void push(stack &s, char x) {
    if (stackIsFull(s))
        cout << "Stack Overflow.\n";
    else
        s.elements[++s.top] = x;
}

void push(stack &s, string x) {
    if (stackIsFull(s))
        cout << "Stack Overflow.\n";
    else
        s.elements[++s.top] = x;
}


string pop(stack &s) {
    if (stackIsEmpty(s))
        cout << "Stack Empty.\n";
    else
        return s.elements[s.top--];
    return "-";
}

//special functions
void convertExpression(stack &s, string pre, int pren)
{
    static int index = pren-1;
    if (index < 0) return;
    else {
        if (isalpha(pre[index])) {
            push(s, pre[index]);
        }
        else {
            string op1 = pop(s);
            string op2 = pop(s);
            string res = op1 + op2 + pre[index];
            push(s, res);
        }
        index--;
        convertExpression(s, pre, pren);
    }
}

//MAIN
int main()
{
    stack s;
    s.top = -1; s.size = 50;
    
    string pre = "+*ab*cd";
    string post;
    unsigned long pren = pre.size();
    
    convertExpression(s, pre, pren);
    post = pop(s);
    cout << "Postfix:\n" << post << endl;
}
