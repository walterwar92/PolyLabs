#include <iostream>
#include <limits>
 
using namespace std;
 
bool isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}
 
bool isValidDate(int day, int month, int year) {
    if (month < 1 || month > 12)
        return false;
    if (day < 1)
        return false;
    if (month == 2) {
        if (isLeapYear(year)) {
            return day <= 29;
        } else {
            return day <= 28;
        }
    }
    const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return day <= daysInMonth[month];
}
 
int main() {
    int birthdays[5][3];
    int daysAlive[5];
    const int todayDay = 7;
    const int todayMonth = 11;
    const int todayYear = 2023;
    for (int i = 0; i < 5; i++) {
        int day, month, year;
        bool validInput = false;
        do {
            cout << i + 1 << ":";
            cin >> day >> month >> year;
            if (cin.fail() || !isValidDate(day, month, year) || year == 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid date. Please try again." << endl;
            } else {
                validInput = true;
            }
        } while (!validInput);
 
        birthdays[i][0] = day;
        birthdays[i][1] = month;
        birthdays[i][2] = year;
 
        int daysInYear = 365;
        if (isLeapYear(year)) {
            daysInYear = 366;
        }
        int daysAliveSinceBirth = (todayYear - year) * daysInYear;
 
        for (int m = month; m <= 12; m++) {
            int daysInMonth = 31;
            if (m == 2) {
                daysInMonth = isLeapYear(year) ? 29 : 28;
            } else if (m == 4 || m == 6 || m == 9 || m == 11) {
                daysInMonth = 30;
            }
            daysAliveSinceBirth += daysInMonth - day + 1;
            day = 1;
        }
 
        daysAliveSinceBirth += todayDay;
 
        daysAlive[i] = daysAliveSinceBirth;
    }
 
    int totalDaysAlive = 0;
    for (int i : daysAlive) {
        totalDaysAlive += i;
    }
    int averageDaysAlive = totalDaysAlive / 5;
    int years = averageDaysAlive / 365;
    int remainingDays = averageDaysAlive % 365;
    int months = remainingDays / 30;
    int days = remainingDays % 30;
    cout << "Average alive: " << years << " Years, " << months << " Months, " << days << " Days" << endl;
 
    int youngestAge = INT_MAX;
    int oldestAge = 0;
    for (int i = 0; i < 5; i++) {
        int currentAge = todayYear - birthdays[i][2];
        if (currentAge < youngestAge) {
            youngestAge = currentAge;
        }
        if (currentAge > oldestAge) {
            oldestAge = currentAge;
        }
    }
 
    cout << "Youngest person's age: " << youngestAge << " Years" << endl;
    cout << "Oldest person's age: " << oldestAge << " Years" << endl;
}