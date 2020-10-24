//B+ Tree with only node splitting
#include <iostream>
#include <iomanip>
using namespace std;
const int d = 2;
const int median = d;

//struct definitions;
typedef
struct bdnode {
    int count = 0;
    struct bdnode *ptr[2*d+1] = {NULL};
    int key[2*d+1] = {-1};
    int inn = 0;
    struct bdnode *lvptr = NULL;
} *BDPTR;

//singly linked list as a queue structs
typedef
struct lnode {
    BDPTR bdptr;
    struct lnode *next;
} *LPTR;

struct LQueue {
    LPTR f;
    LPTR r;
};

//LQueue functions
void LaddAfter(LPTR &L, BDPTR B)
{
    LPTR T = new(lnode);
    T->bdptr = B;
    if (L == NULL) L = T;
    else {
        L->next = T;
        L = T;
    }
}

void Lenqueue(LQueue &LQ, BDPTR B)
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

BDPTR LdeleteFirst(LPTR &L)
{
    BDPTR B = L->bdptr;
    L = L->next;
    return B;
}

BDPTR Ldequeue(LQueue &LQ)
{
    if (LqueueIsEmpty(LQ)) {
        cout << "Queue empty.";
        return NULL;
    }
    else {
        int is_one_element = 0;
        if (LQ.f == LQ.r)
            is_one_element = 1;
        BDPTR B = LdeleteFirst(LQ.f);
        if (is_one_element) LQ.f = LQ.r = NULL;
        return B;
    }
}

//print functions
int innindex = 0;
void setInorderIndex(BDPTR T)
{
    if (T) {
        for (int i = 0; i < 2*d; i++) {
            setInorderIndex(T->ptr[i]);
            T->inn = innindex++;
        }
    }
}

void setSpaces(int n1, int n2)
{
    for (int i = n2 + 1; i < n1; i++)
        cout << " " << setw(1);
}

int previnn = 1;
void printAsItIs(LQueue Q)
{
    if (!LqueueIsEmpty(Q)) {
        BDPTR T = Ldequeue(Q);
        if (T->inn == -1 && !LqueueIsEmpty(Q)) {
            cout << "\n";
            Lenqueue(Q, T);
            previnn = 0;
        }
        else {
            if (T->inn != -1) {
                setSpaces(T->inn, previnn);
                for (int i = 0; i < 2*d; i++)
                    (T->key[i] > 0) ? cout << "•" << T->key[i] << "" : cout << "•_";
                cout << "• ";
                previnn = T->inn;
            }
            for (int i = 0; i <= 2*d; i++) {
                if (T->ptr[i] != NULL)
                    Lenqueue(Q, T->ptr[i]);
            }
        }
        printAsItIs(Q);
    }
}

void printTree(BDPTR T)
{
    LQueue Q1;
    Q1.f = Q1.r = NULL;
    BDPTR D = new(bdnode);        //Dummy
    for (int i = 0; i < 2*d; i++)
        D->ptr[i] = NULL;
    D->inn = -1;
    
    setInorderIndex(T);
    Lenqueue(Q1, T);
    Lenqueue(Q1, D);
    printAsItIs(Q1);
    previnn = 0;
    innindex = 1;
    cout << endl << endl;
}

/*Special Functions*/
//Basic
BDPTR newNode(int k[], int n)   //for simple new node, n = 0. otherwise, T->count/2
{
    BDPTR T = new (bdnode);
    for (int i = 0; i < 2*d+1; i++)
        T->ptr[i] = NULL;
    for (int i = 0; i < n; i++)
        T->key[i] = k[i];
    return T;
}

//Searching functions
BDPTR searchParent(BDPTR T, int k)
{
    if (T->key[0] == k) return NULL;
    else {
        int i = 0;
        for(; i < T->count; i++)
            if (k < T->key[i]) break;
        if (T->ptr[i]->key[0] == k) return T;
        else return searchParent(T->ptr[i], k);
    }
}

BDPTR searchNode(BDPTR T, int k, int i)
{
    if (T && i <= 2*d) {
        if (T->key[i] < k && T->key[i] > 0)
            return searchNode(T, k, i+1);
        else if (T->key[i] == k) return T;
        else return searchNode(T->ptr[i], k, 0);
    }
    return T;
}

BDPTR searchLeaf(BDPTR T, int k, int i, BDPTR &P)
{
    if (T && i <= 2*d) {
        if (T->key[i] < k && T->key[i] > 0)
            return searchLeaf(T, k, i+1, P);
        else if (T->ptr[i]) {
            P = T;
            return searchLeaf(T->ptr[i], k, 0, P);
        }
        else
            return T;
    }
    return T;
}

//Sorting functions
BDPTR sortNode(BDPTR T, int i, int flag) {
    if (i < 2*d-flag) {
        if (T->key[i] > T->key[i+1] && T->key[i] > 0 && T->key[i+1] > 0) {
            while (T->key[i+1] < T->key[i]) {
                swap(T->key[i+1], T->key[i]);
                i--;
            }
        }
        else sortNode(T, i+1, flag);
    }
    return T;
}

