/*Maps*/
//4 numbers in 4 different sorted arrays that add up to eq;
#include <iostream>
#include <map>
#include <queue>
using namespace std;
const int eq = 20;

map<int, vector<int>> insertMaps(int first[], int second[], int n1, int n2)
{
    map <int, vector<int>> m;
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            m[first[i]+second[j]].push_back(first[i]);
            m[first[i]+second[j]].push_back(second[j]);
        }
    }
    return m;
}

void printOutput(map<int, vector<int>> m1, map<int, vector<int>> m2)
{
    map<int, vector<int>> :: iterator it;
    for (it = m1.begin(); it != m1.end(); it++) {
        int to_find = eq - it->first;
        if (m2[to_find].size()) {
            for (int i = 0; i < it->second.size(); i+=2) {
                for (int j = 0; j < m2[to_find].size(); j+=2) {
                    cout << it->second[i] << " " << it->second[i+1] << " ";
                    cout << m2[to_find][j] << " " << m2[to_find][j+1] << " ";
                    cout << endl;
                }
            }
        }
    }
}

//MAIN
int main()
{
    int list1[] = {2, 4, 6, 8};
    int list2[] = {1, 3, 5, 7};
    int list3[] = {2, 4};
    int list4[] = {1, 3};
    
    map<int, vector<int>> first = insertMaps(list1, list2, 4, 4);
    map<int, vector<int>> second = insertMaps(list3, list4, 2, 2);
    
    cout << "The numbers that add up to " << eq << " are:\n";
    printOutput(first, second);
}
