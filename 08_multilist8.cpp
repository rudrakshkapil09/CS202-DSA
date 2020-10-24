//palindrome
#include <iostream>
#include <cstring>
using namespace std;

//stack definition
class Stack {
private:
    int size;
    int top;
    char elements[100];
    
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
    
    char pop()
    {
        if (stackIsEmpty())
            cout << "Stack Empty.\n";
        else
            return elements[top--];
        return '0';
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

//Linked List definition
typedef
struct lnode {
    char word[20];
    struct lnode *next;
} *LPTR;

void addToEnd(LPTR &L, char x[])
{
    LPTR T = new(lnode);
    LPTR T2 = L;
    strcpy(T->word, x);
    T->next = NULL;
    if (L == NULL)
        L = T;
    else {
        while (T2->next != NULL)
            T2 = T2->next;
        T2->next = T;
    }
}

void rprint(LPTR L)
{
    if (L != NULL) {
        cout << L->word << ", ";
        rprint(L->next);
    }
}

void setString(char sentence[100], LPTR L)
{
    if (L != NULL) {
        strcat(sentence, L->word);
        setString(sentence, L->next);
    }
}

int setStack(char sentence[50], Stack s1)
{
    char x;
    for (int i = 0; i < strlen(sentence); i++) {
        s1.push(sentence[i]);
    }
    for (int i = 0; i < strlen(sentence); i++) {
        x = s1.pop();
        if (x != sentence[i])
            return 0;
    }
    return 1;
}

int main()
{
    LPTR L = NULL;
    Stack s(100, -1);
    char word[20], sentence[100];
    int n;
    cout << "Enter number of words: ";
    cin >> n;
    for (int i = 0; i <= n; i++) {
        cout << "Enter the word: ";
        cin.getline(word, 20);
        if (i != 0)
            addToEnd(L, word);
    }
    setString(sentence, L);
    if (setStack(sentence, s))
        cout << "Palindrome.\n";
    else
        cout << "Not.\n";
}
