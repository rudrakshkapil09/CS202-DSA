//All possible permutations of a string - duplicates not allowed
#include <iostream>
using namespace std;

//special functions
void swap(char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void permute(char *ch, int l, int r)
{
    if (l == r)
        cout << ch << "\n";
    else {
        for (int i = l; i <= r; i++) {
            swap((ch+l), (ch+i));
            permute(ch, l+1, r);
            swap((ch+l), (ch+i));
        }
    }
}

//MAIN
int main()
{
    char input[] = "ABC";
    permute(input, 0, strlen(input)-1);
}
