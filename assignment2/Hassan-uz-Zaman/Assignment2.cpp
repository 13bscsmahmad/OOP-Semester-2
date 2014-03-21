#include <iostream>
#include <fstream>

class map
{
	int rows;
	int cols;
	char** array;
	int roboti;
	int robotj;
	int starti;
	int startj;
	int RCount;
	int mindist;

	int** visited;
	int*** distinctPaths;
	int path;
	int steps;
	char filename[20];
	int dist;
	int desti;
	int destj;

	void getMap(void)
	{
		char temp;
		int i = 0;
		int j = 0;
		std::ifstream inFile;
		inFile.open(filename);


		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				inFile.get(array[i][j]);
				if (array[i][j] == 'R')
				{
					roboti = i;
					robotj = j;
					starti = i;
					startj = j;
				}
			}
			inFile.get(temp);
		}
		inFile.close();
	}
	void getDims(void)
	{
		std::ifstream inFile;
		std::cout << "Please enter the input file's name: ";
		std::cin >> filename;
		std::cout << "\n\n";
		char temp = NULL;
		inFile.open(filename);
		cols = -1;
		do
		{
			inFile.get(temp);
			cols++;
		} while (temp != '\n' && !inFile.eof());
		rows = 1;
		while (!inFile.eof())
		{
			do
			{
				inFile.get(temp);
			} while (temp != '\n' && !inFile.eof());
			rows++;
		}
		inFile.close();
	}
	bool checkVisited (int a, int b)
	{
		for (int i = 0; i < (rows*cols); i++)
		{
			if (visited[i][0] == a && visited[i][1] == b)
				return 1;
		}
		return 0;
	}

