//double ended queues
#include <iostream>
using namespace std;

//structs
typedef
struct dnode {
    struct dnode *left;
    int data;
    struct dnode *right;
} *DPTR;

struct DQ {
    DPTR fl;
    DPTR fr;
};

//special functions

void enqueueLeft(DQ &Q, int x) {
    if (!Q.fl) {
        DPTR D = new (dnode);
        D->data = x;
        D->left = D->right = NULL;
        Q.fl = Q.fr = D;
    }
    else {
        DPTR D = new (dnode);
        D->data = x;
        D->right = Q.fl;
        Q.fl->left = D;
        Q.fl = Q.fl->left;
    }
}

void enqueueRight(DQ &Q, int x) {
    if (!Q.fr) {
        DPTR D = new (dnode);
        D->data = x;
        D->left = D->right = NULL;
        Q.fl = Q.fr = D;
    }
    else {
        DPTR D = new (dnode);
        D->data = x;
        D->left = Q.fr;
        Q.fr->right = D;
        Q.fr = Q.fr->right;
    }
}

int dequeueLeft(DQ &Q) {
    if (!Q.fl) {
        cout << "Queue empty.\n";
        return -1;
    }
    else {
        int t = Q.fl->data;
        Q.fl = Q.fl->right;
        if (Q.fl) Q.fl->left = NULL;
        return t;
    }
}

int dequeueRight(DQ &Q) {
    if (!Q.fr) {
        cout << "Queue empty.\n";
        return -1;
    }
    else {
        int t = Q.fr->data;
        Q.fr = Q.fr->left;
        if (Q.fr) Q.fr->right = NULL;
        return t;
    }
}

//MAIN
int main()
{
    DQ Q;
    Q.fl = Q.fr = NULL;
    
    enqueueLeft(Q, 2);
    enqueueLeft(Q, 12);
    enqueueLeft(Q, 15);
    enqueueRight(Q, 100);
    //15 12 2 100
    
    cout << dequeueRight(Q) << " ";
    cout << dequeueLeft(Q) << " ";
    cout << dequeueRight(Q) << " ";
    cout << dequeueLeft(Q) << " ";
    dequeueLeft(Q);             //checking if empty
}
