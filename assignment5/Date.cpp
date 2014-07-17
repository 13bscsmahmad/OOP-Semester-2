#include<iostream>
#include<string>
#include "Date.h"


using namespace std;

Date::Date(int day, int month, int year) {
	this->month = month; 
	this->day = day;
	this->year = year;
}

int Date::getMonth() const{
	return month;
}

int Date::getDay() const{
	return day;
}

int Date::getYear() const{
	return year;
}
