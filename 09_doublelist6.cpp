//Radix sort - using linked queues
#include <iostream>
using namespace std;

//STRUCT DEFINITIONS
typedef
struct lnode {
    int data;
    struct lnode *next;
} *LPTR;

struct LQueue {
    LPTR f;
    LPTR r;
};

typedef
struct bnode {
    int bkno;
    struct LQueue *bkptr;
    struct bnode *bknext;
} *BPTR;

//QUEUE FUNCTIONS

void LaddAfter(LPTR &L, int x)
{
    LPTR T = new(lnode);
    T->data = x;
    if (L == NULL)
        L = T;
    else {
        L->next = T;
        L = T;
    }
}

void Lenqueue(LQueue *LQ, int x)
{
    int was_empty = 0;
    if (LQ->r == NULL) was_empty = 1;
    LaddAfter(LQ->r, x);
    if (was_empty) LQ->f = LQ->r;
}

int LqueueIsEmpty(LQueue *LQ)
{
    if (LQ->f == NULL)
        return 1;
    else return 0;
}

int LdeleteFirst(LPTR &L)
{
    int x = L->data;
    L = L->next;
    return x;
}

int Ldequeue(LQueue *LQ)
{
    if (LqueueIsEmpty(LQ)) {
        cout << "Queue empty.";
        return -1;
    }
    else {
        int is_one_element = 0;
        if (LQ->f == LQ->r)
            is_one_element = 1;
        int x = LdeleteFirst(LQ->f);
        if (is_one_element) LQ->f = LQ->r = NULL;
        return x;
    }
}

//other functions:
void setBuckets(BPTR &B)
{
    static int i = 0;
    if (i < 10) {
        B = new(bnode);
        B->bkno = i;
        B->bkptr = new(LQueue);
        B->bkptr->f = NULL;
        B->bkptr->r = NULL;
        B->bknext = NULL;
        i++;
        setBuckets(B->bknext);
    }
}

void getBkptr(BPTR B, BPTR &T, int i)
{
    if (B->bkno < i)
        getBkptr(B->bknext, T, i);
    else if (B->bkno == i)
        T = B;
}

void inputArrayFromBuckets(BPTR B, int input[], int k)
{
    if (B != NULL) {
        while (!LqueueIsEmpty(B->bkptr))
            input[k++] = Ldequeue(B->bkptr);
        inputArrayFromBuckets(B->bknext, input, k);
    }
}

//radix function
void radixSort(BPTR B, int input[], int input_size)
{
    int i = 0, j, digit = 1;
    BPTR T = NULL;
    while (digit < 1001) {
        j = 0;
        while (j < input_size) {
            i = (input[j]/digit) % 10;
            getBkptr(B, T, i);
            Lenqueue(T->bkptr, input[j]);
            j++;
        }
        inputArrayFromBuckets(B, input, 0);
        digit *= 10;
    }
}

//[MAIN]
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
