//Add two numbers whose digits are represented as a linked list
#include <iostream>
using namespace std;

//Linked List definition
typedef
struct lnode {
    int data;
    int carry = 0;
    struct lnode *next;
} *LPTR;

void rprint(LPTR L)
{
    if (L != NULL) {
        cout << int(L->data) << "";
        rprint(L->next);
    }
}

void addToEnd(LPTR &L, int x)
{
    LPTR T = new(lnode);
    LPTR T2 = L;
    T->data = x;
    T->next = NULL;
    if (L == NULL)
        L = T;
    else {
        while (T2->next != NULL)
            T2 = T2->next;
        T2->next = T;
    }
}

void inputLList(LPTR &L)
{
    int n = 1;
    cout << "Enter elements: ";
    while (n != -1) {
        cin >> n;
        if (n == -1)
            break;
        addToEnd(L, n);
    }
}

void addToFront(LPTR &L, int x, int carry)
{
    LPTR T = new(lnode);
    LPTR T2 = T;
    T->data = x;
    T->carry = carry;
    T->next = L;
    if (L != NULL)
        L = T2;
    else
        L = T;
}

//special functions
void rReverse(LPTR &L)
{
    if (L != nullptr) {
        rReverse(L->next);
        addToEnd(L, L->data);
        L = L->next;
    }
}

void Add(LPTR L1, LPTR L2, LPTR &SUM)
{
    if (L1 != NULL && L2 != NULL) {
        int sum = (L1->data + L2->data);
        int carry = sum/10;
        addToFront(SUM, sum%10, carry);
        if (SUM->next != NULL && SUM->next->carry) {
            if (SUM->data + 1 == 10) {
                SUM->carry = 1;
            }
            SUM->data = (SUM->data + 1) % 10;
        }
        Add(L1->next, L2->next, SUM);
    }
    else {
        int x = (SUM->carry) ? 1 : 0;
        if (L2 != NULL) {
            addToFront(SUM, L2->data, 0);
            Add(L1, L2->next, SUM);
            if (x) SUM->data++;
            
        }
        else if (L1 != NULL) {
            addToFront(SUM, L1->data, 0);
            Add(L1->next, L2, SUM);
            if (x) SUM->data++;
        }
    }
    if (SUM->carry) addToFront(SUM, 1, 0);
}

//[MAIN]
int main()
{
    LPTR L1 = NULL, L2 = NULL, SUM;
    inputLList(L1);
    rReverse(L1);
    inputLList(L2);
    rReverse(L2);
    Add(L1, L2, SUM);
    cout << "Sum => ";
    rprint(SUM);
    cout << endl;
    return 0;
}
