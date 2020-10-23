//Minimum number of operation required to convert number x into y
//using only *2 & -1
#include <iostream>
#include <queue>
#include <set>
using namespace std;

//struct defintion
struct node {
    int val;
    int dist;
};

//special functions
int BFS(int x, int y)
{
    set<int> visited;
    queue<node> Q;
    Q.push({x, 0});
    
    while (!Q.empty()) {
        node current = Q.front();
        visited.insert(current.val);
        Q.pop();
        
        if (current.val == y)
            return current.dist;
        if (current.val*2 == y || current.val-1 == y)
            return current.dist+1;
        
        if (visited.find(current.val*2) == visited.end())
            Q.push({current.val*2, current.dist+1});
        if (visited.find(current.val-1) == visited.end() && current.val-1 >= 0)
            Q.push({current.val-1, current.dist+1});
    }
    return 0;
}

//MAIN
int main()
{
    int x = 2, y = 5;
    cout << "Number of steps => " << BFS(x, y) << "\n";
}


