//sort a given list, eg 2, 5, 6, 7 .. up to 8 numbers with even on left and odd on right

#include <iostream>
using namespace std;

//function declarations
int list[50];
void swap_01(int &, int &);
void swap_02(int *, int *);
void swap_03(int *, int *);
void swap_04(int &, int &);
void swap_05(int  , int  );
void swap_06(int  , int  );
void swap_07(int *, int *);
void swap_08(int &, int &);
void swap_09(int  , int  );

//[MAIN]
int main() {
    
    int list[8] = {2, 5, 4, 8, 9, 3, 7, 6};
    int left, right;
    
    //getting input and storing in list
    /*cout << "Enter elements (terminate with -1):\n";
     for (int i = 0; ; i++) {
     cin >> list[i];
     if (list[i] < 0)
     break;
     n++;
     }
     */
    
    //if left is even, move l forward; if right is odd, move r back
    left = 0; right = 7;
    while (left < right) {
        if (list[left] % 2 == 0)
            left++;
        else if (list[right] % 2 == 1)
            right--;
        else
            swap_08(list[left], list[right]);
    }
    
    //ouputting list (without the -1)
    for (int i = 0; i < 8; i++)
        cout << list[i] << "  ";
    cout << endl;
    return 0;
}


//function definitions:
//1. call by reference (l, r). box = dash; dash = dash; dash = box;
void swap_01(int &x, int &y)
{
    int t;
    t = x;
    x = y;
    y = t;
}

//2. call by pointer (&l, &r). box = cont; cont = cont; cont = box
void swap_02(int *x, int *y)
{
    int t;
    t = *x;
    *x = *y;    //x = y would not swap becuase then x points to y
    *y = t;
}

//3. call by pointer (&l, &r). arrow = arrow (x3) (not swapping correctly)
void swap_03(int *x, int *y)
{
    int *t;
    t = x;
    *x = *y;
    y = t;
}

//4. call by reference (l, r). box = cont; arrow = arrow; cont = box; (not swapping correctly)
void swap_04(int &x, int &y)
{
    int *t;
    t = &x;
    x = y;
    y = *t;
}

//5. call by value (l, r). arrow = dash; box = box; box = cont (not swapping)
void swap_05(int x, int y)
{
    int *t;
    t = &x;
    x = y;
    y = *t;
}

//6. call by value (l, r). box = box (x3) (not swapping)
void swap_06(int x, int y)
{
    int t;
    t = x;
    x = y;
    y = t;
}

//7. call by pointer (&l, &r). arrow = arrow (x3) (not swapping)
void swap_07(int *x, int *y)
{
    int *t;
    t = x;
    x = y;
    y = t;
}

//8. different algo - call by ref - (swapping)
void swap_08(int &x, int &y)
{
    x = x + y;
    y = x - y;
    x = x - y;
}

//9. different algo - call by value - (not swapping)
void swap_09(int  x, int y)
{
    x = x + y;
    y = x - y;
    x = x - y;
}


