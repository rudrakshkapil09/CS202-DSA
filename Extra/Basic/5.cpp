//Rat in a maze
#include <iostream>
#include <vector>
using namespace std;

//special functions
void printPath(vector<pair<int, int>> path)
{
    cout << "Solution Found!\nPath => ";
    for (int i = 0; i < path.size(); i++) {
        cout << "(" << path[i].first << "," << path[i].second << ")";
        (i == path.size()-1) ? cout << "\n" : cout << " -> ";
    }
    
}

int findNext(int M[][5], int &i, int &j, int skip)
{
    int xMoves[4] = {1, 0, 0, -1};
    int yMoves[4] = {0, 1, -1, 0};
    
    for (int k = 0; k < 4; k++) {
        int x = xMoves[k];
        int y = yMoves[k];
        
        if (i+x >= 4 || j+y >= 5 || i+x < 0 || j+y < 0)
            continue;
        if (M[i+x][j+y] == 1 && !skip) {
            i += x;
            j += y;
            return 1;
        }
        else if (M[i+x][j+y] == 1) skip--;
    }
    return 0;
}

int ratInAMaze(int M[][5], vector<pair<int, int>> path, pair<int, int> solution, int i, int j)
{
    pair<int, int> current;
    current.first = i;
    current.second = j;
    path.push_back(current);
    
    if (i == solution.first && j == solution.second) {
        printPath(path);
        return 1;
    }
    else {
        M[i][j] = 2;
        int skip = 0;
        while (findNext(M, i, j, skip)) {
            if (ratInAMaze(M, path, solution, i, j))
                return 1;
            i = current.first;
            j = current.second;
            path.resize(path.size()-1);
            skip++;
        }
        return 0;
    }
}

//MAIN
int main()
{
    int maze[4][5] = {
        {1, 0, 1, 1, 0},
        {1, 1, 1, 0, 1},
        {0, 1, 0, 1, 1},
        {1, 1, 1, 1, 1}
    };
    
    vector<pair<int, int>> path;
    pair<int, int> solution;
    solution.first = 2;
    solution.second = 3;
    
    if (!ratInAMaze(maze, path, solution, 0, 0))
        cout << "No path found. :(\n";
}
