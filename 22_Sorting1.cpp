//External Sort
#include <iostream>
#include <fstream>
using namespace std;
const int max_size = 3;

//special functions
void resetArray(int arr[])
{
    for (int i = 0; i < max_size; i++)
        arr[i] = 0;
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

void insertArray(fstream &file, int arr[], int n)
{
    for (int i = 0; i < n; i++)
        file << arr[i] << " ";
    file << "\n";
}

void choseElements(int A[], int B[], int C[])
{
    int count = 0, i = 0, j = 0;
    while (count < max_size) {
        C[count++] = ()
    }
}

//MAIN
int A[max_size], B[max_size], C[max_size];
int main ()
{
    fstream org, f1, f2, f3, f4;
    
    org.open("org.txt", ios::in);
    f1.open("file1.txt", ios::out);
    f2.open("file2.txt", ios::out);
    
    int flag = 1;
    while (!org.eof()) {
        for (int i = 0; i < max_size; i++)
            org >> A[i];
        insertionSort(A, max_size);
        (flag++ % 2) ? insertArray(f1, A, max_size) : insertArray(f2, A, max_size);
    }
    resetArray(A);
    
    int count = 0;
    while (count < 6) {
        for (int i = 0; i < max_size; i++) {
            f1 >> A[i];
            f2 >> B[i];
        }
        
    }
    
    
    
    
    org.close();
    f1.close();
    f2.close();
}

