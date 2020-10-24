//5.a) Constructing Huffman Code Tree to decode data
//0s not showing before
#include <iostream>
using namespace std;

//struct defintions
typedef
struct hctnode {
    struct hctnode *lchild;
    char data = '-';
    struct hctnode *rchild;
} *HCTPTR;

typedef
struct lnode {
    HCTPTR hctptr;
    struct lnode *next;
} *LPTR;

//special functions
void printArray(char sum[])
{
    for (int i = 0; sum[i] != '\0'; i++)
        cout << sum[i] - '0';
}

void printHCT(HCTPTR H, string sum)
{
    if (H != NULL) {
        printHCT(H->lchild, sum += "0");
        sum.resize(sum.size()-1);
        if (H->data != '-')
            cout << H->data << " => " << sum << endl;
        printHCT(H->rchild, (sum += "1"));
        sum.resize(sum.size()-1);
    }
}

int inpindex = 0;
void creator(HCTPTR &T, char input[])
{
    char ch = input[inpindex++];
    if (ch == '\0') return;
    
    if (!T) {
        T = new hctnode;
        T->lchild = T->rchild = NULL;
        T->data = '-';
    }
    
    if (isalpha(ch))
        T->data = ch;
    else if (ch == '1')
        creator(T->rchild, input);
    else
        creator(T->lchild, input);
}

//MAIN
int main()
{
    HCTPTR H = NULL;
    string s;
    char create1[] = "000a";
    char create2[] = "01g";
    char create3[] = "101t";
    char create4[] = "111d";
    
    creator(H, create1);
    inpindex = 0;
    creator(H, create2);
    inpindex = 0;
    creator(H, create3);
    inpindex = 0;
    creator(H, create4);
    inpindex = 0;
    
    printHCT(H, s);
    cout << endl;
    
    return 0;
}




