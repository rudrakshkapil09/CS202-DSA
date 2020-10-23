//Trapping Rain Water
#include <iostream>
using namespace std;

//special functions
int maxWater(int input[], int n)
{
    int *left = new int[n];
    int *right = new int[n];
    
    left[0] = input[0];
    for (int i = 1; i < n; i++)
        left[i] = max(left[i-1], input[i]);
    
    right[n-1] = input[n-1];
    for (int i = n-2; i >= 0; i--)
        right[i] = max(right[i+1], input[i]);
    
    int water = 0;
    for (int i = 0; i < n; i++)
        water += min(left[i], right[i]) - input[i];
    return water;
}

//MAIN
int main()
{
    //int input[] = {3, 0, 0, 2, 0, 4};
    int input[] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    int n = sizeof(input)/sizeof(int);
    
    cout << "Maximum water that can be collected => " << maxWater(input, n) << " units.\n";
}
