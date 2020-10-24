//Second shortest path - iterative
#include <iostream>
using namespace std;
const int nv = 7;

//struct defintions
int G[nv][nv];
typedef
struct lnode {
    char data;
    struct lnode *next;
} *LPTR;

//creation & printing functions
void printMatrix(int G[][nv], int i, int j)
{
    if (i < nv) {
        if (!i && !j) {
            cout << "  |";
            for (char k = 'A'; k < 'A' + nv; k++)
                cout << k << " ";
            cout << "\n––+–––––––––––––––––––––––––";
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
            else G[i][ch-65] = input[inputindex++]-'0';
        }
        inputMatrix(G, i+1, input, inputindex);
    }
}

//Shortest path
int nextVertex(int G[][nv], int vist[], int dist[], int current)
{
    int min = 999, next = -1;
    for (int j = 0; j < nv; j++) {
        if (G[current][j] > 0 && vist[j] != 1 && dist[j] < min) {
            min = dist[j];
            next = j;
        }
    }
    return next;
}

int pathindex = 0;
void printOutput(char prev[], char goal, char last, int path[])
{
    if (goal != '\0') {
        printOutput(prev, prev[goal-65], last, path);
        (goal != last) ? cout << goal << "->" : cout << goal << endl;
        path[pathindex++] = goal-65;
    }
}

int shortestPath(int G[][nv], int current, int goal, int path[], int first)
{
    int vist[nv] = {0}, dist[nv] = {999,999,999,999,999,999,999};
    char prev[nv] = {'\0'};
    dist[current] = 0;
    
    int flag = 1;
    while (1) {
        if (flag) {
            for (int j = 0; j < nv; j++) {
                if (G[current][j] <= 0)
                    continue;
                else if (G[current][j] + dist[current] < dist[j] && vist[j] == 0) {
                    dist[j] = G[current][j] + dist[current];
                    prev[j] = char(current+65);
                }
            }
            vist[current] = 1;
        }
        
        flag = 1;
        int next = nextVertex(G, vist, dist, current);
        if (next == -1)
            break;
        else if (next != goal)
            current = next;
        else if (prev[current] != '\0') {
            flag = 0;
            current = prev[current]-65;
        }
    }
    if (first) {
        printOutput(prev, goal+65, goal+65, path);
        cout << "Distance => " << dist[goal] << endl;
    }
    return dist[goal];
}

//MAIN
int main()
{
    string input = "B2C4D1,D3E9,F5,C2E2F8G4,G6,,F1,"; //"B2D1,D3E9,A4F5,C2E2F8G4,G6,,F1,"
    inputMatrix(G, 0, input, 0);
    G[1][4] = 10;
    cout << "Graph:\n";
    printMatrix(G, 0, 0);
    
    int path[nv] = {-1, -1, -1, -1, -1, -1, -1};
    char goal = 'F', start = 'A';
    cout << "\nShortest Path from " << start << " to " << goal << ":\n";
    shortestPath(G, start-65, goal-65, path, 1);
    
    int i = 1, sta = -1, end = -1, min = 999;
    while (path[i] != -1) {
        int j = G[path[i-1]][path[i]], distance;
        G[path[i-1]][path[i]] = 0;
        distance = shortestPath(G, start-65, goal-65, path, 0);
        if (distance < min) {
            min = distance;
            sta = path[i-1];
            end = path[i];
        }
        G[path[i-1]][path[i]] = j;
        i++;
    }
    
    cout << "\nSecond shortest path:\n";
    G[sta][end] = 0;
    shortestPath(G, start-65, goal-65, path, 1);
    
}



