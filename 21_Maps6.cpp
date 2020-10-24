/*Maps*/
//Max amount of chocolates from 4 consecutive boxes
#include <iostream>
#include <map>
#include <vector>
using namespace std;

//special functions
int sumFour(vector<int> input, int start)
{
    int count = 0, sum = 0;
    for (int i = start; count < 4; i = (i+1) % input.size()) {
        sum += input[i];
        count++;
    }
    return sum;
}

void printOutput(vector<int> input)
{
    map<int, int> m;
    pair<int, int> x;
    for (int i = 0; i < input.size(); i++) {
        x.first = sumFour(input, i);
        x.second = i;
        m.insert(x);
    }
    
    cout << "The 4 consecutive boxes which give most chocolates are:\n{";
    int count = 0;
    for (int i = m.rbegin()->second; count < 4; i = (i+1) % input.size()) {
        cout << input[i];
        (count++ == 3) ? cout << "}\n" : cout << ", ";
    }
}

//MAIN
int main()
{
    vector<int> input = {2,7,6,1,4,5};
    printOutput(input);
    return 0;
}
