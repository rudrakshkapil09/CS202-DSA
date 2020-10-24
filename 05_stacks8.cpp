//pop sequence
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
        else {
            elements[++top] = x;
            cout << 'S';
        }
        //(isStackFull()) ? cout << "Stack Overflow.\n" : elements[++top] = x;
    }
    
    char pop()
    {
        if (stackIsEmpty()) {
            cout << "Stack Empty.\n";
            return -1;
        }
        else {
            top--;
            return'X';
        }
        //(stackIsEmpty()) ? cout << "Stack empty.\n" : return elements[top--];
    }
    
    int Top()
    {
        if (stackIsEmpty()) {
            cout << "\nStack Empty.\n";
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
    Stack s1(10, -1);
    int push[6] = {1, 2, 3, 4, 5, 6}, pop[6] = {1, 5, 4, 6, 2, 3};
    int i = 0, j = 0;
    
    while (i < 6) {
        while (push[i] != pop[j])
            s1.push(push[i++]);
        s1.push(push[i++]);
        while (s1.Top() == pop[j]) {
            cout << s1.pop();
            j++;
        }
    }
    
    if (!s1.stackIsEmpty())
        cout << "\nNot a pop sequence.\n";
    else
        cout << "\nThis is a pop sequence.\n";
    return 0;
}
