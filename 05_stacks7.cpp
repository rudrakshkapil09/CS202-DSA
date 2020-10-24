//two stacks in single array
#include <iostream>
using namespace std;

class Stack {
private:
    int size;
    int topF, topB;
    int elements[75];
    
public:
    //definitions should be outside class
    //constructor
    Stack(int s, int t)
    {
        size = s;
        topB = this->size;
        topF = t;
    }
    
    void pushF(int x)
    {
        if (stackIsFull())
            cout << "Stack Overflow.\n";
        else
            elements[++topF] = x;
        //(isStackFull()) ? cout << "Stack Overflow.\n" : elements[++top] = x;
    }
    
    void pushB(int x)
    {
        if (stackIsFull())
            cout << "Stack Overflow.\n";
        else
            elements[--topB] = x;
        //(isStackFull()) ? cout << "Stack Overflow.\n" : elements[++top] = x;
    }
    
    
    int popF()
    {
        if (stackIsEmpty()) {
            cout << "Stack Empty.\n";
            return -1;
        }
        return elements[topF--];
        //(stackIsEmpty()) ? cout << "Stack empty.\n" : return elements[top--];
    }
    
    int popB()      //when pop topB goes to right
    {
        if (stackIsEmpty()) {
            cout << "Stack Empty.\n";
            return -1;
        }
        return elements[topB++];
        //(stackIsEmpty()) ? cout << "Stack empty.\n" : return elements[top--];
    }
    
    
    int TopF()
    {
        if (stackIsEmpty()) {
            cout << "Stack Empty.\n";
            return -1;
        }
        else
            return elements[topF];
        //(stackIsEmpty()) ? cout << "Stack empty.\n" : return elements[top];
    }
    
    int TopB()
    {
        if (stackIsEmpty()) {
            cout << "Stack Empty.\n";
            return -1;
        }
        else
            return elements[topB];
        //(stackIsEmpty()) ? cout << "Stack empty.\n" : return elements[top];
    }
    
    
    int stackIsEmpty()
    {
        if (topF == 0 && topB == this->size) return 1;
        else return 0;
    }
    
    int stackIsFull()
    {
        if (topF == topB -1) return 1;
        else return 0;
    }
    
    int stackIsEmptyF()
    {
        if (topF < 0) return 1;
        else return 0;
        
    }
    
    int stackIsEmptyB()
    {
        if (topB > 74) return 1;
        else return 0;
    }
    
};


int main()
{
    Stack s1_s2(75, -1);
    
    cout << "Setting numbers 1 - 75 in elements: odd on left even on right.\n";
    for (int i = 1; i <= 75; i++) {
        if (i % 2 == 0)
            s1_s2.pushB(i);
        else
            s1_s2.pushF(i);
    }
    cout << "Elements set.\n\n";
    
    cout << "Odd numbers in decreasing order:\n";
    while (!(s1_s2.stackIsEmptyF()))
        cout << s1_s2.popF() << " ";
    cout << "\n\nEven numbers in decreasing order: ";
    while (!(s1_s2.stackIsEmptyB()))
        cout << s1_s2.popB() << " ";
    cout << endl;
    return 0;
}
