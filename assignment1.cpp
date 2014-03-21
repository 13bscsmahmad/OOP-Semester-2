#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <string.h>
#include <cstring>
#include <fstream>
#include <iostream>

void printGrid(int row, int column, char **grid);
void cornerCheck(int row, int column, char **grid, char **gridCopy);
void edgeCheck(int row, int column, char **grid, char **gridCopy);
void centerCheck(int row, int column, char **grid, char ** gridCopy);
void nextGrid(int row, int column, char** grid, char **gridCopy);
void freeMem(int column, char **grid, char **gridCopy, int rows);



int main (void){

	
	char name[20];

	printf("Welcome to a simulation of the lifecycle of a bacteria colony.\nCells (X) live and die by the following rules:\n- A cell with 1 or fewer neighbors dies.\n- Locations with 2 neighbors remain stable.\n- Locations with 3 neighbors will create life.\n- A cell with 4 or more neighbors dies.\n");
	printf("Grid input file name? ");
	
	std::cin >> name;	
	
	fflush(stdin);
	
	FILE *ptr = fopen(name, "r");

	if (ptr == NULL){

		printf("Error opening file.\n");
		return 1;
	}

	

	int row, column;

	fscanf(ptr, "%d", &row);
	fscanf(ptr, "%d", &column);


	
	char** grid = (char**)malloc(sizeof(char*) * row); //1st grid 
	for (int i = 0; i < row; i++)
	{
		grid[i] = (char*)malloc(sizeof(char) * column);
	}

	char** gridCopy = (char**)malloc(sizeof(char*) * row); // 2nd Grid for comparison
	for (int i = 0; i < row; i++)
	{
		gridCopy[i] = (char*)malloc(sizeof(char) * column);
	}


	fflush(stdin);
	char extra = 0;
	fscanf(ptr, "%c", &extra);
	//printf("\n\n");
	//2D array created. Going on to fscanf characters from file.

	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < column+1; j++)
		{

			fflush(stdin);
			fscanf(ptr, "%c", &grid[i][j]);

		}


	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			gridCopy[i][j] = grid[i][j]; //copying all elements of grid to gridCopy. 
		}
	}


	printGrid(row, column, grid);

	while(1) {

		char option;

		printf("t)ick, q)uit? ");
		fflush(stdin);
		std :: cin >> option;
		//std::cout << std::endl;

		if (option == 't' || option == 'T'){
			cornerCheck(row, column, grid, gridCopy);
			edgeCheck(row, column, grid, gridCopy);
			centerCheck(row, column, grid, gridCopy);
			printGrid(row, column, grid);
			nextGrid(row, column, grid, gridCopy);

		}

		if (option == 'q' || option == 'Q'){
			fclose(ptr);
			break;
		}

	}

	freeMem(column, grid, gridCopy, row);

	


	return 0;

}

void cornerCheck(int row, int column, char **grid, char **gridCopy){

	//////////////////////   TL      ////////////////////////////////////////////

	int x = 0;

	if (gridCopy[0][1] == 'X'){
		x++;
	}

	if (gridCopy[1][1] == 'X'){
		x++;
	}

	if (gridCopy[1][0] == 'X'){
		x++;
	}

	if (x == 1 || x == 0)
		grid[0][0] = '-';

	if (x == 3){
		grid[0][0] = 'X';
	}


	/////////////////////// TR        ///////////////////////////////////////////////
	int y = 0;

	if (gridCopy[0][column-2] == 'X')
		y++;

	if (gridCopy[1][column - 2] == 'X')
		y++;

	if (gridCopy[1][column - 1] == 'X')
		y++;

	if (y == 1 || y == 0)
		grid[0][column - 1] = '-';

	if (y == 3)
		grid[0][column - 1] = 'X';

	///////////////////////     BL     ///////////////////////////////////////////////

	int z = 0;

	if (gridCopy[row - 1][1] == 'X'){
		z++;
	}

	if (gridCopy[row - 2][1] == 'X'){
		z++;
	}

	if (gridCopy[row - 2][0] == 'X'){
		z++;
	}

	if (z == 0 || z == 1)
		grid[row - 1][0] = '-';

	if (z == 3)
		grid[row - 1][0] = 'X';

	//////////////////////////////      BR       //////////////////

	int zz = 0;

	if (gridCopy[row - 1][column - 2] == 'X'){
		zz++;
	}

	if (gridCopy[row - 2][column - 2] == 'X'){
		zz++;
	}

	if (gridCopy[row - 2][column - 1] == 'X'){
		zz++;
	}

	if (z == 0 || z == 1)
		grid[row - 1][column - 1] = '-';

	if (z == 3)
		grid[row - 1][column - 1] = 'X';

}

