//recursive function to find max and min of an array
#include <iostream>
using namespace std;

//function declaration
int inputArray(int []);
int getMin(int [], int, int, int);
int getMax(int [], int, int, int);
int list[20];

//[MAIN]
int main()
{
    int min, max, n;
    n = inputArray(list);
    min = getMin(list, n, 0, 10000);
    max = getMax(list, n, 0, 0);
    
    cout << "The maximum is: " << max << endl;
    cout << "The minimum is: " << min << endl;
    return 0;
}

//function definitions
int getMin(int a[], int n, int pos, int min)
{
    if (pos <= n) {
        if (a[pos] < min) {
            min = a[pos];
            return getMin(a, n, ++pos, min);
        }
    }
    return min;
    
}


int getMax(int a[], int n, int pos, int max)
{
    if (pos < n) {
        if (a[pos] > max) {
            max = a[pos];
            return getMax(a, n, ++pos, max);
        }
    }
    return max;
}

int inputArray(int a[])
{
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    
    for (int i = 0; i < n; i++)
        cin >> a[i];
    return n;
}
