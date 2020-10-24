//infix to prefix
#include <iostream>
using namespace std;

class Stack {
private:
    int size;
    int top;
    char elements[50];
    
public:
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
            elements[++top] = x;
    }
    
    void pop(char out[], int i)
    {
        if (stackIsEmpty())
            cout << "Stack Empty.\n";
        else
            out[i] = elements[top--];
        //(stackIsEmpty()) ? cout << "Stack empty.\n" : return elements[top--];
    }
    
    void removeBracket()
    {
        elements[top--] = NULL;
    }
    
    char Top()
    {
        if (stackIsEmpty()) {
            cout << "Stack Empty.\n";
            return '-';
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

int getStrength(char x)
{
    switch (x) {
        case '(': return 0;
        case '*': return 1;
        case '/': return 1;
        case '+': return 2;
        case '-': return 2;
        case ')': return 3;
        case 'w': return 4;
        default: return 0;
    }
}

int isStronger(char x, char y)      //1 if x stroger y
{
    int posx = getStrength(x);
    int posy = getStrength(y);
    return (posx < posy) ? 1 : 0;
}

void reverseString(char s[], int n)
{
    char s2[50];
    for (int i = 0; i < n; i++) {
        if (s[n-1-i] == '(')
            s2[i] = ')';
        else if (s[n-1-i] == ')')
            s2[i] = '(';
        else s2[i] = s[n-1-i];
    }
    for (int i = 0; i < n; i++)
        s[i] = s2[i];
}

//open bracket in stack - represent with w - done
//weaker getting stacked - done
//output is same as input
int main()
{
    Stack s1(50, -1);
    int i = 0, n = 0, index = 0;;
    char input[50], output[50];
    
    cout << "Enter infix (eg. a+c):\n";
    cin.getline(input, 50);
    while (input[n] != '\0')
        n++;
    
    reverseString(input, n);
    while (i < strlen(input)) {
        if (isalpha(input[i]))
            output[index++] = input[i];
        else
            switch (input[i]) {
                case '+':
                case '-':
                case '*':
                case '/':
                    if(s1.stackIsEmpty())
                        s1.push(input[i]);
                    else if (isStronger(input[i], s1.Top()))
                        s1.push(input[i]);
                    else {
                        while (!(isStronger(input[i], s1.Top()))) {
                            s1.pop(output, index);
                            index++;
                            if (s1.stackIsEmpty())
                                break;
                        }
                        s1.push(input[i]);
                    }
                    break;
                case '(':
                    if(s1.stackIsEmpty())
                        s1.push('w');   //represents weakest when inside stack
                    if (isStronger(input[i], s1.Top())) {
                        s1.push('w');
                    }
                    break;
                case ')':
                    while(s1.Top() != 'w') {  //loop till w reaches top
                        s1.pop(output, index++);
                        index++;
                    }
                    s1.removeBracket();
                    break;
                    
                default:
                    break;
                    
            }
        i++;
    }
    
    while(!(s1.stackIsEmpty())) {
        s1.pop(output, index);
        index++;
    }
    cout << endl;
    
    cout << "Prefix:\n";
    reverseString(output, index);
    for (int i = 0; i <= n; i++)
        cout << output[i];
    cout << endl;
    return 0;
}
