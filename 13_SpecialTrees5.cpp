// m-way search tree
#include <iostream>
#include <iomanip>
using namespace std;

//struct defintition
const int m = 3;
typedef
struct mtnode {
    int data[m] = {0};
    struct mtnode *dlink[m+1] = {NULL};
    int inn = 0;
} *MTPTR;

//singly linked list as a queue definitions
typedef
struct lnode {
    MTPTR MTPTR;
    struct lnode *next;
} *LPTR;

struct LQueue {
    LPTR f;
    LPTR r;
};

//LQueue functions
void LaddAfter(LPTR &L, MTPTR B)
{
    LPTR T = new(lnode);
    T->MTPTR = B;
    if (L == NULL) L = T;
    else {
        L->next = T;
        L = T;
    }
}

void Lenqueue(LQueue &LQ, MTPTR B)
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

MTPTR LdeleteFirst(LPTR &L)
{
    MTPTR B = L->MTPTR;
    L = L->next;
    return B;
}

MTPTR Ldequeue(LQueue &LQ)
{
    if (LqueueIsEmpty(LQ)) {
        cout << "Queue empty.";
        return NULL;
    }
    else {
        int is_one_element = 0;
        if (LQ.f == LQ.r)
            is_one_element = 1;
        MTPTR B = LdeleteFirst(LQ.f);
        if (is_one_element) LQ.f = LQ.r = NULL;
        return B;
    }
}


//special functions
MTPTR addNode(int key) {
    MTPTR T = new mtnode;
    T->data[0] = key;
    return T;
}

int nodeIsFull(MTPTR T) {
    if (T->data[m-1] <= 0 || T->data[m-1] >= 10000)
        return 0;
    else return 1;
}

int nodeIsEmpty(MTPTR T) {
    if (T->data[0] <= 0 || T->data[0] >= 10000)
        return 1;
    else return 0;
}

void insertNode(MTPTR &T, int key, int i) {
    if (T) {
        for (; T->data[i] < key; i++)
            if (T->data[i] <= 0)
                break;
        
        if (!nodeIsFull(T)) {
            for (int k = m; k > i; k--) {
                if (k < m) T->data[k] = T->data[k-1];
                T->dlink[k] = T->dlink[k-1];
            }
            T->data[i] = key;
        }
        else {
            if (key > T->data[m-1]) i = m;
            insertNode(T->dlink[i], key, 0);
        }
    }
    else T = addNode(key);
}

void createTree(MTPTR &T, int num[], int n)
{
    for (int i = 0; i < n; i++)
        insertNode(T, num[i], 0);
}

void findNode(MTPTR &T, int key, int i) {
    if (T && i <= m) {
        if (key > T->data[i])
            findNode(T, key, i+1);
        else if (key < T->data[i])
            findNode(T->dlink[i], key, 0);
        else
            cout << key << " is found.\n";
    }
    else cout << key << " is not found.\n";
}

void printSorted(MTPTR T, int i)
{
    if (T && i <= m) {
        printSorted(T->dlink[i], 0);
        if (T->data[i] > 0 && T->data[i] < 10000)   //for skipping garbage values
            cout << T->data[i] << " ";
        printSorted(T, i+1);
    }
}

void printDescending(MTPTR T, int i)
{
    if (T && i > -1) {
        printDescending(T->dlink[i], m);
        if (T->data[i-1] > 1 && T->data[i-1] < 10000)  //for skipping garbage values
            cout << T->data[i-1] << " ";
        printDescending(T, i-1);
    }
}

void deleteNode(MTPTR &T, int key, int i) {
    if (T && i <= m) {
        if (key > T->data[i])
            deleteNode(T, key, i+1);
        else if (key < T->data[i])
            deleteNode(T->dlink[i], key, 0);
        else {
            //left side
            if (T->dlink[i] != NULL) {
                int j = 0;
                while (T->dlink[i]->data[j] > 1 && T->dlink[i]->data[j] < 10000) j++;   //move till last element
                T->data[i] = T->dlink[i]->data[j-1];
                T->dlink[i]->data[j-1] = 0;
                
                if (T->dlink[i]->data[0] == 0)   //if last element
                    T->dlink[i] = NULL;
            }
            //right side
            else if (T->dlink[i+1] != NULL) {
                T->data[i] = T->dlink[i+1]->data[0];
                for (; i < m; i++) {
                    T->data[i] = T->data[i+1];          //fixing the dlink node after deletion
                    T->dlink[i] = T->dlink[i+1];
                }
                T->data[m-1] = 0;
                if (T->dlink[i]->data[0] == 0)                   //if last element was deleted
                    T->dlink[i] = NULL;                         //dlink[i] added in if condition
            }
            //neither
            else {
                for (; i <= m; i++) {
                    if (i < m) T->data[i] = T->data[i+1];
                    T->dlink[i] = T->dlink[i+1];
                }
                T->data[m-1] = 0;
                T->dlink[m] = NULL;
                if (nodeIsEmpty(T))
                    T = NULL;
            }
        }
    }
    else cout << "\n" << key << " is not present.\n";
}

