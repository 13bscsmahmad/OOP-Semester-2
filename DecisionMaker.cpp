#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <stdio.h> //required for fflush()

int main (void){

	int count = 0;
	int random;
	std::string yesno = "y";
	char prog = 'n';

	std::string welcome_message = "Welcome to the Decision Maker created by MMA!";
	std::cout << welcome_message << std::endl;
	std::cout << "*********************************************" << std::endl;
	std::cout << std::endl;

	do{
		if (prog == 'y')
			std::cout << std::endl << std::endl;

		std::cout << "Enter the number of options you can decide from ( must be >= 0): ";
		std::cin >> count;
		std::cout << std::endl << std::endl;
		//fflush(stdin);

		if (count >= 0){
		std::string* options = new std::string[count];

		for (int i = 0; i < count; i++){

			if (count <= 1)
				break;

			std::cout << "Enter option " << i+1 <<": ";
			std::getline(std::cin, options[i]); 
			fflush(stdin); // is required as cin takes the number but does not take \n therefore this is left in the stream and taken by the getline(). This causes error, hence this fflush.
		}


		do{

			if (count == 1){
				std::cout << "The decision has already been made by you!" << std::endl << std::endl;
				break;
			}

			if (count == 0){
				std::cout << "Glad you didn't ask me to choose from anything!" << std::endl << std::endl;
				break;
			}

			srand(time(NULL));
			random = rand() % count;



			std::cout << std::endl << std::endl << "Decision made!" << std::endl;
			std::cout << options[random] << std::endl << std::endl;
			std::cout << "Perhaps the same decision once more? ('y' = yes, anything else = move on.): ";
			std::cin >> yesno;
		} while (yesno == "y");

		}
		else
			std::cout << "Negative numbers not allowed!" << std::endl << std::endl;
		std::cout << std::endl << std::endl << "Would you like to make another decision? ('y' for yes): ";
		std::cin >> prog;
	} while (prog == 'y');

	std::cout << std::endl;

	if (prog == 'y')
		std::cout << "***** Thank you for using this program! Hope the decisions I made *****\n***** will help you along your journey. *****\n\n";

	return 0;

}