public:

	map (void)
	{
		getDims();
		steps = 0;

		//Create the array to store the map in it.
		array = new char* [rows];
		for (int i= 0; i < rows; i++)
		{
			*(array+i) = new char [cols];
			for (int j = 0; j < cols; j++)
			{
				array[i][j] = NULL;
			}
		}

		//Create array to store visited coordinates.
		visited = new int* [rows*cols];
		for (int i= 0; i < (rows*cols); i++)
		{
			*(visited+i) = new int [2];
			for (int j = 0; j < 2; j++)
			{
				visited[i][j] = 0;
			}
		}

		getMap();
	}
	void printMap (void)
	{
		for (int i= 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				std::cout << array[i][j];
			}
			std::cout << "\n";
		}
	}
	int getPath (void)
	{
		visited[steps][0] = roboti;
		visited[steps][1] = robotj;
		steps++;
		//std::cout << "Step #"<< steps-1 << ": Robot position = " << roboti << ", " << robotj << " (" << array[roboti][robotj] << ")\n";
		if (array[roboti][robotj] == 'F')
			return 1;
		array[roboti][robotj] = 'R';

		if (!checkVisited(roboti,robotj+1) && array[roboti][robotj+1] != '#')
		{
			++robotj;
			if (getPath())
				return 1;
			else
			{
				array[roboti][robotj] = ' ';
				--robotj;
			}
		}

		if (!checkVisited(roboti+1,robotj) && array[roboti+1][robotj] != '#')
		{
			++roboti;
			if (getPath())
				return 1;
			else
			{
				array[roboti][robotj] = ' ';
				--roboti;
			}
		}

		if (!checkVisited(roboti,robotj-1) && array[roboti][robotj-1] != '#')
		{
			--robotj;
			if (getPath())
				return 1;
			else
			{
				array[roboti][robotj] = ' ';
				++robotj;
			}
		}

		if (!checkVisited(roboti-1,robotj) && array[roboti-1][robotj] != '#')
		{
			--roboti;
			if (getPath())
				return 1;
			else
			{
				array[roboti][robotj] = ' ';
				++roboti;
			}
		}

		return 0;


	}
	void getShortestPath (void)
	{
		std::cout << "\nWorking out the shortest path....\n\n";
		RCount = 0;
		//Create array to store distinctPaths paths.
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (array[i][j] == 'R')
					RCount++;
			}
		}
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (array[i][j] == 'F')
				{
					desti = i;
					destj = j;
				}
			}
		}


		distinctPaths = new int** [RCount * RCount];
		for (int h = 0; h < RCount*RCount; h++)
		{
			*(distinctPaths+h) = new int* [RCount];
			for (int i= 0; i < (RCount); i++)
			{
				*(*(distinctPaths+h)+i) = new int [2];
				for (int j = 0; j < 2; j++)
				{
					distinctPaths[h][i][j] = 0;
				}
			}
		}

		mindist = RCount;
		steps = 0;
		path = 0;
		do
		{
			roboti = starti;
			robotj = startj;
			dist = 0;
			shortestPath();
			//std::cout << "Path #" << path << ": Step #" << dist << "\n";
			path++;
		} while (dist != 0);
		//std::cout << "Done with the paths.";
		path--;
		path--;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (array[i][j] == 'R')
					array[i][j] = ' ';
			}
		}
		array[starti][startj] = 'R';
		for (int i = 0; i < mindist; i++)
		{
			array[distinctPaths[path][i][0]][distinctPaths[path][i][1]] = 'R';
			if (distinctPaths[path][i][0] == desti && distinctPaths[path][i][1] == destj)
			{
				array[distinctPaths[path][i][0]][distinctPaths[path][i][1]] = 'F';
				break;
			}
		}

	}

	int checkDistinct (int path, int a, int b, int dist)
	{
		for (int i = 0; i < dist; i++)
		{
			if (distinctPaths[path][i][0] == a && distinctPaths[path][i][1] == b)
			{
				return 1;
			}
		}
		return 0;
	}

	int shortestPath ()
	{
		distinctPaths[path][dist][0] = roboti;
		distinctPaths[path][dist][1] = robotj;
		//std::cout << "Path #" << path << ": Step #"<< dist << ": Robot position = " << roboti << ", " << robotj << " (Min dist: " << mindist << ")\n";
		if (array[roboti][robotj] == 'F')
		{
			if (dist != 0)
				mindist = dist;
			return 1;
		}

		
		if (dist < mindist - 1 && !checkDistinct(path, roboti, robotj+1, dist) && (array[roboti][robotj+1] == 'R' || array[roboti][robotj+1] == 'F' || array[roboti][robotj+1] == ' '))
		{
			++robotj;
			++dist;
			if (shortestPath())
				return 1;
			else
			{
				--dist;
				--robotj;
			}
		}

		if (dist < mindist - 1 && !checkDistinct(path, roboti, robotj-1, dist) && (array[roboti][robotj-1] == 'R' || array[roboti][robotj-1] == 'F' || array[roboti][robotj-1] == ' '))
		{
			--robotj;
			++dist;
			if (shortestPath())
				return 1;
			else
			{
				--dist;
				++robotj;
			}
		}

		if (dist < mindist - 1 && !checkDistinct(path, roboti+1, robotj, dist) && (array[roboti+1][robotj] == 'R' || array[roboti+1][robotj] == 'F' || array[roboti+1][robotj] == ' '))
		{
			++roboti;
			++dist;
			if (shortestPath())
				return 1;
			else
			{
				--dist;
				--roboti;
			}
		}


		if (dist < mindist - 1 && !checkDistinct(path, roboti-1, robotj, dist) && (array[roboti-1][robotj] == 'R' || array[roboti-1][robotj] == 'F' || array[roboti-1][robotj] == ' '))
		{
			--roboti;
			++dist;
			if (shortestPath())
				return 1;
			else
			{
				--dist;
				++roboti;
			}
		}

		return 0;
	}
};

int main (void)
{
	map map1;
	map1.printMap();
	map1.getPath();
	std::cout << "\n\nFridge reached! \n\n";
	map1.printMap();
	map1.getShortestPath();
	map1.printMap();
	return 0;
}
