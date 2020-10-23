//Sort an array of 0s, 1s and 2s
#include <iostream>
using namespace std;

//special functions
void printArray(int arr[], int n)
{
    cout << "The sorted array is:\n{";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        (i == n-1) ? cout << "}\n" : cout << ", ";
    }
}

void specialSort(int arr[], int n)
{
    int low = 0;
    int hi = n-1;
    int mid = 0;
    
    while (mid <= hi) {
        switch (arr[mid]) {
            case 0:
                if (arr[low] != arr[mid])
                    swap(arr[low], arr[mid]);
                mid++;
                low++;
                break;
            case 1:
                mid++;
                break;
            case 2:
                if (arr[hi] != arr[mid])
                    swap(arr[hi], arr[mid]);
                hi--;
                break;
        }
    }
}

//MAIN
int main()
{
    int input[] = {0, 1, 1, 0, 1, 2, 1, 2, 0, 0, 0, 1};
    int n = sizeof(input)/sizeof(int);
    
    specialSort(input, n);
    printArray(input, n);
    return 0;
}
