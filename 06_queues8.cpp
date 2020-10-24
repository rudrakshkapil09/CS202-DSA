//printing numbers' outputs according to corresponding tags
#include <iostream>
using namespace std;

//queue definition
struct type{
    char base;      //1
    int num;        //0
};

class Queue {
public:
    int size;
    int f;
    int r;
    int tag[20];
    struct type elements[20];
    
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
                elements[r].base = x;
            tag[r] = id;
        }
    }
    
    //for tag[] = 0
    int dequeueNum()
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
    
    //for tag[] = 1
    char dequeueBase()
    {
        char t;
        
        if (f == -1)
            cout << "Queue empty";
        else {
            t = elements[f].base;
            if (f == r)
                f = r = -1;
            else
                f = (f+1) % size;
            return t;
        }
        return -1;
    }
};


//function defintions
int convertRadix(int num, int x, int flag)
{
    int i = 0, digits[20] = {0};
    char hexAlpha[6] = {'A', 'B', 'C', 'D', 'E', 'F'};
    string list[10] = {"Zero ", "One ", "Two ", "Three ", "Four ", "Five ", "Six ", "Seven ", "Eight ", "Nine "};
    
    while (num > 0) {
        (num % x > 9) ? digits[i] = int(hexAlpha[num%16-10]) : digits[i] = num % x;
        num /= x;
        i++;
    }
    i--;
    for (; i >= 0; i--) {
        if (!flag)
            (digits[i] > 9) ? cout << char(digits[i]) : cout << digits[i];
        else
            cout << list[digits[i]];
    }
    
    return 0;
}

void eval(Queue q, char x, int num)
{
    switch (x) {
        case 'b': convertRadix(num, 2, 0); break;
        case 'o': convertRadix(num, 8, 0); break;
        case 'x': convertRadix(num, 16, 0);break;             //working
        case 'p': convertRadix(num, 10, 1);break;             //working
    }
}


//enqueue num followed by base - input
//[MAIN]
int main()
{
    Queue q1;
    q1.size = 20;
    q1.r = q1.f = -1;
    int inputNum = 1, id = -1, num;
    char inputBase, base;
    
    cout << "Input numbers followed by bases to convert to (end with 0 -1):\nb - binary\no - octal\nx - hexadecimal\np - print digits\neg. 0 12 1 b 0 15 1 x 0 8 1 o 0 123 1 p 0 -1\n\n";
    while (inputNum > 0) {
        cin >> id;
        if (id == 0) {
            cin >> inputNum;
            if (inputNum == -1)
                break;
            q1.enqueue(inputNum, 0);
        }
        else {
            cin >> inputBase;
            q1.enqueue(inputBase, 1);
        }
    }
    cout << "Stored in queue.\n";
    
    while (q1.f != q1.r) {
        cout << "\n\nConversion complete:\n";
        num = q1.dequeueNum();
        base = q1.dequeueBase();
        eval(q1, base, num);
    }
    cout << endl;
    return 0;
}
