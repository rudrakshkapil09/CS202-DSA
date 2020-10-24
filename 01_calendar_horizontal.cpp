//Calendar for a given year


#include <iostream>
#include <iomanip>
using namespace std;

//function declarations
string showNameOfMonth(int);
int getNumberOfDays(int, int);
int checkLeap(int);
int getStart(int);

int main()
{
	cout << "\n\n[CALENDAR]\n\n";
	
	int days_in_month, start, year, spacing;
	cout << "Enter year: ";
	cin >> year;
	
	start = getStart(year);
	for (int i = 0; i < 12; i++)	//month number
	{
		days_in_month = getNumberOfDays(i, year);
		
		cout << "   ===============" << showNameOfMonth(i) << "===============\n";
		cout << "   SUN   MON   THU   WED   THU   FRI   SAT\n";
		
		int j;
		for (j = 0; j < start; j++)
			cout << "      ";

		for (int k = 1; k <= days_in_month; k++) {
			cout << setw(6) << k;
		
			if (++j > 6) { 
				cout << "\n";
				j = 0;
			}
		}

		cout << "\n\n";
		start = j;
	}
	
	return 0;
}

int getStart(int year)
{
    year -= 1;
    return ( year + year/4 - year/100 +
             year/400 + 1) % 7;
}


string showNameOfMonth(int monthNumber)
{
	string names[12] = {"=January=", "February=", "==March==", "==April==", "===May===", "==June===", "==July===", "=August==", "September", "=October=", "November=", "December="};
	return names[monthNumber];
}

int getNumberOfDays(int monthNumber, int year) 
{
	int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (checkLeap(year))
		days[1] = 29;
	return days[monthNumber];
}

int checkLeap(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		return 1;
	else return 0;
}