BDPTR sortPointers(BDPTR &T, int i)
{
    if (T->ptr[i+1] && i < T->count) {
        if (T->ptr[i]->key[0] > T->ptr[i+1]->key[0]) {
            while (T->ptr[i]->key[0] > T->ptr[i+1]->key[0]) {
                swap(T->ptr[i+1], T->ptr[i]);
                i--;
            }
        }
        else sortPointers(T, i+1);
    }
    else if (i < 2*d-1) {
        swap(T->ptr[i+1], T->ptr[i+2]);
    }
    return T;
}

//Checking & extra functions
int nodeIsFull(BDPTR T)
{
    if (!T) return 0;
    if (T->count >= 2*d)
        return 1;
    else return 0;
}

void insertKey(BDPTR &T, int k)
{
    int i;
    for (i = 0; i < 2*d; i++)
        if (T->key[i] <= 0)
            break;
    T->key[i] = k;
    T->count++;
}

int findKey(BDPTR T, int k, int i)
{
    if (T->key[i] == k) return i;
    else
        return findKey(T, k, i+1);
}

//Node splitting
BDPTR createParent(BDPTR L, BDPTR R, int k)
{
    BDPTR P = newNode(NULL, 0);
    P->key[0] = k;
    P->count++;
    P->ptr[0] = L;
    P->ptr[1] = R;
    L->lvptr = R;
    return P;
}

BDPTR splitChild(BDPTR &Tleft, int &k)
{
    int *Trightarray = new int[Tleft->count/2];
    int j = 0;
    for (int i = median+1; i <= 2*d; i++) {
        Trightarray[j++] = Tleft->key[i];
        Tleft->key[i] = 0;
    }
    
    BDPTR Tright = newNode(Trightarray, Tleft->count/2);
    Tleft->count /= 2;
    Tright->count = Tleft->count;
    k = Tleft->key[median];
    Tleft->key[median] = 0;
    
    for (int i = d-1; i <= Tleft->count; i++)
        Tright->ptr[i] = Tleft->ptr[i+1];
    
    return Tright;
}

BDPTR addNode(BDPTR T, int k, BDPTR T2);
BDPTR nodeSplit(BDPTR T, BDPTR P, BDPTR L, int k, BDPTR T2)
{
    L->key[2*d] = k;
    L->count++;
    sortNode(L, 0, 0);
    BDPTR R = splitChild(L, k);     //k is median
    if (!T2) {
        insertKey(R, k);
        sortNode(R, 0, 0);
    }
    
    if (!P)
        return createParent(L, R, k);
    else {
        if (!nodeIsFull(P)) {
            insertKey(P, k);
            sortNode(P, 0, 1);
            int i = findKey(P, k, 0);
            for (i += 1; i <= 2*d; i++)
                if (!P->ptr[i]) break;
            P->ptr[i] = R;
            if (L->lvptr) {
                R->lvptr = L->lvptr;
                L->lvptr = R;
            } else L->lvptr = R;
            sortPointers(P, 0);
        }
        else {
            T = addNode(T, k, P);
            
            BDPTR Temp = NULL;
            if (P->ptr[T->count+1]) {
                Temp = P->ptr[P->count+1];
                P->ptr[P->count+1] = NULL;
                P->ptr[2*d] = NULL;
            }
            
            P = searchNode(T, k, 0);
            int i = findKey(P, k, 0);
            P->ptr[i] = L;
            P->ptr[i+1] = R;
            if (i != 0)
                P->ptr[0] = Temp;
            
            if (L->lvptr) {
                R->lvptr = L->lvptr;
                L->lvptr = R;
            } else L->lvptr = R;
        }
        return T;
    }
}

//Actual insertion function
BDPTR addNode(BDPTR T, int k, BDPTR T2)
{
    BDPTR P = T2, L;
    if (!T2)
        L = searchLeaf(T, k, 0, P);
    else {
        L = T2;
        P = searchParent(T, L->key[0]);
    }
    
    if (nodeIsFull(L)) {
        return nodeSplit(T, P, L, k, T2);
    }
    else if (!L) {
        L = newNode(NULL, 0);
        L->count++;
        L->key[0] = k;
        T = L;
    }
    else {
        insertKey(L, k);
        sortNode(L, 0, 1);
    }
    return T;
}

//printing leaves
void printLeaf(BDPTR T)
{
    if (!T) return;
    if (T->ptr[0])
        printLeaf(T->ptr[0]);
    else {
        for (int i = 0; i < T->count; i++)
            cout << T->key[i] << " ";
        printLeaf(T->lvptr);
    }
}

//inputting
BDPTR inputElements(BDPTR &T, int input[], int n)
{
    for (int i = 0; i < n; i++) {
        T = addNode(T, input[i], NULL);
        printTree(T);
        cout << "––––––––––––––––––\n";
    }
    return T;
}

//MAIN
int main()
{
    BDPTR T = NULL;
    //int input[] = {7, 2, 5, 9, 1, 6, 4, 8, 3, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int input[] = {6, 1, 9, 4, 8, 3, 7, 5, 2, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    T = inputElements(T, input, sizeof(input)/sizeof(input[0]));
    cout << endl;
    printLeaf(T);
    cout << endl;
    return 0;
}
