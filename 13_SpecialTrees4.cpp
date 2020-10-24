//Heaps & heapsort
#include <iostream>
using namespace std;

//no struct defintion as
//heap is implemented as an array

//special functions
int percolate_up_count = 0;
void heapify(int heap[], int n)
{
    if (n > 0) {
        if (heap[n] < heap[(n-1)/2]) {
            swap(heap[n], heap[(n-1)/2]);
            percolate_up_count++;
            heapify(heap, (n-1)/2);
        }
    }
}

void createHeap(int heap[], int input[], int n_input)
{
    static int i = 0;
    if (i < n_input) {
        heap[i] = input[i];
        heapify(heap, i++);
        createHeap(heap, input, n_input);
    }
}

int percolate_down_count = 0;
void heapSort(int heap[], int n)
{
    if (n > 0) {
        cout << heap[0] << " ";
        heap[0] = heap[n-1];
        int i = 0;
        while (heap[i] > min(heap[2*i+1], heap[2*i+2]) && i < (n-1)/2) {
            int k = (heap[2*i+1] < heap[2*i+2]) ? 2*i+1 : 2*i+2;
            swap(heap[k], heap[i]);
            i = k;
            percolate_down_count++;
        }
        heapSort(heap, n-1);
    }
}

int checkHeap(int heap[], int n)
{
    if (n > 0) {
        if (heap[n] < heap[(n-1)/2])
            return 0;
        checkHeap(heap, n-1);
    }
    return 1;
}

//[MAIN]
int main()
{
    int H[50];
    int input[20] = {12, 7, 20, 40, 5, 18, 36, 2, 9};
    cout << "Original array:\n";
    for (int i = 0; i < 9; i++)
        cout << input[i] << " ";
    
    cout << "\nThe array is a heap -> ";
    if (checkHeap(input, 9))
        cout << "True\n";
    else cout << "False\n";
    
    createHeap(H, input, 9);
    cout << "\nElements of heap:\n";
    for (int i = 0; i < 9; i++)
        cout << H[i] << " ";
    cout << "\nThe array is a heap -> ";
    if (checkHeap(H, 9))
        cout << "True\n";
    else cout << "False\n";
    
    cout << "\nSorted:\n";
    heapSort(H, 9);
    cout << "\n\nNumber of up percolations => " << percolate_up_count;
    cout << "\nNumber of down percolations => " << percolate_down_count << endl;
}
