//All possible DFTs - works for weakly connected 
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
int vertexInDegree(int G[][nv], int i, int v)
{
    if (i < nv)
        return G[i][v] + vertexInDegree(G, i+1, v);
    else return 0;
}

int vertexOutDegree(int G[][nv], int i, char v)
{
    if (i < nv)
        return G[v][i] + vertexOutDegree(G, i+1, v);
    else return 0;
}

void storeDegrees(int G[][nv], int in[], int out[])
{
    for (int i = 0; i < nv; i++) {
        in[i] = vertexInDegree(G, 0, i);
        out[i] = vertexOutDegree(G, 0, i);
    }
}

int findUnvisited(int visited[])
{
    for (int i = 0; i < nv; i++)
        if (visited[i] == 0) return i;
    return -1;
}

int numcount = 1;
void DFT(int G[][nv], int current, int visited[], char prev, int in[], int out[], int flag)
{
    if (current > -1) {
        visited[current] = 1;
        cout << char(current+65) << " ";
        if (flag) {
            for (int j = 0; j < nv; j++)
                if (G[current][j] && visited[j] != 1) {
                    DFT(G, j, visited, current+65, in, out, flag);
                    if (out[j] == 0) {
                        out[current]--;
                        in[j]--;
                        G[current][j] = 0;
                    }
                }
        }
        else {
            for (int j = nv-1; j >= 0; j--)
                if (G[current][j] && visited[j] != 1) {
                    DFT(G, j, visited, current+65, in, out, flag);
                    if (out[j] == 0) {
                        out[current]--;
                        in[j]--;
                        G[current][j] = 0;
                    }
                }
        }
        numcount++;
        if (prev == '\0')
            DFT(G, findUnvisited(visited), visited, '\0', in, out, flag);
    }
    else cout << endl;
}

void allDFT(int G[][nv], char start, int flag)
{
    int visited[nv] = {0};
    int in[nv] = {0}, out[nv] = {0};
    storeDegrees(G, in, out);
    DFT(G, start-65, visited, '\0', in, out, flag);
}

//MAIN
int main()
{
    string input = "BC,CE,,AC,D,"; //"BC,CE,,A,," //"BC,C,,E,,"
    inputMatrix(G, 0, input, 0);
    
    cout << "Directed:\n";
    printMatrix(G, 0, 0);
    
    cout << "\nAll DFTs:\n";
    char start = 'E';
    int out = vertexOutDegree(G, 0, start-65);
    int in = vertexInDegree(G, 0, start-65);
    
    for (int i = 0; i < out; i++)
        allDFT(G, start, 1);
    for (int i = 0; i < in; i++)
        allDFT(G, start, 0);
}


