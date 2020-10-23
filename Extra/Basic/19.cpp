//Min number of swaps to sort array
#include <iostream>
#include <vector>
using namespace std;

// Function returns the minimum number of swaps required to sort the array
int minSwaps(vector<int> arr) {
    long n = arr.size();
    int ans = 0;            //return value
    
    //first -> value, second -> org position
    pair<int, int> arrPos[n];
    for (int i = 0; i < n; i++) {
        arrPos[i].first = arr[i];
        arrPos[i].second = i;
    }
    
    //sort
    sort(arrPos, arrPos+n);
    
    //new vector to keep track of visited - initially all false
    vector<bool> visited(n, false);
    for (int i = 0; i < n; i++) {
        if (visited[i] || arrPos[i].second == i+1)
            continue;
        else {
            int cycle_length = 0;
            int j = i;
            
            while (!visited[j]) {            //DFS
                visited[j] = true;
                j = arrPos[j].second;
                cycle_length++;
            }
            
            if (cycle_length > 0)
                ans += cycle_length - 1;
        }
    }
    
    return ans;
}

int main() {
    vector<int> input = {4, 3, 1, 2};
    cout << minSwaps(input);
}
