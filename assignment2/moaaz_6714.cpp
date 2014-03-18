//Mohammad Moaaz Ahmad//
//Reg.# 6714          //
//BS(CS)-3A           //  
////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <cstring>

bool reached = false;

class Robot{

private:

	int row;
	int col;
	char** map;
	int x;
	int y;


public:

	Robot(char* fileName);
	void findFridge();
	void rec(int x, int y);
	void displayMap();
	

};


Robot::Robot(char* fileName){

		//Constructor

		row = 0;
		col = 0;


		std::string line; 

		std::ifstream myfile (fileName);

		if (myfile.is_open())
		{
			std::getline(myfile,line); //Store 1st line of file
			col = line.length(); 


			myfile.seekg(0); //return to the beginning

			while (getline(myfile,line))
				row++; //Get number of rows by storing each row one by one in a string

			// Allocate memory for 2D array

			map = new char*[row];
			for (int i = 0; i < row; i++)
			{
				map[i] = new char[col];
			}

			myfile.close(); // Hack, since file pointer is not returning to the beginning with the seekg() function

			std::ifstream myfile (fileName);

			/*myfile.seekg(0);*/  //not working, therefore dirty workaround used above

			for (int i = 0; i < row; i++){

				getline(myfile, line);
				strcpy(map[i], line.c_str());

			}

			myfile.close();
		} else {

			std::cout << "Error opening filestream." << std::endl;
			exit(1);
		}

		//Get original position of robot in the original map

		for (int i = 0; i < row; i++){
			for (int j = 0; j < col; j++){
				if (map[i][j] == 'R'){
					x = i;
					y = j;
				}
			}
		}

		//Display original map + statement for the final map


		displayMap();
		std::cout << "Path To Fridge:" << std::endl << std::endl;
	}

void Robot::findFridge(){
	rec(x,y);
}

void Robot::rec(int x, int y){

	// Base case

	if (map[x][y+1] == 'F' || map[x][y-1] == 'F' || map[x+1][y] == 'F' || map[x-1][y] == 'F'){

		for (int i = 0; i < row; i++){
			for (int j = 0; j < col; j++){
				if (map[i][j] == 'B') 
					map[i][j] = ' ';
			}
		}

		reached = true;
		return;
	}

	//Conditions

	if (map[x][y+1] == ' '){ //Right
		map[x][y+1] = 'R';
		rec(x, y+1);
	} else 
		if (map[x][y-1] == ' '){ //Left
			map[x][y-1] = 'R';
			rec(x, y-1);
		} else 
			if (map[x+1][y] == ' '){ //Down
				map[x+1][y] = 'R';
				rec(x+1, y);
			} else 
				if (map[x-1][y] == ' '){ //Up
					map[x-1][y] = 'R';
					rec(x-1, y);

		
			
		
	}

	if (reached == false){

		if (map[x][y+1] == ' '){
			map[x][y+1] = 'R';
			displayMap();
			rec(x, y+1);

		} else
			if (map[x][y-1] == ' '){
				map[x][y-1] = 'R';
				rec(x, y-1);
			} else 
				if (map[x+1][y] == ' '){
					map[x+1][y] = 'R';
					rec(x+1, y);
				} else
					if (map[x-1][y] == ' '){
						map[x-1][y] = 'R';
						rec(x-1, y);

					
				
			
		}

		if (reached == false)
			map[x][y] = 'B'; // 'B' for backtrack! Leaves a 'B' where it backtracks from
	}
}

void Robot::displayMap(){

	for (int i = 0; i < row; i++){
		if (i > 0)
			std::cout << std::endl;

		for (int j = 0; j < col; j++){
			std::cout << map[i][j];
		}
	}

	std::cout << std::endl << std::endl;
}


int main(int argc, char** argv){

  Robot robot(argv[1]); //read in the input map file.
  robot.findFridge(); //find the path to the fridge
  robot.displayMap(); //display the map with the path that was found

	return 0;
}
