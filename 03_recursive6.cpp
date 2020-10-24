//Program to calculate nth term in Newman-Conway sequence
//1 1 2 2 3 4 4 4 5 6 7 7...

#include <iostream>
using namespace std;

//Function declaration
int seqNC(int n);

//[MAIN]
int main()
{
    int n;
    cout << "Enter the value of n: ";
    cin >> n;
    
    cout << "Number " << n << " in the sequence is " << seqNC(n) << endl;
    
    return 0;
}

int seqNC(int n)
{
    if (n < 3)
        return 1;
    else
        return seqNC(seqNC(n-1)) + seqNC(n-seqNC(n-1));
}