//print functions
int innindex = 0;
void setInorderIndex(MTPTR T)
{
    if (T) {
        for (int i = 0; i < m; i++) {
            setInorderIndex(T->dlink[i]);
            T->inn = innindex++;
        }
    }
}

void setSpaces(int n1, int n2)
{
    for (int i = n2 + 1; i < n1; i++)
        cout << "" << setw(1);
}

int previnn = 0;
void printAsItIs(LQueue Q, MTPTR D)
{
    //static int prev = 0;
    if (!LqueueIsEmpty(Q)) {
        MTPTR T = Ldequeue(Q);
        if (T->inn == -1 && !LqueueIsEmpty(Q)) {
            cout << "\n";
            Lenqueue(Q, T);
            previnn = 0;
        }
        else {
            if (T->inn != -1) {
                setSpaces(T->inn, previnn);
                for (int i = 0; i < m; i++)
                    (T->data[i] != 0) ? cout << T->data[i] << " " : cout << "_ ";
                cout << " ";
                previnn = T->inn;
            }
            for (int i = 0; i <= m; i++) {
                if (T->dlink[i])
                    Lenqueue(Q, T->dlink[i]);
            }
        }
        printAsItIs(Q, D);
    }
}

void printTree(MTPTR T)
{
    LQueue Q1;
    Q1.f = Q1.r = NULL;
    MTPTR D = new(mtnode);        //Dummy
    for (int i = 0; i < m; i++)
        D->dlink[i] = NULL;
    D->inn = -1;
    
    setInorderIndex(T);
    Lenqueue(Q1, T);
    Lenqueue(Q1, D);
    printAsItIs(Q1, D);
    previnn = 0;
    innindex = 1;
    cout << endl << endl;
}


//MAIN
int main()
{
    MTPTR T = NULL;
    int input[] = {25, 90, 45, 15, 33, 30, 20, 36, 3, 120, 80, 75};
    createTree(T, input, 12);
    
    cout << "Ascending order:\n";
    printSorted(T, 0);
    cout << "\nDescending order:\n";
    printDescending(T, m);
    
    cout << endl << endl;
    findNode(T, 33, 0);
    findNode(T, 120, 0);
    findNode(T, 36, 0);
    findNode(T, 3, 0);
    
    cout << "\nTree after deletion of 36:\n";
    deleteNode(T, 36, 0);
    printTree(T);
    
    cout << "\nTree after deletion of 30:\n";
    deleteNode(T, 30, 0);
    printTree(T);
    
    cout << "\nTree after deletion of 33:\n";
    deleteNode(T, 33, 0);
    printTree(T);
    
    cout << "\nTree after deletion of 75:\n";
    deleteNode(T, 75, 0);
    printTree(T);
    
    cout << "\nTree after deletion of 80:\n";
    deleteNode(T, 80, 0);
    printTree(T);
    
    cout << "\nTree after deletion of 45:\n";
    deleteNode(T, 45, 0);
    printTree(T);
    
    cout << "\nTree after insertion of 65:\n";
    insertNode(T, 65, 0);
    printTree(T);
    
    cout << "\nTree after insertion of 50:\n";
    insertNode(T, 50, 0);
    printTree(T);
    cout << "\nTree after insertion of 75:\n";
    insertNode(T, 75, 0);
    printTree(T);
    cout << "\nTree after insertion of 119:\n";
    insertNode(T, 119, 0);
    printTree(T);
    cout << "\nTree after deletion of 90:\n";
    deleteNode(T, 90, 0);
    printTree(T);
    
    
    
    return 0;
}

