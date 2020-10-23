//Alien dictionary
#include <iostream>
#include <stack>
using namespace std;
const int nv = 4;

string dictionary2[] = {"caa", "aaa", "aab"};
string dictionary[] = {"baa", "abcd", "abca", "cab", "cad"};

//special functions
int getIndegree(int G[][nv], int i)
{
    int deg = 0;
    for (int j = 0; j < nv; j++)
        if (G[j][i])
            deg++;
    return deg;
}

void setDegrees(int G[][nv], int degrees[])
{
    for (int i = 0; i < nv; i++)
        degrees[i] = getIndegree(G, i);
}

int findStart(int degrees[])
{
    for (int i = 0; i < nv; i++)
        if (!degrees[i])
            return i;
    return -1;
}

void setGraph(int G[][nv])
{
    for (int i = 1; i < sizeof(dictionary)/sizeof(string); i++) {
        string word1 = dictionary[i-1];
        string word2 = dictionary[i];
        unsigned long n = (word1.size() < word2.size()) ? word1.size() : word2.size();
        
        for (int j = 0; j < n; j++) {
            if (word1[j] != word2[j]) {
                G[word1[j]-'a'][word2[j]-'a'] = 1;
                break;
            }
        }
    }
}

void topoSortUtil(int G[][nv], int i, int visited[], stack<int> &s)
{
    visited[i] = 1;
    for (int j = 0; j < nv; j++)
        if (G[i][j] && !visited[j])
            topoSortUtil(G, j, visited, s);
    s.push(i);
}

void topologicalSort(int G[][nv], int degrees[])
{
    int visited[nv];
    memset(visited, 0, sizeof(visited));
    stack<int> S;
    topoSortUtil(G, findStart(degrees), visited, S);
    
    while (!S.empty()) {
        cout << char(S.top()+'a') << " ";
        S.pop();
    }
    cout << "\n";
}

//MAIN
int main()
{
    int G[nv][nv], degrees[nv];
    memset(G, 0, sizeof(G));
    memset(degrees, 0, sizeof(degrees));
    
    setGraph(G);
    setDegrees(G, degrees);
    topologicalSort(G, degrees);
    return 0;
}
