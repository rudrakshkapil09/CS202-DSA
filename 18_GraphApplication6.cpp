//Dijkstra's shortest path - recursive
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
int nextVertex(int G[][nv], int vist[], int dist[], int current, int j, int min, int next)
{
    if (j < nv) {
        if (G[current][j] > 0 && vist[j] != 1 && dist[j] < min)
            return nextVertex(G, vist, dist, current, j+1, dist[j], j);
        else return nextVertex(G, vist, dist, current, j+1, min, next);
    }
    else return next;
}

void printOutput(char prev[], char goal, char last)
{
    if (goal != '\0') {
        printOutput(prev, prev[goal-65], last);
        (goal != last) ? cout << goal << "->" : cout << goal << endl;
    }
}

void shortestPath(int G[][nv], int vist[], int dist[], char prev[], int current, int goal, int j, int flag)
{
    if (current != goal) {
        if (flag) {
            if (j < nv) {
                if (G[current][j] > 0 && G[current][j] + dist[current] < dist[j] && vist[j] == 0) {
                    dist[j] = G[current][j] + dist[current];
                    prev[j] = char(current+65);
                }
                shortestPath(G, vist, dist, prev, current, goal, j+1, flag);
            }
            vist[current] = 1;
        }
        
        int next = nextVertex(G, vist, dist, current, 0, 999, -1);
        if (next == -1)
            return;
        else if (next != goal)
            shortestPath(G, vist, dist, prev, next, goal, 0, 1);
        else if (prev[current] != '\0')
            shortestPath(G, vist, dist, prev, prev[current]-65, goal, 0, 0);
    }
}

//MAIN
int main()
{
    string input = "B2C4D1,D3E9,F5,C2E2F8G4,G6,,F1,"; //"B2D1,D3E9,A4F5,C2E2F8G4,G6,,F1,"
    inputMatrix(G, 0, input, 0);
    G[1][4] = 10;
    cout << "Graph:\n";
    printMatrix(G, 0, 0);
    
    char goal = 'F', start = 'B';
    int visited[nv] = {0}, distance[nv] = {999,999,999,999,999,999,999};
    char prev[nv] = {'\0'};
    distance[start-65] = 0;
    cout << "\nShortest Path from " << start << " to " << goal << ":\n";
    shortestPath(G, visited, distance, prev, start-65, goal-65, 0, 1);
    printOutput(prev, goal, goal);
    cout << "Distance => " << distance[goal-65] << endl;
}
