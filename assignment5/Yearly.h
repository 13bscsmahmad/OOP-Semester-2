#ifndef Yearly_H
#define Yearly_H


#include "Appointment.h"

using namespace std;

class Yearly : public Appointment{

public:
	Yearly(string description, int day, int month, int year, int hour, int min) : Appointment(description, day, month, year, hour, min){
		//ctor
	}

	bool occurs_on(int day, int month, int year);
	void print() const;
};


#endif
