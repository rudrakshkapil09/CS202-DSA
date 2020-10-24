 ]//AVL
#include <iostream>
using namespace std;

typedef
struct bstnode {
    struct bstnode *lchild;
    int data;
    int inn = 0;
    struct bstnode *rchild;
} *BSTPTR;

//singly linked list as a queue & stack definitions
typedef
struct lnode {
    BSTPTR BSTPTR;
    struct lnode *next;
} *LPTR;

struct LQueue {
    LPTR f;
    LPTR r;
};

//LQueue functions
void LaddAfter(LPTR &L, BSTPTR B)
{
    LPTR T = new(lnode);
    T->BSTPTR = B;
    if (L == NULL) L = T;
    else {
        L->next = T;
        L = T;
    }
}

void Lenqueue(LQueue &LQ, BSTPTR B)
{
    int was_empty = 0;
    if (LQ.r == NULL) was_empty = 1;
    LaddAfter(LQ.r, B);
    if (was_empty) LQ.f = LQ.r;
}

int LqueueIsEmpty(LQueue LQ)
{
    if (LQ.f == NULL)
        return 1;
    else return 0;
}

BSTPTR LdeleteFirst(LPTR &L)
{
    BSTPTR B = L->BSTPTR;
    L = L->next;
    return B;
}

BSTPTR Ldequeue(LQueue &LQ)
{
    if (LqueueIsEmpty(LQ)) {
        cout << "Queue empty.";
        return NULL;
    }
    else {
        int is_one_element = 0;
        if (LQ.f == LQ.r)
            is_one_element = 1;
        BSTPTR B = LdeleteFirst(LQ.f);
        if (is_one_element) LQ.f = LQ.r = NULL;
        return B;
    }
}


//printing functions
int innindex = 1;
void setInorderIndex(BSTPTR T)
{
    if (T != NULL) {
        setInorderIndex(T->lchild);
        T->inn = innindex++;
        setInorderIndex(T->rchild);
    }
}

void setSpaces(int n1, int n2)
{
    for (int i = n2 + 1; i < n1; i++)
        cout << " ";
}

int previnn = 0;
void printAsItIs(LQueue Q)
{
    if (!LqueueIsEmpty(Q)) {
        BSTPTR T = Ldequeue(Q);
        if (T->data == -1 && !LqueueIsEmpty(Q)) {
            cout << "\n";
            Lenqueue(Q, T);
            previnn = 0;
        }
        else {
            if (T->data != -1) {
                setSpaces(T->inn, previnn);
                cout << T->data;
                previnn = T->inn;
            }
            if (T->lchild) Lenqueue(Q, T->lchild);
            if (T->rchild) Lenqueue(Q, T->rchild);
        }
        printAsItIs(Q);
    }
}

void printTree(BSTPTR T)
{
    LQueue Q1;
    Q1.f = Q1.r = NULL;
    BSTPTR D = new(bstnode);        //Dummy
    D->lchild = D->rchild = NULL;
    D->data = -1;
    
    setInorderIndex(T);
    Lenqueue(Q1, T);
    Lenqueue(Q1, D);
    printAsItIs(Q1);
    previnn = 0;
    innindex = 1;
}

//special functions
//creation
int height(BSTPTR T)
{
    if (T)
        return 1 + max(height(T->lchild), height(T->rchild));
    else return -1;
}

int checkBalance(BSTPTR T)
{
    if (!T) return 1;
    else if (height(T->lchild) - height(T->rchild) > 1) return 0;  //left skew
    else if (height(T->rchild) - height(T->lchild) > 1) return -1;  //right skew
    else return 1;
}

int single_count = 0;
BSTPTR singleLeftRotate(BSTPTR K1, BSTPTR K2)
{
    K1->rchild = K2->lchild;
    K2->lchild = K1;
    cout << "[Single Left]\n";
    single_count++;
    return K2;
}

