//recursive function to solve towers of hanoi problem.

#include <iostream>
using namespace std;

//Function declaration
void hanoiTower(int, int, int, int);

//[MAIN]
int main()
{
    int n, src = 65, dest = 67, temp = 66;      //A,C and B
    cout << "Enter number of discs: ";
    cin >> n;
 ]
    cout << "The solution for " << n << " discs and 3 poles is as follows:\n";
    hanoiTower(n, src, dest, temp);
    
    return 0;
}

//Function definitions
void hanoiTower(int n, int src, int dest, int temp)
{
    if (n > 1)
    {
        hanoiTower(n-1, src, temp, dest);
        cout << (char)src << " to " << (char)dest << endl;
        hanoiTower(n-1, temp, dest, src);
    }

    else
        cout << (char)src << " to " << char(dest) << endl;
    
    return;
}

