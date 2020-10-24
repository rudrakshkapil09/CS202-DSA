//quick sort on array
#include <iostream>
using namespace std;

//functions
int inputList(int list[])
{
    int n = 1, i = 0;
    cout << "Enter elements: ";
    while (1) {
        cin >> n;
        if (n == -1)
            break;
        list[i++] = n;
    }
    return i;
}

int partition(int list[], int l, int h)
{
    int p = list[l];
    int low = l+1;
    int high = h;
    
    while (low < high) {
        while (list[low] < p) low++;
        while (list[high] > p) high--;
        if (low < high)
            swap(list[low], list[high]);
    }
    swap(list[l], list[high]);
    return high;
}

void quickSort(int list[], int low, int high)
{
    if (low < high) {
        int j = partition(list, low, high);
        quickSort(list, low, j-1);
        quickSort(list, j+1, high);
    }
}

int main()
{
    int list[20];
    int n = inputList(list);
    quickSort(list, 0, n-1);
    
    cout << "Sorted:\n";
    for (int i = 0; i < n; i++)
        cout << list[i] << " ";
}