BSTPTR singleRightRotate(BSTPTR K1, BSTPTR K2)
{
    K1->lchild = K2->rchild;
    K2->rchild = K1;
    cout << "[Single Right]\n";
    single_count++;
    return K2;
}

int double_count = 0;
BSTPTR doubleRotate(BSTPTR K1, BSTPTR K2, BSTPTR K3)
{
    K1->rchild = K2->lchild;
    K2->lchild = K1;
    K3->lchild = K2->rchild;
    K2->rchild = K3;
    cout << "[Double]\n";
    double_count++;
    return K2;
}

BSTPTR checkTree(BSTPTR &T, int key, int flag)
{
    if (checkBalance(T) != 1) {
        BSTPTR K1 = T, K2 = NULL, K3 = NULL;
        if (checkBalance(T) == 0)
            K3 = K1->lchild;
        else K3 = K1->rchild;
        
        if ((!flag && key < K1->data && key < K3->data) || (flag && checkBalance(T) == 0))   //completely left skewed
            return singleRightRotate(K1, K3);
        else if ((!flag && key > K1->data && key > K3->data) || (flag && checkBalance(T) == -1))
            return singleLeftRotate(K1, K3);
        else {
            K2 = (K1->data < K3->data) ? K3->lchild : K3->rchild;
            return doubleRotate(K1, K2, K3);
        }
    }
    else return T;
}

BSTPTR insertNode(BSTPTR &T, int key)
{
    if (T) {
        if (key < T->data) T->lchild = insertNode(T->lchild, key);
        else if (key > T->data) T->rchild = insertNode(T->rchild, key);
        else cout << "Error: Duplicate data.\n";
        BSTPTR T1 = checkTree(T, key, 0);
        return T1;
    }
    else {
        T = new(bstnode);
        T->data = key;
        T->rchild = T->lchild = NULL;
        return T;
    }
}

//deletion
BSTPTR findMin(BSTPTR T) {
    if (T->lchild) return findMin(T->lchild);
    else return T;
}

BSTPTR findMax(BSTPTR T) {
    if (T->rchild) return findMax(T->rchild);
    else return T;
}

BSTPTR deleteNode(BSTPTR T, int key)
{
    if (!T) return NULL;
    if (T->data > key)
        T->lchild = deleteNode(T->lchild, key);
    else if (T->data < key)
        T->rchild = deleteNode(T->rchild, key);
    else {
        BSTPTR T1;
        if ((T->rchild && T->lchild) || T->rchild) {
            T1 = findMin(T->rchild);
            T->data = T1->data;
            T->rchild = deleteNode(T->rchild, T1->data);
        }
        else if (T->lchild) {
            T1 = findMax(T->lchild);
            T->data = T1->data;
            T->lchild = deleteNode(T->lchild, T1->data);
        }
        else T = NULL;
    }
    int k = (T) ? T->data : key;
    return checkTree(T, k, 1);
}

//inputting & deleting elements
void inputElements(BSTPTR &T, int input[], int n)
{
    for (int i = 0; i < n; i++) {
        cout << "Insertion of " << input[i] << endl;
        T = insertNode(T, input[i]);
        printTree(T);
        cout << "\n––––––––––––––––––\n";
    }
}

void deleteElements(BSTPTR &T, int input[], int n)
{
    for (int i = 0; i < n; i++) {
        cout << "Deletion of " << input[i] << endl;
        T = deleteNode(T, input[i]);
        printTree(T);
        cout << "\n––––––––––––––––––\n";
    }
}

//MAIN
int main()
{
    BSTPTR T = NULL;
    int input[] = {1, 2, 3, 4, 5, 6, 7, 15, 14, 13, 12, 11, 10, 9, 8};
    inputElements(T, input, sizeof(input)/sizeof(input[0]));
    cout << "Single => " << single_count << endl;
    cout << "Double => " << double_count << endl;
    
    cout << "\n––––––––––––––––––\n";
    int list[] = {12, 15, 8, 9, 11, 10, 13};
    deleteElements(T, list, sizeof(list)/sizeof(list[0]));
    return 0;
}
