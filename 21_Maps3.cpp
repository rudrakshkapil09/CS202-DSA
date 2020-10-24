/*Maps*/
//Postion in sorted array
#include <iostream>
#include <map>
#include <vector>
using namespace std;

//special functions
map<int,int> setMaps(vector<int> input)
{
    map<int, int> m;
    map<int ,int> :: iterator it;
    for (int i = 0; i < input.size(); i++)
        m[input[i]];
    
    int pos = 0;
    for (it = m.begin(); it != m.end(); it++, pos++)
        it->second = pos;
    return m;
}

void printOutput(vector<int> input, map<int, int> m)
{
    cout << "Positions in sorted array:\n{";
    for (int i = 0; i < input.size(); i++) {
        cout << m[input[i]];
        (i == input.size()-1) ? cout << "}\n" : cout << ", ";
    }
}

//MAIN
int main()
{
    vector<int> input = {10, 5, 40, 35, 20, 80, 12};
    map<int, int> m = setMaps(input);
    printOutput(input, m);
    return 0;
}
