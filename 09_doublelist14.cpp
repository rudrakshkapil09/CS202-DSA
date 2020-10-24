//flatten
#include <iostream>
using namespace std;

//struct definition
typedef
struct dnode {
    int data;
    struct dnode *right;
    struct dnode *left;
    struct dnode *dlink;
} *DPTR;

//special functions
DPTR addPointer(int num)
{
    DPTR T = new(dnode);
    T->right = NULL;
    T->left = NULL;
    T->dlink = NULL;
    T->data = num;
    return T;
}

void rinputList(DPTR &D1, int input[], int choicelist[], int n)
{
    static int index_num = 0, index_choice = 0;
    int num = input[index_num++];
    int choice = choicelist[index_choice++];
    
    if (index_num > n) return;
    if (choice == 0) {                       //no branch
        D1 = addPointer(num);
        rinputList(D1->right, input, choicelist, n);
    }
    else if (choice == 1) {                 //next list
        D1 = addPointer(num);
        rinputList(D1->dlink, input, choicelist, n);
        rinputList(D1->right, input, choicelist, n);
    }
    else                                //return to prev list
        return;
}

void rPrint(DPTR D1)
{
    if (D1 != NULL) {
        cout << D1->data << " ";
        if (D1->dlink)
            rPrint(D1->dlink);
        rPrint(D1->right);
    }
}

//[MAIN]
int main()
{
    DPTR D = NULL;
    int expression[] = {1, 2, 3, 4, 11, 12, 13, 111, 112, 113, 0, 14, 15, 0, 5, 6};
    int choice[] =     {0, 0, 0, 1,  0,  0,  1,   0,   0,   0,-1,  0,  0,-1, 0, 0};
    int n = sizeof(expression)/sizeof(expression[0]);
    
    rinputList(D, expression, choice, n);
    rPrint(D);
    return 0;
}
