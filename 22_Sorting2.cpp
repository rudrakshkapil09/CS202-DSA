//Shell Sort
#include <iostream>
#include <vector>
using namespace std;

//special functions
void printArray(int arr[], int n)
{
    cout << "Array:\n{";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        (i != n-1) ? cout << ", " : cout << "}\n";
    }
}

void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i-1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

void shellSort(int arr[], int n)
{
    vector<int> indexes;
    int h = 1;
    for (int i = 0; h <= n; i++, h = 3*i+1)
        indexes.push_back(h);
    
    while (indexes.size()) {
        int jump = indexes.back();
        indexes.resize(indexes.size()-1);
        
        for (int i = 0; i+jump < n; i++)
            if (arr[i] > arr[i+jump])
                swap(arr[i], arr[i+jump]);
    }
    
    //final step:
    insertionSort(arr, n);
}

//MAIN
int main()
{
    int list[] = {15, 5, 9, 20, 32, 6, 8, 14, 27};
    int n = sizeof(list)/sizeof(list[0]);
    
    shellSort(list, n);
    printArray(list, n);
}
