/////////////////////////
//Done by:             //
//                     //       
//Rafay Ahmed Khan     //
//Mohammad Moaaz Ahmad //
//26th April, 2014     //
//                     //
/////////////////////////


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <stdlib.h>
#include "header.h"
using namespace std;



int main(int argc, char** argv) 
{ 
	char ch; 
	std::cout << "Which version do you want to play? (O) or (E): "; 
	std::cin >> ch; 

	if (ch == 'O') { 
		Hangman hangman; 
		hangman.run(); //Read in the file, prompt number of guesses, 
		//prompt number of letters, play! 
	} 
	else { 
		EvilHangman hangman; 
		hangman.run(); //Read in the file, prompt number of guesses, 
		//prompt number of letters, 
		//prompt whether to display possible words, play! 
	} 
	return 0; 
}
