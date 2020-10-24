//5.e) Checking whether the level order of a binary tree is a heap
//without using pos; move by 2*i+1 or 2 -i from i;
#include <iostream>
using namespace std;

//Linked List definition
typedef
struct lnode {
    int data;
    int pos;
    struct lnode *next;
} *LPTR;

//function definitions
void rprint(LPTR L)
{
    if (L != NULL) {
        cout << int(L->data) << ".";
        rprint(L->next);
    }
    else cout << endl;
}

int globalpos = 0;
void addToEnd(LPTR &L, int x)
{
    LPTR T = new(lnode);
    LPTR T2 = L;
    T->data = x;
    T->next = NULL;
    T->pos = globalpos++;
    if (L == NULL)
        L = T;
    else {
        while (T2->next != NULL)
            T2 = T2->next;
        T2->next = T;
    }
}

void inputLList(LPTR &L, int num[], int n)
{
    static int numindex = 0;
    cout << "Enter elements: ";
    while (numindex < n)
        addToEnd(L, num[numindex++]);
}

//special functions
LPTR getChild1(LPTR L)
{
    int pos = L->pos;
    while (L->next && L->pos != 2*pos+1)
        L = L->next;
    return L;
}

LPTR getChild2(LPTR L)
{
    int pos = L->pos;
    while (L->next && L->pos != 2*pos+2)
        L = L->next;
    return L;
}

int checkHeap(LPTR L, int max)
{
    if (L && (2*L->pos+2) < max) {
        if (L->data > getChild1(L)->data || L->data > getChild2(L)->data)
            return 0;
        else return checkHeap(L->next, max);
    }
    else return 1;
}

//MAIN
int main()
{
    LPTR L = NULL;
    int input[] = {3, 6, 4, 8, 9, 7, 5, 10, 18, 20, 15};
    inputLList(L, input, 11);
    rprint(L);
    if (checkHeap(L, 11))
        cout << "List is a heap.\n";
    else cout << "List is not a heap.\n";
}
