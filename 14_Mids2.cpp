//2. multilevel list with int, char and string
#include <iostream>
#include <string>
using namespace std;
char Lstring[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'X', 'Y', 'Z'};

union u {
    struct lnode *dlink = NULL;     //1 for dlink //2 for capslink
    char c;                         //0
    int num;                        //-1
    char s[50];                     //-2
};

typedef
struct lnode {
    int tag;
    struct lnode *next = NULL;
    union u data;
} *LPTR;
LPTR ML[26] = {NULL};

int *setDefault()
{
    int tag[50] = {-1, -1, 2, 1, -1, 0, 2, -2, 3, -1, 3};
    return tag;
}

LPTR addPointer()
{
    LPTR T = new (lnode);
    T->tag = 1;
    T->next = NULL;
    T->data.dlink = NULL;
    return T;
}

LPTR addNodeChar()
{
    char ch;
    cout << "Enter character: ";
    cin >> ch;
    LPTR L1 = new(lnode);
    L1->next = NULL;
    L1->data.c = ch;
    L1->tag = 0;
    return L1;
}

LPTR addNodeNum()
{
    int x;
    cout << "Enter integer: ";
    cin >> x;
    LPTR L1 = new(lnode);
    L1->next = NULL;
    L1->data.num = x;
    L1->tag = -1;
    return L1;
}

LPTR addNodeString()
{
    char s[50], x;
    cout << "Enter string: ";
    cin >> x;
    cin.getline(s, 50);
    LPTR L1 = new(lnode);
    L1->next = NULL;
    strcpy(L1->data.s, s);
    L1->tag = -2;
    return L1;
}

int getIndex(char C)
{
    int i = 0;
    while (C != Lstring[i]) i++;
    return i;
}

void getNewList(char id, int list[], int n)
{
    cout << "Enter tags of list " << id << ":\n  0 -> char\n -1 -> int\n -2 -> string\n  1 -> dlink\n  2 -> new list\n  3 -> end\nEnter => ";
    for (int i = 0; i <= n; i++)
        cin >> list[i];
    cout << "Stored\n";
}

void rinputList(LPTR &L1, int tag[])
{
    static int index = 0;
    int t = tag[index++];
    int midtag[50];
    char ch;
    int nmid, index2;
    
    switch (t) {
        case 0:
            L1 = addNodeChar();
            rinputList(L1->next, tag);
            break;
        case -1:
            L1 = addNodeNum();
            rinputList(L1->next, tag);
            break;
        case -2:
            L1 = addNodeString();
            rinputList(L1->next, tag);
            break;
        case 1:
            L1 = addPointer();
            cout << "Dlink\n";
            rinputList(L1->data.dlink, tag);
            cout << "Up\n";
            rinputList(L1->next, tag);
            break;
        case 2:
            cout << "Enter capital letter for new list: ";
            cin >> ch;
            L1 = addPointer();
            
            if (!ML[getIndex(ch)]) {
                cout << "Enter number of elements of list " << ch << ": ";
                cin >> nmid;
                
                getNewList(ch, midtag, nmid);
                index2 = index;
                index = 0;
                cout << "Dlink\n";
                rinputList(L1->data.dlink, midtag);
                cout << "Up\n";
                index = index2;
                ML[getIndex(ch)] = L1->data.dlink;
            }
            else
                L1->data.dlink = ML[getIndex(ch)];
            rinputList(L1->next, tag);
            break;
        case 3:
            break;
    }
}


void rPrint(LPTR L1)
{
    if (L1 != NULL) {
        if (L1->tag == 0) {
            cout << "'" << L1->data.c << "',";
            rPrint(L1->next);
        }
        else if (L1->tag == -1) {
            cout << L1->data.num << ",";
            rPrint(L1->next);
        }
        else if (L1->tag == -2) {
            int i = 0;
            while (i < strlen(L1->data.s))
                cout << L1->data.s[i++];
            cout << "\b,";
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

//main
int main ()
{
    int n;
    char choice1, choice2;
    //getting expression {aj{mBq}l{iLk{dh}R}sT}
    choice2 = 'a';
    while (int(choice2) < 65 || int(choice2) > 90) {
        cout << "Please enter a capital letter for the name of the first list: ";
        cin >> choice2;
    }
    
    cout << "Do you wish to enter a new tag expression or use default? (N/D): ";
    cin >> choice1;
    if (choice1 == 'N') {
        int expression[50];
        cout << "Enter number of elements: ";
        cin >> n;
        cout << "Enter expression: ";
        for (int i = 0; i < n; i++)
            cin >> expression[i];
        rinputList(ML[getIndex(choice2)], expression);
    }
    else {
        int expression[50] = {-1, -1, 2, 1, -1, 0, 2, -2, 3, -1, 3};
        rinputList(ML[getIndex(choice2)], expression);
    }
    
    //creating ML list &
    
    //printing
    choice2 = 'A';
    while (1) {
        cout << "\nEnter the name of list to print: ";
        cin >> choice2;
        if (choice2 < 65 || choice2 > 90) break;
        if (ML[getIndex(choice2)] == NULL) {
            cout << "No such list.\n";
            continue;
        }
        cout << "Elements of list " << choice2 << ":\n{";
        rPrint(ML[getIndex(choice2)]);
        cout << "}";
    }
    return 0;
}
//input (new line after each string):
//A D 15 8 C 6 -1 0 -1 -2 2 -1 3 7 p 3 .btech
//G 3 -1 0 -2 3 27 r .cse
//45 36 s G .nitw
//9
