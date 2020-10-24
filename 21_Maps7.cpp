//Checking if a row of a matrix is a permutation of another
#include <iostream>
#include <map>
#include <vector>
using namespace std;

//special functions
int setMap(int matrix[][5], int row, int col, map<int, vector<int>> m)
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            m[i].push_back(matrix[i][j]);
        sort(m[i].begin(), m[i].end());
    }
    
    map<int, vector<int>> :: iterator itr, itr2;
    for (itr = m.begin(); itr != m.end(); itr++)
        for (itr2 = itr; itr2 != m.end(); itr2++)
            if (itr != itr2 && itr2->second == itr->second) {
                cout << "Rows " << itr->first+1 << " and " << itr2->first+1 << " are permutations of one another.\n";
                return 1;
            }
    cout << "There are no rows which are permutations of one another.\n";
    return 0;
}

//MAIN
int main()
{
    map<int, vector<int>> m;
    int matrix1[5][5] = {
        1, 1, 3, 2, 5,
        3, 2, 4, 5, 1,      //this row
        3, 2, 1, 5, 6,
        1, 4, 2, 5, 3,      //permutation of this row
        1, 7, 4, 3, 2
    };
    
    return setMap(matrix1, 5, 5, m);
}
