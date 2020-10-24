//Huffman Code Tree
#include <iostream>
using namespace std;

//struct defintions
typedef
struct hctnode {
    struct hctnode *lchild;
    int freq;
    char data = '-';
    struct hctnode *rchild;
} *HCTPTR;

typedef
struct lnode {
    HCTPTR hctptr;
    struct lnode *next;
} *LPTR;

//special functions
LPTR sortedInsert(HCTPTR H, LPTR &L)
{
    if (L == NULL) {                        //first node
        L = new(lnode);
        L->next = NULL;
        L->hctptr = H;
    }
    
    else if (L->hctptr->freq >= H->freq) {   //add to front
        LPTR L1 = new(lnode);
        L1->next = L;
        L1->hctptr = H;
        L = L1;
    }
    
    else if (L->hctptr->freq < H->freq) {  //add in the middle
        LPTR L1 = L;
        LPTR L2 = new(lnode);
        L2->hctptr = H;
        L2->next = NULL;
        
        if (L1->next == NULL)
            return sortedInsert(H, L1->next);
        
        while (L1->next->hctptr->freq <= H->freq) {
            L1 = L1->next;
            if (L1->next == NULL)
                return sortedInsert(H, L1->next);
        }
        L2->next = L1->next;
        L1->next = L2;
    }
    return L;
}

void createList(LPTR &L, int input[], int size)
{
    static int inputindex = 0;
    if (inputindex < size) {
        char data = (input[inputindex++]);
        int freq = input[inputindex++];
        
        HCTPTR H = new(hctnode);
        H->data = data;
        H->freq = freq;
        H->rchild = H->lchild = NULL;
        sortedInsert(H, L);
        createList(L, input, size);
    }
}

LPTR removeFirst(LPTR &L)
{
    LPTR L1 = L;
    L = L->next;
    return L1;
}

HCTPTR createTree(LPTR &L)
{
    if (L->next) {
        LPTR LL = removeFirst(L);
        LPTR LR = removeFirst(L);
        
        HCTPTR H = new(hctnode);
        H->lchild = LL->hctptr;
        H->rchild = LR->hctptr;
        H->freq = H->lchild->freq + H->rchild->freq;
        
        sortedInsert(H, L);
        return createTree(L);
    }
    else return L->hctptr;
}

void printHCT(HCTPTR H, int sum)
{
    if (H != NULL) {
        printHCT(H->lchild, sum*10);
        if (H->data != '-')
            cout << H->data << " => " << sum << endl;
        printHCT(H->rchild, (sum * 10 + 1));
    }
}

void decodeTree(HCTPTR H, char order[], int n)
{
    static int indexorder = 0;
    static HCTPTR P = H;
    if (indexorder >= n) return;
    
    int dir = order[indexorder++] - '0';
    if (H->data == '-') {
        if (dir)
            decodeTree(H->rchild, order, n);
        else decodeTree(H->lchild, order, n);
    }
    else {
        cout << H->data << " ";
        indexorder--;
        decodeTree(P, order, n);
    }
}


//MAIN
int main()
{
    LPTR L = NULL;
    HCTPTR H = NULL;
    int input[20] = {'a', 25, 'm', 40, 'p', 10, 'j', 5, 's', 3, 't', 2, 'v', 50};
    char decode[23] = "1101111110001110000111";
    int n = sizeof(decode)/sizeof(decode[0]);
    
    createList(L, input, 14);
    H = createTree(L);
    printHCT(H, 0);
    cout << "\nDecoded => ";
    decodeTree(H, decode, n);
    cout << endl;
    
    return 0;
}




