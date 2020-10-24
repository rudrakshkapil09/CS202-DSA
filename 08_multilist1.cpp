//multilevel list
#include <iostream>
using namespace std;

union u {
    struct lnode *dlink;     //1
    char c;                  //0
};

typedef
struct lnode {
    int tag;
    union u data;
    struct lnode *next;
} *LPTR;

LPTR addPointer()
{
    LPTR T = new(lnode);
    T->tag = 1;
    T->next = NULL;
    T->data.dlink = NULL;
    return T;
}

void rinputList(LPTR &L1, char input[50])
{
    static int index = 0;
    char ch = input[index++];
    
    if (int(ch) > 96 && int(ch) < 123) {      //lowercase letter
        L1 = new(lnode);
        L1->next = NULL;
        L1->data.c = ch;
        L1->tag = 0;
        rinputList(L1->next, input);
    }
    else if (int(ch) == 123) {           //opening curly bracket
        L1 = addPointer();
        rinputList(L1->data.dlink, input);
        rinputList(L1->next, input);
    }
    else                                //closing curly bracket
        return;
}

void rPrint(LPTR L1)
{
    if (L1 != NULL) {
        if (L1->tag == 0) {
            cout << L1->data.c;
            rPrint(L1->next);
        }
        else if (L1->tag == 1) {
            cout << "{";
            rPrint(L1->data.dlink);
            cout << "}";
            rPrint(L1->next);
        }
    }
}

int main ()
{
    LPTR L = NULL;
    char input[] = "{aj{mbq}l{ilk{dh}r}st}";
    rinputList(L, input);
    
    cout << "\nOutput =>\n";
    rPrint(L);
    cout << endl;
    return 0;
}
