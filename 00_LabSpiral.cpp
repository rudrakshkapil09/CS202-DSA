//Program to print spiral order of a matrix
#include <iostream>
#include <iomanip>
using namespace std;

int matrix[10][10];

void setMatrix(int matrix[][10], int n)
{
    int count = 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = count++;
}

void printMatrix(int matrix[][10], int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << matrix[i][j] << setw(3);
        cout << "\n";
    }
    cout << endl;
}

void printSpiral(int matrix[][10], int hs, int vs, int hf, int vf, int dir)
{
    if (hf >= hs || vf >= vs) {
        switch (dir) {
            case 1:
                for (int i = hs; i <= hf; i++)
                    cout << matrix[vs][i] << " ";
                printSpiral(matrix, hs, ++vs, hf, vf, 2);
                break;
            case 2:
                for (int i = vs; i <= vf; i++)
                    cout << matrix[i][hf] << " ";
                printSpiral(matrix, hs, vs, --hf, vf, 3);
                break;
            case 3:
                for (int i = hf; i >= hs; i--)
                    cout << matrix[vf][i] << " ";
                printSpiral(matrix, hs, vs, hf, --vf, 4);
                break;
            case 4:
                for (int i = vf; i >= vs; i--)
                    cout << matrix[i][hs] << " ";
                printSpiral(matrix, ++hs, vs, hf, vf, 1);
                break;
        }
    }
}

//main
int main()
{
    int n;
    cout << "Enter value of n => ";
    cin >> n;
    
    setMatrix(matrix, n);
    printMatrix(matrix, n);
    cout << "Spiral order:\n";
    printSpiral(matrix, 0, 0, n-1, n-1, 1);
    cout << endl;
}
