#include<iostream>
#include<string>
#include "Yearly.h"
#include <iomanip>

using namespace std;


bool Yearly::occurs_on(int day, int month, int year){
	bool occurs = false;
// Day and month may match, but the year has to be >=.
	if (day == getDate().getDay() && month == getDate().getMonth() && year >= getDate().getYear()) {
		occurs = true;
	}

	return occurs;

}

void Yearly::print() const{ // Function displays appointment EXACTLY as in the sample interaction. Using <iomanip> to set hours and minutes to 2 digits

	cout << setw(2) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " -> " << description << " (Yearly)" << endl;
}
