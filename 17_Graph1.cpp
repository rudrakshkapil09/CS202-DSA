//Graphs - 2D array
#include <iostream>
using namespace std;
const int nv = 5;
int DG[nv][nv], UG[nv][nv];

//special functions
void printMatrix(int G[][nv], int i, int j)
{
    if (i < nv) {
        if (!i && !j) {
            cout << "  |";
            for (char k = 'A'; k < 'A' + nv; k++)
                cout << k << " ";
            cout << "\n--+---------";
        }
        
        if (j < nv) {
            if (!j) cout << "\n" << char(i+65) << " |";
            (G[i][j] > 0) ? cout << G[i][j] << " " : cout << "  ";
            printMatrix(G, i, j+1);
        }
        else printMatrix(G, i+1, 0);
    }
    else cout << "\n";
}

void inputMatrix(int G[][nv], int i, string input, int inputindex)
{
    if (i < nv) {
        while (1) {
            char ch = input[inputindex++];
            if (ch == '0') break;
            else G[i][ch-65] = 1;
        }
        inputMatrix(G, i+1, input, inputindex);
    }
}

int vertexOutDegree(int G[][nv], int i, char v)
{
    if (i < nv)
        return G[v-65][i] + vertexOutDegree(G, i+1, v);
    else return 0;
}

int vertexInDegree(int G[][nv], int i, int v)
{
    if (i < nv)
        return G[i][v-65] + vertexInDegree(G, i+1, v);
    else return 0;
}

//checking cyclic
int isCyclic(int G[][nv], int i, int j, int start, int flag, int counter)
{
    if (i < nv) {
        if (i == start) return 1;
        if (j < nv) {
            if (G[i][j]) {
                start = (flag) ? start : i;
                if (counter <= nv)
                    return isCyclic(G, j, 0, start, 1, counter+1);    //follow path
                else return 1;
            }
            else return isCyclic(G, i, j+1, start, flag, counter);
        }
        else return isCyclic(G, i+1, 0, start, 0, 0);
    }
    else return 0;
}

//MAIN
int main()
{
    string input_UG = "BCD0ACE0ABD0ACE0BD0";
    string input_DG = "B0C0D0E0B0";   //CD0AE0BD0E00    //D0CE0AD0E00
    inputMatrix(UG, 0, input_UG, 0);
    inputMatrix(DG, 0, input_DG, 0);
    
    cout << "Undirected:\n";
    printMatrix(UG, 0, 0);
    while (1) {
        char ch;
        cout << "Enter a vertex to print its degree: ";
        cin >> ch;
        if (ch == '0') break;
        cout << "Degree of " << ch << " => " << vertexOutDegree(UG, 0, ch) << endl;
    }
    
    cout << "\n\nDirected:\n";
    printMatrix(DG, 0, 0);
    while (1) {
        char ch;
        cout << "Enter a vertex to print its in-degree: ";
        cin >> ch;
        if (ch == '0') break;
        cout << "Degree of " << ch << " => " << vertexInDegree(DG, 0, ch) << endl;
    }
    
    cout << "\n\nThe graph is ";
    (isCyclic(DG, 0, 0, -1, 0, 0)) ? cout << "cyclic.\n" : cout << "acyclic.\n";
}


