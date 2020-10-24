/*Maps*/
//3 highest frequencies
#include <iostream>
#include <map>
#include <vector>
using namespace std;

//special functions
void printOutput(vector<int> input)
{
    map <int, int> m1;                  //storing values in first map
    map <int, int> :: iterator it1;
    for (int i = 0; i < input.size(); i++)         //first -> value
        m1[input[i]]++;                 //second -> count
    
    map <int, vector<int>> m2;
    map <int, vector<int>> :: reverse_iterator it2;
    for (it1 = m1.begin(); it1 != m1.end(); it1++)
        m2[it1->second].push_back(it1->first);
    
    int count = 0;
    for (it2 = m2.rbegin(); count < 3; it2++) {
        cout << "Frequency " << it2->first << " => ";
        for (int i = 0; i < it2->second.size(); i++) {
            cout << it2->second[i];
            (i == it2->second.size()-1) ? cout << "\n" : cout << ", ";
            count++;
        }
    }
    
}

//MAIN
int main()
{
    vector<int> input = {2,3,8,4,5,8,2,5,6,5,2};
    printOutput(input);
    return 0;
}
