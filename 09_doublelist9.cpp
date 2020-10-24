//radix sort - without bucket numbers & buckets are linked lists
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
    struct bnode *bknext;
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

//special functions
void setBuckets(BPTR &B)
{
    static int i = 0;
    if (i < 10) {
        B = new(bnode);
        B->bkptr = NULL;
        B->bknext = NULL;
        i++;
        setBuckets(B->bknext);
    }
}

void getBkptr(BPTR B, BPTR &T, int i)
{
    for (int j = 0; j < i; j++)
        B = B->bknext;
    T = B;
}

void inputArrayFromBuckets(BPTR B, int input[], int k)
{
    if (B != NULL) {
        while (!(B->bkptr == NULL))
            input[k++] = returnFromList(B->bkptr);
        inputArrayFromBuckets(B->bknext, input, k);
    }
}

void radixSort(BPTR B, int input[], int input_size)
{
    int i = 0, j, digit = 1;
    BPTR T = NULL;
    while (digit < 1001) {
        j = 0;
        while (j < input_size) {
            i = (input[j]/digit) % 10;
            getBkptr(B, T, i);
            addToEnd(T->bkptr, input[j]);
            j++;
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