void printGrid(int row, int column, char **grid){

	for (int i = 0; i < row; i++)
	{
		if (i > 0)
			printf("\n");
		for (int j = 0; j < column; j++)
		{
			printf("%c", grid[i][j]);
		}
	}

	printf("\n");
}

void edgeCheck(int row, int column, char **grid, char **gridCopy){

	row = row - 1;
	column = column - 1;

	//   -------
	//   -------
	//   -------
	//	 -------

	//////////////////// Upper edge ////////////////////////////

	int d = 0;

	for (int x = 1; x <= column; x++)
	{
		if (gridCopy[0][x-1] == 'X')
			d++;
		if (gridCopy[0][x+1] == 'X')
			d++;
		if (gridCopy[1][x - 1] == 'X')
			d++;
		if (gridCopy[1][x] == 'X')
			d++;
		if (gridCopy[1][x + 1] == 'X')
			d++;

		if (d == 1 || d == 0 || d >= 4)
			grid[0][x] = '-';

		if (d == 3)
			grid[0][x] = 'X';

		////////////////////////////////         Bottom Edge Checking   ////////////////////////////

		d = 0;

		if (gridCopy[row][x-1] == 'X')
			d++;
		if (gridCopy[row][x+1] == 'X')
			d++;
		if (gridCopy[row - 1][x - 1] == 'X')
			d++;
		if (gridCopy[row - 1][x] == 'X')
			d++;
		if (gridCopy[row - 1][x + 1] == 'X')
			d++;

		if(d == 1 || d==0 || d >= 4)
			grid[row][x] = '-';

		if(d == 3)
			grid[row][x] = 'X';

	}

	/////////////////////////////////////   Left Edge    ///////////////////////////

	int q = 0;

	for (int g = 1; g < row; g++)
	{
		if(gridCopy[g-1][0] == 'X')
			q++;
		if(gridCopy[g-1][1] == 'X')
			q++;
		if(gridCopy[g][1] == 'X')
			q++;
		if(gridCopy[g+1][1] == 'X')
			q++;
		if(gridCopy[g+1][0] == 'X')
			q++;

		if (q == 1 || q == 0 || q >= 4)
			grid[g][0] = '-';

		if (q == 3)
			grid[g][0] = 'X';


		///////////////////////////////      Right Edge        ///////////////////////

		q = 0;

		if(gridCopy[g-1][column] == 'X')
			q++;
		if(gridCopy[g+1][column] == 'X')
			q++;
		if(gridCopy[g-1][column-1] == 'X')
			q++;
		if(gridCopy[g][column-1] == 'X')
			q++;
		if(gridCopy[g+1][column-1] == 'X')
			q++;

		if(q == 1 || q == 0 || q >= 4)
			grid[g][column] = '-';

		if(q == 3)
			grid[g][column] = 'X';
	}
}

void centerCheck(int row, int column, char **grid, char **gridCopy){

	row = row - 1;
	column = column - 1;

	for(int i = 1; i < row; i++)
	{
		for(int y = 1; y < column; y++)
		{
			int a = 0;

			if(gridCopy[i][y+1] == 'X')
				a++;
			if(gridCopy[i][y-1] == 'X')
				a++;
			if(gridCopy[i+1][y-1] == 'X')
				a++;
			if(gridCopy[i-1][y-1] == 'X')
				a++;
			if(gridCopy[i+1][y] == 'X')
				a++;
			if(gridCopy[i+1][y+1] == 'X')
				a++;
			if(gridCopy[i-1][y+1] == 'X')
				a++;
			if(gridCopy[i-1][y] == 'X')
				a++;


			if(a == 1 || a == 0 || a >= 4)
				grid[i][y] = '-';

			if(a == 3)
				grid[i][y] = 'X';	
		}
	}

	return;

}

void nextGrid(int row, int column, char** grid, char **gridCopy){

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			gridCopy[i][j] = grid[i][j];
		}
	}
}

void freeMem(int column, char **grid, char **gridCopy, int rows){

	

	delete grid;
	delete gridCopy;
	

}
