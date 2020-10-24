//DFT
#include <iostream>
using namespace std;
const int nv = 5;
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
int findUnvisited(int visited[])
{
    for (int i = 0; i < nv; i++)
        if (visited[i] == 0) return i;
    return -1;
}
int hasNext(int G[][nv], int visited[], int current)
{
    for (int i = 0; i < nv; i++)
        if (G[current][i] > 0 && visited[i] == 0)
            return 1;
    return 0;
}

int numcount = 1;
void DFT(int G[][nv], int current, int visited[], char prev)
{
    if (numcount <= nv) {
        visited[current] = 1;
        if (prev != '\0')
            cout << prev << "->" << char(current+65) << "\n";
        else if (!hasNext(G, visited, current))
            cout <<  char(current+65) << "\n";
        for (int j = 0; j < nv; j++)
            if (G[current][j] && visited[j] != 1)
                DFT(G, j, visited, current+65);
        numcount++;
        if (prev == '\0')
            DFT(G, findUnvisited(visited), visited, '\0');
    }
}


//MAIN
int main()
{
    string input = "BC,CE,,A,D,"; //"BC,CE,,A,," //"BC,C,,E,,"
    inputMatrix(G, 0, input, 0);
    
    cout << "Directed:\n";
    printMatrix(G, 0, 0);
    
    cout << "\nDFT:\n";
    int visited[nv] = {0};
    char start = 'A';
    DFT(G, start-65, visited, '\0');
    
}


