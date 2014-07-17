#ifndef Appointment_H
#define Appointment_H

#include "Date.h"

using namespace std;

class Appointment{
protected:
	Date date;
	string description;
	Date getDate();

public:


	int hour;
	int minute;

	Appointment(string description, int day, int month, int yr, int hr, int min);
	virtual bool occurs_on(int day, int month, int year) = 0; // Pure virtual function
	virtual void print() const; // constant function

};

#endif
