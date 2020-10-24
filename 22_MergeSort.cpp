//Merge Sort
#include <iostream>
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

void merge(int arr[], int l, int m, int r)
{
    //sizes
    int n1 = m-l+1;
    int n2 = r-m;
    
    //copy contents
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[l+i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m+1+j];
    
    //sorted merge
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    //leftovers
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r) {
        int m = (l+r)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

//MAIN
int main()
{
    int input[] = {12, 11, 13, 5, 6, 7};
    mergeSort(input, 0, 5);
    printArray(input, 6);
}
