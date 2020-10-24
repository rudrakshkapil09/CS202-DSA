//kd tree
#include <iostream>
#include <iomanip>
using namespace std;
const int dim = 2;

//tree definition
typedef
struct kdnode
{
    int inn = 0;
    struct kdnode *lchild;
    int data[dim];
    struct kdnode *rchild;
} *KDPTR;

//singly linked list as a queue definitions
typedef
struct lnode {
    KDPTR KDPTR;
    struct lnode *next;
} *LPTR;

struct LQueue {
    LPTR f;
    LPTR r;
};

//LQueue functions
void LaddAfter(LPTR &L, KDPTR B)
{
    LPTR T = new(lnode);
    T->KDPTR = B;
    if (L == NULL) L = T;
    else {
        L->next = T;
        L = T;
    }
}

void Lenqueue(LQueue &LQ, KDPTR B)
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

KDPTR LdeleteFirst(LPTR &L)
{
    KDPTR B = L->KDPTR;
    L = L->next;
    return B;
}

KDPTR Ldequeue(LQueue &LQ)
{
    if (LqueueIsEmpty(LQ)) {
        cout << "Queue empty.";
        return NULL;
    }
    else {
        int is_one_element = 0;
        if (LQ.f == LQ.r)
            is_one_element = 1;
        KDPTR B = LdeleteFirst(LQ.f);
        if (is_one_element) LQ.f = LQ.r = NULL;
        return B;
    }
}

//print functions
int innindex = 1;
void setInorderIndex(KDPTR T)
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
        cout << " " << setw(3);
}

int previnn = 0;
void printAsItIs(LQueue Q)
{
    if (!LqueueIsEmpty(Q)) {
        KDPTR T = Ldequeue(Q);
        if (T->inn == -1 && !LqueueIsEmpty(Q)) {
            cout << "\n";
            Lenqueue(Q, T);
            previnn = 0;
        }
        else {
            if (T->inn != -1) {
                setSpaces(T->inn, previnn);
                for (int i = 0; i < dim; i++)
                    cout << T->data[i] << " ";
                previnn = T->inn;
            }
            if (T->lchild) Lenqueue(Q, T->lchild);
            if (T->rchild) Lenqueue(Q, T->rchild);
        }
        printAsItIs(Q);
    }
}

void printTree(KDPTR T)
{
    LQueue Q1;
    Q1.f = Q1.r = NULL;
    KDPTR D = new(kdnode);        //Dummy
    D->lchild = D->rchild = NULL;
    D->inn = -1;
    
    setInorderIndex(T);
    Lenqueue(Q1, T);
    Lenqueue(Q1, D);
    printAsItIs(Q1);
    previnn = 0;
    innindex = 1;
    cout << "\n–––––––––––––––\n";
}

//special functions
KDPTR newNode(int k[])
{
    KDPTR T = new(kdnode);
    T->lchild = T->rchild = NULL;
    for (int j = 0; j < dim; j++)
        T->data[j] = k[j];
    return T;
}

int findNode(KDPTR T, int data[], int i)
{
    if (T) {
        if (T->data[i] == data[i]) {
            int is_found = 1;
            for (int j = 0; j < dim; j++) {
                if (T->data[j] != data[j]) {
                    is_found = 0;
                    break;
                }
            }
            if (is_found) return 1;
        }
        if (data[i] < T->data[i])
            return findNode(T->lchild, data, (i+1) % dim);
        else return findNode(T->rchild, data, (i+1) % dim);
    }
    else return 0;
}

void create(KDPTR &T, int data[], int i)
{
    if (T) {
        if (data[i] < T->data[i])
            create(T->lchild, data, (i+1) % dim);
        else if (data[i] > T->data[i])
            create(T->rchild, data, (i+1) % dim);
        else if (findNode(T, data, 0))
            cout << "Duplicate data.\n";
    }
    else T = newNode(data);
}


int minimum = 999;
int findmin(KDPTR T, int d, int i)
{
    if(T) {
        if(T->data[d] < minimum)
            minimum = T->data[d];
        if(i != d) {
            findmin(T->lchild, d, (i+1) % dim);
            findmin(T->rchild, d, (i+1) % dim);
        }
        else
            findmin(T->lchild, d ,(i+1) % dim);
    }
    return minimum;
}

int maximum = -1;
int findmax(KDPTR T, int d, int i)
{
    if(T) {
        if(T->data[d] > maximum)
            maximum = T->data[d];
        if(i != d) {
            findmax(T->rchild, d, (i+1) % dim);
            findmax(T->lchild, d, (i+1) % dim);
        }
        else
            findmax(T->rchild, d ,(i+1) % dim);
    }
    return maximum;
}

void displayMinimums(KDPTR T)
{
    for (int i = 0; i < dim; i++) {
        cout << "Minimum of dimension " << i+1 << " => " << findmin(T, i, 0) << endl;
        minimum = 999;
    }
    cout << endl;
}

void displayMaximums(KDPTR T)
{
    for (int i = 0; i < dim; i++) {
        cout << "Maximum of dimension " << i+1 << " => " << findmax(T, i, 0) << endl;
        maximum = -1;
    }
    cout << endl;
}


//inputting function
KDPTR inputElements(KDPTR &T, int input[][dim], int n)
{
    for (int i = 0; i < n; i++) {
        create(T, input[i], 0);
        printTree(T);
    }
    return T;
}

//MAIN
int main()
{
    KDPTR T = NULL;
    int input[][dim] = {{20, 5}, {3, 18}, {70,15}, {10, 80}, {40, 30}, {80, 25}, {85, 2}, {25, 32}, {85, 2}};
    
    T = inputElements(T, input, 9);
    displayMinimums(T);
    displayMaximums(T);
    
    int a[dim] = {10, 80};
    if (findNode(T, a, 0))
        cout << "Found.\n";
    else cout << "Not found.\n";
    
    int b[dim] = {85, 22};
    if (findNode(T, b, 0))
        cout << "Found.\n";
    else cout << "Not found.\n";
    
}
