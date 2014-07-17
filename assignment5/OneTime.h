#ifndef OneTime_H
#define OneTime_H


#include "Appointment.h"

using namespace std;

class OneTime : public Appointment{

public:
	OneTime(string description, int day, int month, int year, int hour, int min) : Appointment(description, day, month, year, hour, min){
		//ctor
	}

	bool occurs_on(int day, int month, int year);
	void print() const;
};

#endif


