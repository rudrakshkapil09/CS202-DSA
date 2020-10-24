//prefix evaluation
#include <iostream>
using namespace std;

//queue definition
union u {
    int num;        //tag - 0
    char sym;    //tag - 1
};

class Queue {
    int size;
    int f;
    int r;
    int tag[20];
    union u elements[20];
    
public:
    Queue(int size, int front, int rear)
    {
        this->size = size;
        f = front;
        r = rear;
    }
    
    void enqueue(int x, int id)
    {
        if ((r+1) % size == f)
            cout << "Queue full.\n";
        else {
            if (f == -1)      //queue empty
                f = 0;
            r = (r+1) % size;
            if (id == 0)
                elements[r].num = x;
            else if (id == 1)
                elements[r].sym = x;
            tag[r] = id;
        }
    }
    
    //for tag[] = 0
    int dequeue()
    {
        int t;
        
        if (f == -1)
            cout << "Queue empty";
        else {
            t = elements[f].num;
            if (f == r)
                f = r = -1;
            else
                f = (f+1) % size;
            return t;
        }
        return -1;
    }
    
    int queueHasOneElement()
    {
        if (f == r)
            return 1;
        return 0;
    }
    
    int getTag()
    {
        return tag[f];
    }
    
};

//function definition
int eval(char opt, int op2, int op1)
{
    switch (opt) {
        case '+': return (op2 + op1);
        case '-': return (op2 - op1);
        case '*': return (op2 * op1);
        case '/': return (op2 / op1);
        default: return 0;
    }
}


//[MAIN]
int main() {
    Queue q1(20, -1, -1);
    int inputNum = 1, id = -1, num, num2;
    char inputSym, opt;
    
    cout << "Enter prefix expression after each tag [0 - int : 1 - char] (end with 0 -1):\n";  //eg. 1 + 0 5 0 3 0 -1
    while (inputNum > 0) {
        cin >> id;
        if (id == 0) {
            cin >> inputNum;
            if (inputNum == -1)
                break;
            q1.enqueue(inputNum, 0);
        }
        else {
            cin >> inputSym;
            q1.enqueue(inputSym, 1);
        }
    }
    cout << "Prefix expression stored in queue.\n";
    
    while(!q1.queueHasOneElement()) {
        if (q1.getTag()) {
            opt = q1.dequeue();
            if (!q1.getTag()) {
                num = q1.dequeue();
                if (!q1.getTag()) {
                    num2 = q1.dequeue();
                    q1.enqueue(eval(opt, num, num2), 0);
                }
                else { q1.enqueue(opt, 1); q1.enqueue(num, 0); }
            }
            else q1.enqueue(opt, 1);
        }
        else {
            num = q1.dequeue();
            q1.enqueue(num, 0);
        }
    }
    
    cout << "\nAnswer = " << q1.dequeue() << endl;
    
    return 0;
}
