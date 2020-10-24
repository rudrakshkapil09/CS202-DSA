//radix sort - array of linked lists
#include <iostream>
using namespace std;

typedef
struct lnode {
    int data;
    struct lnode *next;
} *LPTR;

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

void inputArrayFromBuckets(LPTR bucket[], int input[])
{
    int j = 0;                      //input array counter
    for (int i = 0; i < 10; i++)  //bucket counter
        while (bucket[i] != NULL)
            input[j++] = returnFromList(bucket[i]);
}

void radixSort(LPTR bucket[], int input[], int input_size)
{
    int i = 0, j = 0, digit = 1;
    while (digit < 1001) {
        j = 0;
        while (j < input_size) {
            i = (input[j]/digit)%10;
            addToEnd(bucket[i], input[j]);
            j++;
        }
        inputArrayFromBuckets(bucket, input);
        digit *= 10;
    }
}

int main()
{
    LPTR bucket[10] = {NULL};
    int size, input[20];
    //int input[10] = {786, 181, 202, 645, 193, 329, 864, 7, 148, 272};
    cout << "Enter number of integers: ";
    cin >> size;
    cout << "Enter list: ";
    for (int k = 0; k < size; k++)
        cin >> input[k];
    radixSort(bucket, input, 10);
    for (int k = 0; k < 10; k++)
        cout << input[k] << " ";
    cout << endl;
}
