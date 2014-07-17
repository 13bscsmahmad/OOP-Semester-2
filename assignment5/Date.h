#ifndef Date_H
#define Date_H


class Date{

private:
	int month;
	int day;
	int year;

public:

	Date(int day, int month, int year);

	int getMonth() const;
	int getDay() const; 
	int getYear() const;


};

#endif
