//Checking and printing Hamiltonian cycle
#include <iostream>
#include <vector>
using namespace std;
const int nv = 5;

//graph functions
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

void printVector(vector<char> arr)
{
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i];
        (i < arr.size()-1) ? cout << "->" : cout << "\n";
    }
}


//special functions
int findHamiltonian(int G[][nv], vector<char> &path, int visited[], int current, int start)
{
    visited[current] = 1;
    path.push_back(current+65);
    
    for (int j = 0; j < nv; j++) {
        if (G[current][j] && !visited[j]) {
            if (findHamiltonian(G, path, visited, j, start))
                return 1;
            path.resize(path.size()-1);
        }
    }
    if (G[current][start] && path.size() == nv) {
        path.push_back(start+65);
        return 1;
    }
    return 0;
}

//MAIN
int G[nv][nv];
int main()
{
    vector<char> path;
    string input = "BD,ACDE,BE,ABE,BCD,";
    int visited[nv] = {0};
    
    cout << "Graph:\n";
    inputMatrix(G, 0, input, 0);
    printMatrix(G, 0, 0);
    
    if (findHamiltonian(G, path, visited, 0, 0)) {
        cout << "\nHamiltonian cycle => ";
        printVector(path);
    }
    else cout << "\nNo Hamiltonian cycle present.\n";
    return 0;
}
