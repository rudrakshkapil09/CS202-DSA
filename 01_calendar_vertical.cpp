//Calendar for a given year


#include <iostream>
#include <iomanip>
using namespace std;

//functions & array declarations
string showNameOfMonth(int);
string showNameOfDay(int);
int getNumberOfDays(int, int);
int checkLeap(int);
int getSpace(int, int);
int getStart(int, int);
int grid[7][7];

 
int main()
{
    cout << "\n\n[CALENDAR]\n\n";
    
    int days_in_month, start, year, date, start_of_last_month, next_start;

    cout << "Enter year: ";
    cin >> year;
    
    for (int i = 0; i < 12; i++)    //monthNumber
    {
        days_in_month = getNumberOfDays(i, year);
        if (i == 0) {
            start = getSpace(i, year);
            start_of_last_month = start;
        }
        else
            start = (start_of_last_month + getNumberOfDays(i-1, year) + 1) % 7;

        date = 1;
        
        //setting up grid
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 7; k++) {
                if (j == 0 && k < start)
                    grid[j][k] = 0;
                else {
                    grid[j][k] = date;
                    date++;
                    //date2 = date;
                }
                
                //if (date > days_in_month) {
                //    date = 1;
                //    break;
                //}
            }
            
            //if (date2 > days_in_month) {
            //   date = 1;
            //    break;
            //}
        }
        
        //printing - output
        cout << "   ===============" << showNameOfMonth(i) << "===============\n";
        for (int j = 0; j < 7; j++) {
            cout << "   " << showNameOfDay(j);
            
            for (int k = 0; k < 6; k++) {
                if (grid[k][j] == 0 || grid[k][j] > days_in_month)
                    cout << "      ";
                else
                    cout << setw(6) << grid[k][j];
            }
            cout << "\n";
        }
        cout << "\n";
        
        //start needs to change - done
        // 3, 11, 19 ... not appearing - done
        //31 needs to appear in 7th coloumn - done
        //count needs to reset after crossing number of days - done
        // JAN -> APRIL not showing anything - done
        
    }
    
    return 0;
}



//function definitons
//1.
string showNameOfMonth(int monthNumber)
{
    string names_months[12] = {"=January=", "February=", "==March==", "==April==", "===May===", "==June===", "==July===", "=August==", "September", "=October=", "November=", "December="};
    return names_months[monthNumber];
}

//2.
string showNameOfDay(int monthNumber)
{
    string names_days[7] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};
    return names_days[monthNumber];
}

//3.
int getNumberOfDays(int monthNumber, int year)
{
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (checkLeap(year))
        days[1] = 29;
    return days[monthNumber];
}

//4.
int checkLeap(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        return 1;
    else return 0;
}

//5. returns how many initial days to skip each month, for a given year
int getSpace(int monthNumber, int year)
{
    if (monthNumber == 0) {
        if (checkLeap(year)) {
            int a = (6+year+(year/4)-(year/100)+(year/400));
            return a % 7 - 1;
        }
        else {
            int b = (6+year+(year/4)-(year/100)+(year/400));
            return b % 7;
        }
    }
    else {
        return (getSpace(monthNumber-1, year) + getNumberOfDays(monthNumber-1, year)) % 7;
    }
}
