//All possible permutations of a string - using STL
#include <iostream>
#include <cstring>
using namespace std;

//special functions
void permute(string s)
{
    sort(s.begin(), s.end());
    do {
        cout << s << "\n";
    } while (next_permutation(s.begin(), s.end()));
}

int main()
{
    string input;
    cout << "Enter a string: ";
    cin >> input;
    permute(input);
}
