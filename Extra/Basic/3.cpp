//Tug of War
#include <iostream>
#include <vector>
using namespace std;

//struct defintion
struct solution {
    int diff = 999;
    int lsum = 0, rsum = 0;
    vector<int> left;
    vector<int> right;
};

//special functions
int getSum(vector<int> arr)
{
    int i = 0, sum = 0;
    while (i < arr.size()) {
        sum += arr[i++];
    }
    return sum;
}

void printSubset(vector<int> arr)
{
    cout << "{";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i];
        (i == arr.size() - 1) ? cout << "}\n" : cout << ", ";
    }
}

void fillVectors(vector<int> arr, vector<int> &left, vector<int> &right)
{
    int i = 0;
    for (;i < arr.size()/2; i++)
        left.push_back(arr[i]);
    for (;i < arr.size(); i++)
        right.push_back(arr[i]);
}

struct solution best;
int checkSums(vector<int> left, vector<int> right)
{
    int left_sum = getSum(left);
    int right_sum = getSum(right);
    if (abs(left_sum - right_sum) < best.diff) {
        best.diff = abs(left_sum - right_sum);
        best.lsum = left_sum;
        best.rsum = right_sum;
        best.left = left;
        best.right = right;
        return 1;
    }
    return 0;
}

void tugOfWar(vector<int> left, vector<int> right)
{
    int flag = 1;
    while (flag) {
        flag = 0;
        for (int i = 0; i < left.size(); i++) {
            for (int j = 0; j < right.size(); j++) {
                swap(left[i], right[j]);
                int changed = checkSums(left, right);
                flag = (flag) ? flag : changed;
                swap(left[i], right[j]);
            }
        }
        left = best.left;
        right = best.right;
    }
}

//MAIN
int main()
{
    vector<int> left, right;
    //vector<int> arr = {23, 45, -34, 12, 0, 98, -99, 4, 189, -1, 4};  //works
    vector<int> arr = {3, 4, 5, -3, 100, 1, 89, 54, 23, 20};
    
    
    fillVectors(arr, left, right);
    tugOfWar(left, right);
    cout << "Minimum difference => " << best.diff << "\n";
    cout << "First Subset => ";
    printSubset(best.left);
    cout << "Second Subset => ";
    printSubset(best.right);
    cout << "Sums => " << best.lsum << ", " << best.rsum << "\n";
    return 0;
}

