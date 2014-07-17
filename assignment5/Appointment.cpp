#include<iostream>
#include<string>
#include "Appointment.h"

using namespace std;


Appointment::Appointment(string description, int day, int month, int yr, int hr, int min) : description(description), date(day, month, yr), hour(hr), minute(min){
	//initialized all members using initializing list...
}

Date Appointment::getDate(){
	return date;
}

void Appointment::print() const{

	cout << hour << ":" << minute << " -> " << description << endl;
}
