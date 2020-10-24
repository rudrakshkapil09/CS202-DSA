//generic stack
#include <iostream>
using namespace std;

union u {
    int a;      //1
    float c;    //2
    char d;     //3
    char b[20]; //4
};

struct Gstack {
    int tag[50] = {0};
    u elements[50];
    int top;
    int size;
};

int stackIsFull(Gstack s)
{
    if (s.top >= s.size - 1) return 1;
    else return 0;
}

int stackIsEmpty(Gstack s)
{
    if (s.top < 0) return 1;
    else return 0;
}

void push(Gstack &s, int x) {
    if (stackIsFull(s))
        cout << "Stack Overflow.\n";
    else {
        s.elements[++s.top].a = x;
        s.tag[s.top] = 1;
    }
}

void push(Gstack &s, float x) {
    if (stackIsFull(s))
        cout << "Stack Overflow.\n";
    else {
        s.elements[++s.top].c = x;
        s.tag[s.top] = 2;
    }
}

void push(Gstack &s, char x) {
    if (stackIsFull(s))
        cout << "Stack Overflow.\n";
    else {
        s.elements[++s.top].d = x;
        s.tag[s.top] = 3;
    }
}

void push(Gstack &s, char x[]) {
    if (stackIsFull(s))
        cout << "Stack Overflow.\n";
    else {
        s.top++;
        strcpy(s.elements[s.top].b, x);
        s.tag[s.top] = 4;
    }
}

void pop(Gstack &s) {
    if (stackIsEmpty(s))
        cout << "Stack Empty.\n";
    else {
        if (s.tag[s.top] == 1)
            cout << s.elements[s.top--].a << ", ";
        else if (s.tag[s.top] == 2)
            cout << s.elements[s.top--].c << ", ";
        else if (s.tag[s.top] == 3)
            cout << s.elements[s.top--].d << ", ";
        else if (s.tag[s.top] == 4) {
            cout << s.elements[s.top--].b;
            //s.top--;
            cout << " ";
        }
    }
}

void addElement(Gstack &s)
{
    int choice = 0;
    int int_input;
    float float_input;
    char char_input, string_input[20];
    string_input[0] = 'a';
    cout << "\nWhat type of data would you like to enter?\n1) int\n2) float\n3) char\n4) string\nEnter choice => ";
    cin >> choice;
    cout << "Enter the input: ";
    switch (choice) {
        case 1:
            cin >> int_input;
            push(s, int_input);
            break;
        case 2:
            cin >> float_input;
            push(s, float_input);
            break;
        case 3:
            cin >> char_input;
            push(s, char_input);
            break;
        case 4:
            for (int i = 1; string_input[i-1] != '.'; i++)
                cin >> string_input[i];
            push(s, string_input);
        default:
            break;
    }
}

void printStack(Gstack &s)
{
    while (!stackIsEmpty(s))
        pop(s);
}

int main()
{
    Gstack s1;
    s1.size = 50;
    s1.top = -1;
    int choice = 0;
    
    while (choice != 3) {
        cout << "\n1) Add new element\n2) Print entire stack\n3) Quit\nEnter choice => ";
        cin >> choice;
        switch (choice) {
            case 1: addElement(s1); break;
            case 2: printStack(s1); cout << endl; break;
            case 3: break;
        }
    }
    
}
