#include<iostream>
#include<string>
#include <iomanip>
#include "Daily.h"

using namespace std;


bool Daily::occurs_on(int day, int month, int year){

	bool occurs = false;

	if (year == date.getYear()){
		if (month == date.getMonth()){
			if (day >= date.getDay()){
				occurs = true;
				return occurs;
			}			
		}

		if (month > date.getMonth()){
			occurs = true;
			return occurs;
		}

	}

	else
		if (year > date.getYear()){
			occurs = true;
			return occurs;
		}

		return occurs;

}

void Daily::print() const{ // Function displays appointment EXACTLY as in the sample interaction. Using <iomanip> to set hours and minutes to 2 digits
	
	cout << setw(2) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " -> " << description << " (Daily)" << endl;
}
