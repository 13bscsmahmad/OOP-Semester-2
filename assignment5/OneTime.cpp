#include<iostream>
#include<string>
#include "OneTime.h"
#include <iomanip>

using namespace std;

bool OneTime::occurs_on(int day, int month, int year){
	bool occurs = false;

// Day, month, and year all must match
	if (day == date.getDay() && month == date.getMonth() && year == date.getYear())
		occurs = true;

	return occurs;
}

void OneTime::print() const{ // Function displays appointment EXACTLY as in the sample interaction. Using <iomanip> to set hours and minutes to 2 digits

	cout << setw(2) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " -> " << description << " (One time)" << endl;
}
