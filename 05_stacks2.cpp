//balancing symbols using a stack
#include <iostream>
using namespace std;

class Stack {
private:
    int size;
    int top;
    char elements[50];
    
public:
    //definitions should be outside class
    //constructor
    Stack(int s, int t)
    {
        size = s;
        top = t;
    }
    
    void push(char x)
    {
        if (stackIsFull())
            cout << "Stack Overflow.\n";
        else
            elements[++top] = x;
        //(isStackFull()) ? cout << "Stack Overflow.\n" : elements[++top] = x;
    }
    
    char pop()
    {
        if (stackIsEmpty()) {
            return -1;
        }
        return elements[top--];
        //(stackIsEmpty()) ? cout << "Stack empty.\n" : return elements[top--];
    }
    
    int Top()
    {
        if (stackIsEmpty()) {
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

int main()
{
    Stack s1(50, -1);
    
    int i, isBalanced = 1;
    char input[50];
    cout << "Enter the brackets: \n";
    cin.getline(input, 50);
    
    i = 0;
    while (i < strlen(input)) {
        switch (input[i]) {
            case '{':
                s1.push(input[i]);
                break;
            case '}':
                s1.pop();
                if (s1.pop() == -1) {
                    isBalanced = 0;
                }
                break;
        }
        i++;
    }
    
    if (!(s1.stackIsEmpty())) {
        isBalanced = 0;
    }
    
    switch (isBalanced) {
        case 1: cout << "\nBalanced.\n"; break;
        case 0: cout << "\nNot balanced.\n"; break;
    }
    
    return 0;
}







