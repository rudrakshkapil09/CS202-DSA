//balancing brackets - {([
#include <iostream>
using namespace std;

struct type{
    char bracket;
    int id;
};

class Stack {
public:
    int size;
    int top;
    struct type elements[50];
    
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
            elements[++top].bracket = x;
        //(isStackFull()) ? cout << "Stack Overflow.\n" : elements[++top] = x;
    }
    
    void setId(int x)
    {
        elements[top].id = x;
    }
    
    char pop()
    {
        if (stackIsEmpty()) {
            return -1;
        }
        return elements[top--].bracket;
        //(stackIsEmpty()) ? cout << "Stack empty.\n" : return elements[top--];
    }
    
    int Top()
    {
        if (stackIsEmpty()) {
            return -1;
        }
        else
            return elements[top].bracket;
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

int getId(char x)
{
    char list[11] = {'-', '{', '}', '(', '-', '[', ')', '-', '-' , '-', ']'};
    for (int i = 0; i < 11; i++)
        if (x == list[i])
            return i;
    return 0;
}

//[MAIN]
int main()
{
    Stack s1(50, -1);
    int isBalanced = 1, i;
    char input[50];
    cout << "Enter the brackets: \n";
    cin.getline(input, 50);
    
    i = 0;
    while (i < strlen(input)) {
        if (getId(input[i]) % 2 != 0) {     //open bracket
            s1.push(input[i]);              //push
            s1.setId(getId(input[i]));      //set its id
        }
        else {
            if (s1.elements[s1.top].id == getId(input[i])/2)    //if matching close bracket
                s1.pop();                               //pop out
            else {
                isBalanced = 0;                         //else unbalanced
                break;
            }
        }
        i++;
    }
    
    if (!(s1.stackIsEmpty()))
        isBalanced = 0;
    
    switch (isBalanced) {
        case 1: cout << "\nBalanced.\n"; break;
        case 0: cout << "\nNot balanced.\n"; break;
    }
    
    return 0;
}
