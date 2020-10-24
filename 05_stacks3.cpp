//postfix evaluation
#include <iostream>
using namespace std;

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

int main()
{
    Stack s1(50, -1);
    
    int i, op1, op2;
    char input[50];
    cout << "Enter postfix:\n";
    cin.getline(input, 50);
    
    i = 0;
    while (i < strlen(input)) {
        if (isdigit(input[i])) {
            s1.push(input[i] - '0');
        }
        else {
            op1 = s1.pop();
            op2 = s1.pop();
            s1.push(eval(op1, op2, input[i]));
        }
        i++;
    }
    
    cout << "Answer = " << s1.pop() << endl; //s1.pop() not working for some reason - fixed: char pop was declared not int
    
    return 0;
}
