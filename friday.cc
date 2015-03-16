/*
ID: sunapi31
PROG: friday 
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ifstream fin ("friday.in");
    ofstream fout ("friday.out");
    int n, year=1900;
    int week[7] = {0, 0, 0, 0, 0, 0, 0};
    string daynames[7] = {"mon", "tues", "wed", "thurs", "fri", "sat", "sun"};
    string monthnames[12] = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sept", "oct", "nov", "dec"};
    int daysin[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int weekday = 0;
    fin >> n;
    for(int i=0; i<n; i++) {
        bool leapYear = (year % 4) == 0;
        bool centuryYear = (year%100==0) && !(year%400==0);
        for (int month = 0; month < 12; month++) {
            int daysinmonth = daysin[month];
            // does feb has an extra weekday?
            if(!centuryYear && leapYear && month == 1) {
                daysinmonth += 1;
            }

            for(int day = 0; day < daysinmonth; day++) {
                // cerr << year << " " << monthnames[month] << " " << day + 1 << "\t" << daynames[weekday] << endl;
                if(day == 12) { // is thirteenth of the month?
                    week[weekday]++;
                    // cerr << "13th of " << monthnames[month] << " is " << daynames[weekday] << endl;
                }
                weekday = (weekday + 1) % 7;
            }
            
        }
        year++;
    }

    // output
    fout <<
    week[5] << " " << week[6] << " " <<
    week[0] << " " << week[1] << " " <<
    week[2] << " " << week[3] << " " <<
    week[4] << endl;
    return 0;
}

