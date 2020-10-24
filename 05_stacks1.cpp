//printing digits using a stack

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

int main()
{
    //declaring & defining s1
    Stack s1(50, -1);
    
    //getting input
    int num;
    cout << "Enter the number: ";
    cin >> num;
    
    //pushing
    while (num != 0) {
        s1.push(num % 10);
        num /= 10;
    }
    //popping
    cout << "Digits stored in stack.\n";
    
    while (!s1.stackIsEmpty())
        cout << s1.pop();
    
    cout << endl;
    return 0;
}












