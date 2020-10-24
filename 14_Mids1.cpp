//1. four field structure with key and heap_ptr
#include <iostream>
using namespace std;

struct heap_node{
    int data[50] = {0};
};

typedef
struct bstnode {
    struct bstnode *lchild;
    int key;
    struct heap_node *heap_ptr;
    struct bstnode *rchild;
} *BSTPTR;

//special functions
void heapify(int heap[], int n)
{
    if (n > 0) {
        if (heap[n] < heap[(n-1)/2]) {
            swap(heap[n], heap[(n-1)/2]);
            heapify(heap, (n-1)/2);
        }
    }
}

BSTPTR newNode(int k, int x)
{
    BSTPTR T = new(bstnode);
    T->key = k;
    T->heap_ptr = new(heap_node);
    T->heap_ptr->data[0] = x;
    T->lchild = T->rchild = NULL;
    return T;
}

int indexi = 0;
void create(BSTPTR &T, int k, int x)
{
    if (T) {
        if (k < T->key) create(T->lchild, k, x);
        else if (k > T->key) create(T->rchild, k, x);
        else {
            T->heap_ptr->data[indexi] = x;
            heapify(T->heap_ptr->data, indexi++);
        }
    }
    else {
        T = newNode(k, x);
        indexi++;
    }
}

void findNode(BSTPTR T, int k)
{
    if (T) {
        if (k < T->key) findNode(T->lchild, k);
        else if (k > T->key) findNode(T->rchild, k);
        else {
            int i = 0;
            cout << "Heap elements for key " << k << " => ";
            while (T->heap_ptr->data[i] != 0)
                cout << T->heap_ptr->data[i++] << " ";
        }
    }
    else cout << -1 << endl;
}

//MAIN
int main()
{
    BSTPTR T = NULL;
    for (int i = 10; i > 0; i--)
        create(T, 10, i);
    indexi = 0;
    for (int i = 10; i > 0; i--)
        create(T, 8, i);
    indexi = 0;
    for (int i = 10; i > 0; i--)
        create(T, 12, i);
    indexi = 0;
    for (int i = 10; i > 0; i--)
        create(T, 11, i);
    indexi = 0;
    
    findNode(T, 8);
}
