#include<iostream>
#include<string>
#include "Monthly.h"
#include <iomanip>

using namespace std;


bool Monthly::occurs_on(int day, int month, int year){

	bool occurs = false;

//if year and day are the same, but month is not

	if (year == date.getYear()){
		if (month >= date.getMonth())
			if (day == date.getDay()){
				occurs = true;
				return occurs;
			}
	}

//if day is the same but year is not

	if (year > date.getYear()){
		if (day == date.getDay()){
			occurs = true;
			return occurs;
		}
	}

	return occurs;

}

void Monthly::print() const{ // Function displays appointment EXACTLY as in the sample interaction. Using <iomanip> to set hours and minutes to 2 digits

	cout << setw(2) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " -> " << description << " (Monthly)" << endl;

}
