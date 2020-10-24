//Graph - Array of linked lists
#include <iostream>
using namespace std;
const int nv = 5;

//struct defintion
typedef
struct dtnode {
    char key;
    struct dtnode *next;
} *DTPTR ;

typedef
struct hdnode {
    char key;
    struct hdnode *hdlink;
    DTPTR dtlink;
} *HDPTR;

//special functions
void createHeaders(HDPTR &G, int i)
{
    if (i < nv) {
        if (!G) {
            G = new (hdnode);
            G->hdlink = NULL;
            G->dtlink = NULL;
            G->key = i + 65;
        }
        createHeaders(G->hdlink, i+1);
    }
}

DTPTR newNode(char ch)
{
    DTPTR D = new (dtnode);
    D->next = NULL;
    D->key = ch;
    return  D;
}

void addData(DTPTR &D, char ch)
{
    if (!D)
        D = newNode(ch);
    else addData(D->next, ch);
}

void inputList(HDPTR &G, string input, int i, int inputindex)
{
    if (i < nv) {
        while (1) {
            char ch = input[inputindex++];
            if (ch == '0') break;
            else addData(G->dtlink, ch);
        }
        inputList(G->hdlink, input, i+1, inputindex);
    }
}

void printLine(DTPTR D, int i)
{
    if (!D) return;
    else {
        if (D->key-65 == i) {
            cout << "1 ";
            printLine(D->next, i+1);
        }
        else {
            cout << "  ";
            printLine(D, i+1);
        }
    }
}

void printMatrix(HDPTR G, int i, int j, int start_flag)
{
    if (i >= nv || !G) return;
    if (start_flag) {
        cout << "  |";
        for (char k = 'A'; k < nv+65; k++)
            cout << k << " ";
        cout << "\n--+---------";
        printMatrix(G, i, j, 0);
    }
    else {
        cout << endl << G->key << " |";
        printLine(G->dtlink, 0);
        printMatrix(G->hdlink, i, 0, 0);
    }
}

int rcountOut(DTPTR D)
{
    if (!D) return 0;
    else return 1 + rcountOut(D->next);
}

int rcountIn(DTPTR D, char ch)
{
    if (!D) return 0;
    if (D->key == ch) return 1;
    return rcountIn(D->next, ch);
}

int vertexOutDegree(HDPTR G, char ch) {
    if (G->key != ch)
        return vertexOutDegree(G->hdlink, ch);
    else return rcountOut(G->dtlink);
}

int vertexInDegree(HDPTR G, int &deg, int ch) {
    if (G) {
        deg += rcountIn(G->dtlink, ch);
        return vertexInDegree(G->hdlink, deg, ch);
    }
    else return deg;
}

//cyclic
HDPTR findHead(HDPTR G, char ch)
{
    if (G->key == ch) return G;
    else return findHead(G->hdlink, ch);
}

int isCyclic(HDPTR orG, HDPTR G, char start, int flag, int ac_cnt, int loop_cnt)
{
    if (G && ac_cnt <= nv) {
        if (G->key == start) return 1;
        else {
            while (G->dtlink) {
                start = (flag) ? start : G->key;
                if (loop_cnt > nv) return 1;
                else {
                    int check = isCyclic(orG, findHead(orG, G->dtlink->key), start, 1, ac_cnt, loop_cnt+1);
                    if (G->dtlink) G->dtlink = G->dtlink->next;
                    return check;
                }
            }
            return isCyclic(orG, G->hdlink, -1, 0, ac_cnt+1, 0);
        }
    }
    else return 0;
}


//MAIN
int main()
{
    string input_UG = "BCD0ACE0ABD0ACE0BD0";
    string input_DG = "D0CE0AD0E00";   //BD0CE0AD0E00  //CD0AE0BD0E00 //D0CE0AD0E00
    //B0C0D0E0B0
    
    HDPTR UG = NULL, DG = NULL;
    createHeaders(UG, 0);
    createHeaders(DG, 0);
    
    inputList(UG, input_UG, 0, 0);
    inputList(DG, input_DG, 0, 0);
    
    cout << "Undirected:\n";
    printMatrix(UG, 0, 0, 1);
    while (1) {
        char ch;
        cout << "\nEnter a vertex to print its degree: ";
        cin >> ch;
        if (ch == '0') break;
        cout << "Degree of " << ch << " => " << vertexOutDegree(UG, ch) << endl;
    }
    
    cout << "\n\nDirected:\n";
    printMatrix(DG, 0, 0, 1);
    cout << endl;
    while (1) {
        char ch;
        int deg = 0;
        cout << "\nEnter a vertex to print its in-degree: ";
        cin >> ch;
        if (ch == '0') break;
        cout << "Degree of " << ch << " => " << vertexInDegree(DG, deg, ch) << endl;
    }
    
    cout << "\n\nThe graph is ";
    (isCyclic(DG, DG, -1, 0, 0, 0)) ? cout << "cyclic.\n" : cout << "acyclic.\n";
    
    return 0;
}


