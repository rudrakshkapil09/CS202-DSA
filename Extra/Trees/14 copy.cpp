//Convert general tree from pointer representation to fc & ns
#include <iostream>
#include <vector>
using namespace std;

//struct definitions
typedef
struct gtnode {
    int data;
    vector<gtnode *> child;
} *GTPTR;

typedef
struct tnode {
    int data;
    int inn;
    struct tnode *fc;
    struct tnode *ns;
} *TPTR;

//printing output tree
void printSpaces(int count)
{
    for (int i = 0; i < count; i++)
        cout << "  ";
}

int lastGen(TPTR T)
{
    if (T) {
        if (T->fc) return 0;
        else return lastGen(T->ns);
    }
    else return 1;
}

void VRT(TPTR T, int count, int downflag)
{
    if (T) {
        printSpaces(count);
        if (lastGen(T) && downflag) {
            while (T) {
                cout << T->data << " ";
                T = T->ns;
            }
            cout << "\n";
            return;
        }
        cout << T->data << endl;
        VRT(T->fc, count+1, 1);
        VRT(T->ns, count, 0);
    }
}

GTPTR newNode(int x)
{
    GTPTR T = new gtnode;
    T->data = x;
    return T;
}

TPTR newnode(int x)
{
    TPTR T = new tnode;
    T->data = x;
    T->fc = T->ns = NULL;
    return T;
}

//convert
void convertTree(GTPTR T, GTPTR P, TPTR &O)
{
    if (T) {
        O = newnode(T->data);
        if (T->child.size())
            convertTree(T->child[0], T, O->fc);
        if (P != T) {
            TPTR O1 = O;
            for (int i = 1; i < P->child.size(); i++) {
                convertTree(P->child[i], P->child[i], O1->ns);
                O1 = O1->ns;
            }
        }
    }
}


//MAIN
int main()
{
    GTPTR T = newNode(1);
    T->child.push_back(newNode(2));
    T->child.push_back(newNode(3));
    T->child.push_back(newNode(4));
    T->child[0]->child.push_back(newNode(5));
    T->child[0]->child.push_back(newNode(6));
    T->child[1]->child.push_back(newNode(7));
    T->child[2]->child.push_back(newNode(8));
    T->child[2]->child.push_back(newNode(9));
    T->child[2]->child.push_back(newNode(10));
    
    TPTR O = NULL;
    convertTree(T, T, O);
    VRT(O, 0, 0);
}




