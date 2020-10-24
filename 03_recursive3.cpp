//recursive function to display change in denominations

#include <iostream>
using namespace std;

//function declaration
void displayChange(int, int [], int);
int denominations[] = {200, 100, 50, 20, 10, 5, 2, 1};

//[MAIN]
int main()
{
    int amount;
    cout << "Enter amount: ";
    cin >> amount;
    
    cout << "Breakdown:\n";
    displayChange(amount, denominations, 0);
    
    return 0;
}

void displayChange(int amt, int d[], int pos)
{
    if (pos < 8) {
        if (amt/d[pos] > 0) {
            cout << d[pos] << "\t\bx\t\b\b\b" << amt/d[pos] << "\n";
            displayChange(amt%d[pos], d, pos);
        }
        else {
            displayChange(amt, d, pos+1);
        }
    }
    else
        cout << "\n";
    
}


//1 is not showing up properly - done
//no repeats showing - still -
