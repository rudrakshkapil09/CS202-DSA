//radix sort - without bucket numbers & buckets are linked lists - more efficient by remembering the last position you just entered it into
#include <iostream>
using namespace std;

//struct definitions
typedef
struct lnode {
    int data;
    struct lnode *next;
} *LPTR;

typedef
struct bnode {
    LPTR bkptr;
    struct bnode *bkleft;
    struct bnode *bkright;
} *BPTR;

//list functions
void addToEnd(LPTR &L, int x)
{
    LPTR T = new(lnode);
    T->data = x;
    T->next = NULL;
    if (L == NULL)
        L = T;
    else {
        LPTR T2 = L;
        while (T2->next != NULL)
            T2 = T2->next;
        T2->next = T;
    }
}

int returnFromList(LPTR &L)
{
    int x = L->data;
    L = L->next;
    return x;
}

void addToEnd(BPTR &B)
{
    BPTR B1 = new(bnode);
    BPTR B2 = B;
    B1->bkright = NULL;
    B1->bkleft = NULL;
    if (B == NULL)
        B = B1;
    else {
        while (B2->bkright != NULL)
            B2 = B2->bkright;
        B2->bkright = B1;
        B1->bkleft = B2;
    }
}

//special functions
void setBuckets(BPTR &B)
{
    for (int i = 0; i < 10; i++)
        addToEnd(B);
}

void getBkptr(BPTR &B, BPTR &T, int i, int k)
{
    if (i > k)
        for (int j = k; j < i; j++)
            B = B->bkright;
    else
        for (int j = i; j < k; j++)
            B = B->bkleft;
    T = B;
}

void inputArrayFromBuckets(BPTR B, int input[], int k)
{
    if (B) {
        while (B->bkptr)
            input[k++] = returnFromList(B->bkptr);
        inputArrayFromBuckets(B->bkright, input, k);
    }
}

void radixSort(BPTR B, int input[], int input_size)
{
    int i = 0, j, digit = 1, k = 0;
    BPTR T = NULL;
    BPTR T2 = B;
    while (digit < 1001) {
        j = 0;
        while (j < input_size) {
            i = (input[j]/digit) % 10;
            getBkptr(T2, T, i, k);
            addToEnd(T->bkptr, input[j++]);
            k = i;
        }
        inputArrayFromBuckets(B, input, 0);
        digit *= 10;
    }
}

int main()
{
    BPTR B = NULL;
    setBuckets(B);
    int input[100] = {786, 181, 202, 645, 193, 329, 864, 7, 148, 272};
    radixSort(B, input, 10);
    for (int i = 0; i < 10; i++)
        cout << input[i] << " ";
    cout << endl;
}
