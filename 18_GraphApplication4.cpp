//Strongly connected components
#include <iostream>
using namespace std;
const int nv = 10;

//struct defintions
int G[nv][nv];

//creation functions
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
            if (ch == ',') break;
            else G[i][ch-65] = 1;
        }
        inputMatrix(G, i+1, input, inputindex);
    }
}

//special functions
void reverseGraph(int G[][nv]) {
    for (int i = 0; i < nv; i++)
        for (int j = 0; j < nv; j++) {
            if (G[i][j] == 1) {
                G[j][i] = 2;
                G[i][j] = 0;
            }
        }
}

int findMax(int arr[])
{
    int max = -1, pos = -1;
    for (int i = 0; i < nv; i++)
        if (arr[i] > max) {
            pos = i;
            max = arr[i];
        }
    return pos;
}

int findUnvisited(int visited[])
{
    for (int i = 0; i < nv; i++)
        if (visited[i] == 0) return i;
    return -1;
}

int numcount = 1;
void setNumbers(int G[][nv], int current, int visited[], int num[], char prev)
{
    if (numcount <= nv) {
        visited[current] = 1;
        int j;
        for (j = 0; j < nv; j++)
            if (G[current][j] && visited[j] != 1)
                setNumbers(G, j, visited, num, current+65);
        num[current] = numcount++;
        if (prev == '\0')
            setNumbers(G, findUnvisited(visited), visited, num, '\0');
    }
}

void printOutput(int G[][nv], int current, int num[], int count)
{
    if (current > -1) {
        num[current] = -1;
        int j;
        for (j = 0; j < nv; j++)
            if (G[current][j] && num[j] != -1) {
                cout << char(current+65) << "->";
                printOutput(G, j, num, count+1);
                break;
            }
        if (j == nv)
            cout << char(current+65) << endl;
        if (count <= nv)
            printOutput(G, findMax(num), num, count);
    }
}

void printList(int num[])
{
    for (int i = 0; i < nv; i++)
        cout << char(i+65) << "->" << num[i] << "   ";
    cout << endl << endl;
}

//MAIN
int main()
{
    string input = "BD,CF,ADE,E,,C,FH,FJ,H,I,";
    inputMatrix(G, 0, input, 0);
    
    cout << "Directed:\n";
    printMatrix(G, 0, 0);
    
    cout << "\nStrongly connected components:\n";
    int visited[nv] = {0};
    int num[nv] = {0};
    char start = 'B';
    setNumbers(G, start-65, visited, num, '\0');
    printList(num);
    reverseGraph(G);
    printOutput(G, findMax(num), num, 0);
}


