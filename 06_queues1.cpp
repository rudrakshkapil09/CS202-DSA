//checking palindrome stack using queue
#include <iostream>
using namespace std;

//stack & queue definitions
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
    }
    
    int Top()
    {
        if (stackIsEmpty()) {
            cout << "Stack Empty.\n";
            return -1;
        }
        else
            return elements[top];
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


class Queue {
private:
    int size;
    int f;
    int r;
    int elements[10];
    
public:
    Queue(int size, int front, int rear)
    {
        this->size = size;
        f = front;
        r = rear;
    }
    
    void enqueue(int x)
    {
        if ((r+1) % size == f)
            cout << "Queue full.\n";
        else {
            if (f == -1)      //queue empty
                f = 0;
            r = (r+1) % size;
            elements[r] = x;
        }
    }
    
    int dequeue()
    {
        if (f == -1)
            cout << "Queue empty";
        else {
            int t = elements[f];
            if (f == r)
                f = r = -1;
            else
                f = (f+1) % size;
            return t;
        }
        return -1;
    }
};



//[MAIN]
int main() {
    Stack s1(10, -1);
    Queue q1(10, -1, -1);
    int n, input, flag = 1, mid, i;     //1 for palindrome, 0 for not
    
    cout << "Enter number of digits: ";
    cin >> n;
    cout << "Enter the number: ";
    cin >> input;
    
    for (i = 0; i < n; i++) {
        s1.push(input%10);
        input /= 10;
    }
    cout << "Number stored as a stack of digits.\n";
    
    
    cout << "Storing the digits in a queue...\n";
    for (i = 0; !s1.stackIsEmpty(); i++)
        q1.enqueue(s1.pop());
    cout << "Number stored as a queue of digits.\n";
    
    cout << "Dequeuing till midpoint and storing in stack.\n";
    mid = n % 2 == 0 ? n/2 : n/2 + 1;
    for (i = 0; i < mid; i++)
        s1.push(q1.dequeue());
    if (n % 2 != 0)
        s1.pop();
    
    while (!s1.stackIsEmpty())
        if (s1.pop() != q1.dequeue()) {
            flag = 0;
            break;
        }
    
    if (flag == 1)
        cout << "\nEntered number is a palindrome.\n";
    else
        cout << "\nEntered number is not a palindrome.\n";
    
    cout << endl;
    return 0;
}
