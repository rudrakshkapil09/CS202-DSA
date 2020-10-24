//All possible permutations of a word
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
void printList(int path[], string word)
{
    for (int i = 0; i < nv; i++) {
        (i == nv-1) ?
        cout << word[path[i]] << endl : cout << word[path[i]] << " ";
    }
}

int findUnvisited(int visited[])
{
    for (int i = 0; i < nv; i++)
        if (visited[i] == 0) return i;
    return -1;
}

void DFT(int G[][nv], int path[], int current, int visited[], char prev, int count, string word, int &number)
{
    if (current > -1) {
        visited[current] = 1;
        path[count++] = current;
        
        if (count == nv) {
            printList(path, word);
            number++;
        }
        else
            for (int j = 0; j < nv; j++)
                if (G[current][j] && visited[j] != 1)
                    DFT(G, path, j, visited, current+65, count, word, number);
        count--;
        visited[current] = 0;
    }
}

void allDFT(int G[][nv], int start, string word, int &number)
{
    int visited[nv] = {0}, path[nv] = {0};
    DFT(G, path, start, visited, '\0', 0, word, number);
}

string setGraph(int G[][nv])
{
    string input = "";
    for (int i = 0; i < nv; i++) {
        for (int j = 0; j < nv; j++) {
            if (i != j)
                input += char(j+65);
        }
        input += ",";
    }
    inputMatrix(G, 0, input, 0);
    printMatrix(G, 0, 0);
    return input;
}

void printPerms(int G[][nv], string word, int &count)
{
    for (int i = 0; i < word.size(); i++)
        allDFT(G, i, word, count);
}

//MAIN
int main()
{
    string word = "VERMA";  //ABCDE
    string input = setGraph(G);
    
    cout << "\nAll Permutations:\n";
    int count = 0;
    printPerms(G, word, count);
    cout << "\nTotal => " << count << endl;
    return 0;
}


