//////////////////////////
// Mohammad Moaaz Ahmad //
// Registration # 6714  //
// BS(CS) - 3A          //
// 5th May, 2014        //
//////////////////////////

#include<iostream>
#include<string>
#include<vector>
#include "Appointment.h"
#include "OneTime.h"
#include "Daily.h"
#include "Monthly.h"
#include "Yearly.h"
#include "Date.h"


using namespace std;

void checkAppointments(vector<Appointment*>& apptbook){ //Loop through the apptbook to check what appt. is on the specified day

	int day;
	int month;
	int year;

	cout << "Enter date (dd mm yyyy): ";
	cin >> day >> month >> year;

	for (int i = 0; i < apptbook.size(); i++){
		if (apptbook[i]->occurs_on(day, month, year))
			apptbook[i]->print();
	}

}



void addAppointment(vector<Appointment*>& apptbook){ //add an appt. based on user's input

	int day;
	int month;
	int year;
	int hour;
	int min;
	string description;

	int type;

	cout << "Enter date and time (dd mm yyyy hr min): ";
	cin >> day >> month >> year >> hour >> min;

	cin.ignore();

	cout << "Enter description: " << endl;
	getline(cin, description);


	cout << "Enter appointment type: (1) for one-time, (2) for daily, (3) for monthly, (4) for yearly: ";
	cin >> type;

	Appointment* appointment;

	switch (type) //for creating subclass on the heap
	{

	case 1:
		appointment = new OneTime(description, day, month, year, hour, min); //One time reminder
		break;

	case 2:
		appointment = new Daily(description, day, month, year, hour, min); //Daily reminder
		break;

	case 3:
		appointment = new Monthly(description, day, month, year, hour, min); //Monthly reminder
		break;

	case 4:
		appointment = new Yearly(description, day, month, year, hour, min); //Yearly reminder
		break;

	default:

		cout << "Invalid Input. " << endl;
		break;
	}

	apptbook.push_back(appointment);
}




int main(){

	vector<Appointment*> apptbook;

	char option;

	do {
		cout << "********** Appointment Book Application ************" << endl<< endl;
		cout << "(a) See all appointments on a given day." << endl;
		cout << "(b) Add an appointment." << endl << endl;
		cout << "Enter an option or 'q' to quit: ";

		cin >> option;
		switch(option){
		case 'a': 
			checkAppointments(apptbook);
			break;
		case 'b':
			addAppointment(apptbook);
			break;
		case 'q':
			break;
		default:
			cout << "You entered an invalid option.  Try again!";    
		}
		cout << endl;
	}
	while(option != 'q');

	// Cleaning up 

	for(int i = 0; i < apptbook.size(); i++){
		delete apptbook[i];
	}
	apptbook.clear();


	return 0;
}
