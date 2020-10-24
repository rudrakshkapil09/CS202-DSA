//Ternary search trees
#include <iostream>
using namespace std;

typedef
struct tstnode{
    string ch;
    int end;
    struct tstnode *lchild;
    struct tstnode *dlink;
    struct tstnode *rchild;
} *TSTPTR;

/*Creation Functions*/
TSTPTR newNode(char ch)
{
    TSTPTR T = new (tstnode);
    T->ch = ch;
    T->end = 0;
    T->lchild = T->dlink = T->rchild = NULL;
    return T;
}

void insertKey(TSTPTR &T, string key, int i)
{
    if (i >= key.size())
        return;
    else if (!T && key[i] != '\0') {
        T = newNode(key[i]);
        insertKey(T->dlink, key, i+1);
        if (i+1 == key.size())
            T->end = 1;
    }
    else if (key[i+1] == '\0' && key[i] == T->ch[0])
        T->end = 1;
    else {
        if (key[i] < T->ch[0])
            insertKey(T->lchild, key, i);
        else if (key[i] > T->ch[0])
            insertKey(T->rchild, key, i);
        else
            insertKey(T->dlink, key, i+1);
    }
}

/*Searching Functions*/
int findKey(TSTPTR T, string key, int i)
{
    if (T && i < key.size()) {
        if (key[i] < T->ch[0])
            return findKey(T->lchild, key, i);
        else if (key[i] > T->ch[0])
            return findKey(T->rchild, key, i);
        else {
            if (T->end == 1 && (i+1 == key.size())) return 1;
            else return findKey(T->dlink, key, i+1);
        }
    }
    else {
        if (key.size() <= i) return 2;
        else return 0;
    }
}

void printFound(TSTPTR T, string key)
{
    cout << key;
    int f = findKey(T, key, 0);
    if (f == 1)
        cout << "\t => found.\n";
    else if (f == 2)
        cout << "\t => found (prefix).\n";
    else cout << "\t => not found.\n";
}

/*Printing Function*/
void printSorted(TSTPTR T, string out)
{
    if (T) {
        printSorted(T->lchild, out);
        if (T->end) {
            out += T->ch;
            cout << out << ", ";
            if (!T->dlink)
                out.resize(out.size()-1);
            else printSorted(T->dlink, out);
            out.resize(out.size()-1);
        }
        else {
            out += T->ch;
            printSorted(T->dlink, out);
            out.resize(out.size()-1);
        }
        printSorted(T->rchild, out);
    }
}

/*Deletion Functions*/
int hasSomePointer(TSTPTR T)
{
    if (T->lchild || T->rchild || T->dlink || T->end)
        return 1;
    else return 0;
}

int isRedundant(TSTPTR T, TSTPTR &N)
{
    if (T->dlink || T->end) return 0;
    else if (T->lchild && !T->rchild) {
        N = T->lchild;
        return 1;
    }
    else if (T->rchild && !T->lchild) {
        N = T->rchild;
        return 1;
    }
    else return 0;
}

void deleteKey(TSTPTR &T, string key, int i)
{
    if (!T) return;
    if (i < key.size() && (i != key.size()-1 || T->ch[0] != key[key.size()-1])) {
        if (T->ch[0] > key[i])
            deleteKey(T->lchild, key, i);
        else if (T->ch[0] < key[i])
            deleteKey(T->rchild, key, i);
        else
            deleteKey(T->dlink, key, i+1);
    }
    else if (T->ch[0] == key[i]) {
        T->end = 0;
    }
    TSTPTR N = NULL;
    if (!hasSomePointer(T))
        T = NULL;
    else if (isRedundant(T, N))
        T = N;
}

/*helper functions for main*/
void createTST(TSTPTR &T, string input[], int n)
{
    cout << "Insertion...\n";
    for (int i = 0; i < n; i++) {
        cout << input[i] << " inserted.\n";
        insertKey(T, input[i], 0);
    }
    cout << endl << endl;
}

void checkTST(TSTPTR T, string input[], int n)
{
    cout << "Searching...\n";
    for (int i = 0; i < n; i++)
        printFound(T, input[i]);
    cout << endl;
}

void deleteTST(TSTPTR &T, string input[], int n)
{
    cout << "Deletion...\n";
    for (int i = 0; i < n; i++) {
        cout << "\nDeletion of " << input[i] << ":\n";
        printFound(T, input[i]);
        deleteKey(T, input[i], 0);
        printSorted(T, "");
        cout << "\n";
        printFound(T, input[i]);
        if (!T) {
            cout << "\nTST no longer exists.\n";
            return;
        }
    }
}

//MAIN
int main()
{
    TSTPTR T = NULL;
    string input[] = {"cat", "apple", "apples", "app", "apply", "cow", "cower", "trot", "trap", "toilet", "trod", "carrot", "cats"};
    string del_input[] = {"apples", "cats", "app", "cow", "toilet", "trot", "trod", "trap", "apply", "apple", "cat", "carrot", "cower"};
    int num = sizeof(input)/sizeof(input[0]);
    
    //creating and searching
    createTST(T, input, num);
    checkTST(T, input, num);
    
    cout << "Searching for extras...\n";
    printFound(T, "catt");
    printFound(T, "ca");
    printFound(T, "c");
    printFound(T, "appl");
    printFound(T, "applo");
    printFound(T, "cowe");
    printFound(T, "cowerd");
    printFound(T, "ap");
    
    //printing in order
    cout << "\n\nLexographical order:\n";
    printSorted(T, "");
    cout << "\n\n\n";
    
    //deletion
    deleteTST(T, del_input, num);
    return 0;
}

