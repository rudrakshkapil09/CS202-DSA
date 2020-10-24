//multilevel with multilists
#include <iostream>
using namespace std;
char Lstring[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'X', 'Y', 'Z'};

union u {
    struct lnode *dlink = NULL;     //1
    char c;                  //0
};

typedef
struct lnode {
    int tag;
    union u data;
    struct lnode *next = NULL;
} *LPTR;
LPTR ML[26] = {NULL};

LPTR addPointer()
{
    LPTR T = new(lnode);
    T->tag = 1;
    T->next = NULL;
    T->data.dlink = NULL;
    return T;
}

int getIndex(char C)
{
    int i = 0;
    while (C != Lstring[i]) i++;
    return i;
}

void getNewList(char id, char list[])
{
    char x;
    cout << "Enter elements of list " << id << ": ";
    cin >> x;
    cin.getline(list, 50);
    cout << "Stored\n";
}

void rinputList(LPTR &L1, char input[50])
{
    static int index = 0;
    char ch = input[index++];
    char midlist[50] = {};
    
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
    else if (int(ch) > 64 && int(ch) < 91) {    //uppercase letter
        L1 = addPointer();
        
        if (!ML[getIndex(ch)]) {
            getNewList(ch, midlist);
            int index2 = index;
            index = 0;
            rinputList(L1->data.dlink, midlist);       //MIDLIST not inputting?
            index = index2;
            ML[getIndex(ch)] = L1->data.dlink;
        }
        else L1->data.dlink = ML[getIndex(ch)];
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
        else {
            cout << "{";
            rPrint(L1->data.dlink);
            cout << "}";
            rPrint(L1->next);
        }
    }
}

int main ()
{
    char choice, expression[50];
    //getting expression {aj{mBq}l{iLk{dh}R}sT}
    cout << "Do you wish to enter a new expression or use default? (N/D): ";
    cin >> choice;
    if (choice == 'N') {
        cout << "Enter expression: ";
        cin.getline(expression, 50);
    }
    else strcpy(expression, "{aj{mBq}l{iLk{dh}R}stR}");
    
    //creating ML list &
    choice = 'a';
    while (int(choice) < 65 || int(choice) > 90) {
        cout << "\nPlease enter a capital letter for the name of the first list: ";
        cin >> choice;
    }
    rinputList(ML[getIndex(choice)], expression);
    
    //printing
    choice = 'A';
    while (1) {
        cout << "\nEnter the name of list to print: ";
        cin >> choice;
        if (choice < 65 || choice > 90) break;
        if (ML[getIndex(choice)] == NULL) {
            cout << "No such list.\n";
            continue;
        }
        cout << "Elements of list " << choice << ": ";
        rPrint(ML[getIndex(choice)]);
    }
    return 0;
}
