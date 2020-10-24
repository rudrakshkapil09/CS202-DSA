//bubble sort - 2 stacks 5 variable
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
        else
            return elements[top--];
        //(stackIsEmpty()) ? cout << "Stack empty.\n" : return elements[top--];
    }
    
    void removeElement()
    {
        elements[top--] = NULL;
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
    Stack s1(10, -1);
    Stack s2(10, -1);
    int list[5] = {3, 1, 4, 2, 6};
    
    cout << "The unsorted list is: ";
    for (int i = 0; i < 5; i++)
        cout << list[i] << " ";
    
    cout << "\nThe sorted list is: ";
    for (int i = 0; i < 5; i++) {
        if (s1.stackIsEmpty() || list[i] > s1.Top())
            s1.push(list[i]);
        else {
            while (list[i] < s1.Top()) {
                s2.push(s1.Top());
                s1.removeElement();
            }
            s1.push(list[i]);
            while (!(s2.stackIsEmpty())) {
                s1.push(s2.Top());
                s2.removeElement();
            }
        }
        
    }
    
    while (!(s1.stackIsEmpty()))
        cout << s1.pop() << " " ;
    
    cout << endl;
    return 0;
}

