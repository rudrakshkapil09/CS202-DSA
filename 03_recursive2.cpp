//recursive function to check whether an array is a palindrome
#include <iostream>
using namespace std;

//function declaration
int checkPalindrome(int [], int, int);
int inputArray(int []);
int list[20];

//[MAIN]
int main()
{
    int n = inputArray(list);
    int flag = checkPalindrome(list, n, 0);
    if (flag)
        cout << "The array is a palindrome.\n";
    else
        cout << "Not a palindrome.\n";
    
    return 0;
}

//function definition
int checkPalindrome(int a[], int n, int l)
{
    if (n == 0 || n == 1)
        return 1;
    if (l >= n)
        return 1;
    if (a[l] != a[n])
        return 0;
    return checkPalindrome(a, n-1, l+1);
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


