//k queues & stacks in single array
#include <iostream>
using namespace std;

const int k = 10;
class Stack {
public:
    int size;
    int top[k];
    int elements[k*k];
    
    void push(int x, int i)
    {
        if (top[i] == k)
            cout << "Stack full.\n";
        else {
            if (top[i] == -1)
                top[i] = i * k;
            else top[i]++;
            elements[top[i]] = x;
        }
    }
    
    int pop(int i)
    {
        if (top[i] % k == k-1)
            cout << "Stack empty.";
        else {
            int t = elements[top[i]];
            top[i]--;
            return t;
        }
        return -1;
    }
};

class Queue {
public:
    int size;
    int f[k];
    int r[k];
    int elements[k*k];  //10 queues of 10 elements each - 100 elements total
    
    void enqueue(int x, int i)
    {
        if ((r[i]+1) % size + i*k == f[i])
            cout << "Queue full.\n";
        else {
            if (f[i] == -1)    //queue empty
                f[i] = r[i] = i * k;
            else
                r[i] = (r[i]+1) % size;
            elements[r[i]] = x;
        }
    }
    
    int dequeue(int i)
    {
        if (f[i] == -1)
            cout << "Queue empty";
        else {
            int t = elements[f[i]];
            if (f[i] == r[i]) f[i] = r[i] = -1;
            else f[i] = (f[i]+1) % size;
            return t;
        }
        return -1;
    }
};

int main()
{
    Queue multi_queue;
    Stack multi_stack;
    multi_queue.size = k*k;
    multi_stack.size = k*k;
    
    for (int i = 0; i < 10; i++)
        multi_queue.f[i] = multi_queue.r[i] = multi_stack.top[i] = -1;
    
    multi_queue.enqueue(5, 4); //store 5 in the 5th queue (f[4] = r[4])
    multi_queue.enqueue(10, 4);
    cout << multi_queue.dequeue(4) << endl;
    cout << multi_queue.dequeue(4) << endl;
    cout << multi_queue.dequeue(4) << endl;
    
    
    multi_stack.push(40, 9);
    multi_stack.push(41, 9);
    cout << multi_stack.pop(9) << endl;
    cout << multi_stack.pop(9) << endl;
    cout << multi_stack.pop(9) << endl;
    
    return 0;
}
