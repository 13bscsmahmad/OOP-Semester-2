//Object-Oriented Programming Assignment 2 by Shah Nawaz Khan. Reg # 05382. Class = BSCS-3A.
//Credits: I wrote the code myself but I had a little help with understanding the logic behind recursive backtracking 
//from M. Hassan uz Zaman. Reg # 07038. And I checked the syntax for my code from cplusplus.com

#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>
#include "Robot.h"

using namespace std; 


int main(int argc, char** argv)
{
	Robot robot(argv[1]); //Read in the input map file
	robot.findFridge();   //Find path to the fridge
	robot.displayMap();  //Display the path with the map that was found

	return 0;
}
