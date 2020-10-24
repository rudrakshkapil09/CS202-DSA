/*Maps*/
//Max different numbers in root to leaf path
#include <iostream>
#include <map>
#include <queue>
using namespace std;

//tree defintion
typedef
struct btnode {
    struct btnode *lchild;
    int data;
    int inn;                    //in order number
    struct btnode *rchild;
} *BTPTR;

//tree printing
int innindex = 1;
void setInorderIndex(BTPTR T)
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
void printAsItIs(queue<BTPTR> Q)
{
    if (!Q.empty()) {
        BTPTR T = Q.front();
        Q.pop();
        if (T->data == -1 && !Q.empty()) {
            cout << "\n";
            Q.push(T);
            previnn = 0;
        }
        else {
            if (T->data != -1) {
                setSpaces(T->inn, previnn);
                cout << T->data;
                previnn = T->inn;
            }
            if (T->lchild) Q.push(T->lchild);
            if (T->rchild) Q.push(T->rchild);
        }
        printAsItIs(Q);
    }
}

void printTree(BTPTR T)
{
    queue<BTPTR> Q;
    BTPTR D = new(btnode);        //Dummy
    D->lchild = D->rchild = NULL;
    D->data = -1;
    
    cout << "Tree:\n";
    setInorderIndex(T);
    Q.push(T);
    Q.push(D);
    printAsItIs(Q);
    previnn = 0;
    innindex = 1;
    cout << "\n–––––––––––––––\n";
}

//creating tree
int deserialise(BTPTR &T, int data[])
{
    static int dataindex = 0;
    int ch = data[dataindex++];
    if (ch != -1) {
        T = new(btnode);
        T->data = ch;
        T->lchild = T->rchild = NULL;
        deserialise(T->lchild, data);
        deserialise(T->rchild, data);
    }
    return dataindex;
}

//special functions
int max_old = -1;
int getMax(BTPTR T, map<int, int> &m, string &path, string &max_path)
{
    if (T) {
        path += T->data + '0';
        m[T->data]++;
        int max_distinct = max(getMax(T->lchild, m, path, max_path), getMax(T->rchild, m, path, max_path));
        
        m[T->data]--;
        if (!m[T->data]) {
            m.erase(T->data);
            if (max_old < max_distinct)
                max_path = path;
        }
        (max_old < max_distinct) ? max_old = max_distinct : max_old = max_old;
        
        path.resize(path.size()-1);
        return max_distinct;
    }
    else return m.size();
}

//MAIN
int main()
{
    map <int, int> m1;
    string path = "", max_path = "";
    BTPTR T = NULL;
    int input[] = {1, 2, 4, -1, -1, 5, -1, -1, 3, 6, -1, 8, -1, -1, 3, -1, 9, -1, -1};
    
    deserialise(T, input);
    printTree(T);
    cout << "Max distinct path length => " << getMax(T, m1, path, max_path);
    cout << "\nPath => " << max_path << "\n";
}
