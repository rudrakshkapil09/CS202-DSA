//Minimum number of jumps to reach end
#include <iostream>
using namespace std;

//special functions
int findMin(int arr[], int n)
{
    if (n <= 1)
        return 0;
    if (!arr[0])
        return -1;
    
    int maxReach = arr[0];
    int step = arr[0];
    int jump = 1;
    
    for (int i = 1; i < n; i++) {
        if (i == n-1)
            return jump;
        
        maxReach = max(maxReach, i+arr[i]);
        step--;
        if (!step) {
            jump++;
            if (i >= maxReach)
                return -1;
            step = maxReach - i;
        }
    }
    return -1;
}

//MAIN
int main()
{
    int arr[] = {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9};
    cout << "Minimum steps => " << findMin(arr, sizeof(arr)/sizeof(int)) << "\n";
}

