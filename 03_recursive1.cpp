//recursive function to find sum of an array
#include <iostream>
using namespace std;


//function declaration
int sumArray(int [], int);
int inputArray(int []);
int list[20];

//[MAIN]
int main()
{
    int n = inputArray(list);
    int sum = sumArray(list, n);
    cout << "Sum = " << sum << endl;

    return 0;
}

//function definition
int sumArray(int a[], int n)
{
    if (n < 0)
        return 0;
    else
        return a[n] + sumArray(a, n-1);
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
