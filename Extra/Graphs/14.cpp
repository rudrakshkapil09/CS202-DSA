//Boggle - graph method
#include <iostream>
#include <string>
using namespace std;
const int M = 3, N = 3;

string dictionary[] = {"GEEKS", "FOR", "QUIZ", "GO"};
int words = sizeof(dictionary)/sizeof(dictionary[0]);

//special functions
int isWord(string s)
{
    for (int i = 0; i < words; i++)
        if (dictionary[i] == s)
            return 1;
    return 0;
}

void findWords(char G[][N], int vist[][N], int i, int j, string str)
{
    vist[i][j] = 1;
    str += G[i][j];
    
    if (isWord(str))
        cout << str << "\n";
    for (int row = i-1; row <= i+1 && row < M; row++)
        for (int col = j-1; col <= j+1 && col < N; col++)
            if (row >= 0 && col >= 0 && !vist[row][col])
                findWords(G, vist, row, col, str);
    
    str.resize(str.size()-1);
    vist[i][j] = 0;
}

void checkAll(char G[][N])
{
    int visited[M][N] = {{0}};
    string s = "";
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            findWords(G, visited, i, j, s);
}

//MAIN
int main()
{
    char boggle[M][N] = {
        {'G','I','Z'},
        {'U','E','K'},
        {'Q','S','E'}
    };
    cout << "Words:\n";
    checkAll(boggle);
}
