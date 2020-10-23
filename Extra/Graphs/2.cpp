//Snakes and ladders problem
#include <iostream>
#include <queue>
using namespace std;

//special functions
int minThrows(int moves[], int N)
{
    int *visited = new int[N];
    for (int i = 0; i < N; i++)
        visited[i] = 0;
    
    queue<pair<int, int>> Q;
    visited[0] = 1;
    Q.push({0, 0});
    pair<int, int> vertex;
    
    while (!Q.empty()) {
        vertex = Q.front();
        int v = vertex.first;
        
        if (v == N-1) break;
        else {
            Q.pop();
            for (int i = v+1; i <= (v+6) && i < N; i++) {
                if (!visited[i]) {
                    pair<int, int> j;
                    j.second = vertex.second + 1;
                    visited[i] = 1;
                    
                    j.first = (moves[i] == -1) ? i : moves[i];
                    Q.push(j);
                }
            }
        }
    }
    
    return vertex.second;
}


//MAIN
int main()
{
    int N = 30;
    int moves[N];
    for (int i = 0; i < N; i++)
        moves[i] = -1;
    
    // Ladders
    moves[2] = 21;
    moves[4] = 7;
    moves[10] = 25;
    moves[19] = 28;
    
    // Snakes
    moves[26] = 0;
    moves[20] = 8;
    moves[16] = 3;
    moves[18] = 6;
    
    cout << "Minimum dice throws => " << minThrows(moves, N) << "\n";
    return 0;
}
