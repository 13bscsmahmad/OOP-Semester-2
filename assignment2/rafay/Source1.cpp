// Done by Rafay A. Khan
// BSCS 3A 
//Reg# 04848



#include <iostream>
#include <string>
#include <fstream>
using namespace std;

bool execution=true;// variabe to control back tracking

class Robot{

	string fname;//file name
	string temp;
	string *map;
	int row, col, startx, starty;

public:
	Robot(string File);
	void findFridge();
	void displayMap();
	void recursive(int,int);
};

Robot:: Robot(string File)
{
	ifstream infile;// file pointer
	row=0;
	col=0;

	fname=File;



	

	infile.open(fname.c_str());




	cout<<"The given map:"<<endl<<endl;

	while (!infile.eof())
	{
		getline(infile,temp);
		cout<<temp<<endl;
		row++;


	}


	col=temp.size();



	map=new string [row];

	infile.seekg(0,infile.beg);

	for (int i=0; i<row; i++)
	{
		getline(infile,map[i]);

	}


	


	startx=0, starty=0;


	for  ( int i=0 ;i<row; i++)
	{
		for (int j=0 ; j<col; j++)
		{
			if (map[i][j]=='R')
			{
				startx=i;
				starty=j;
			}
		}

	}


	//cout<<startx<<starty;
}






void Robot::findFridge()
{

	recursive(startx,starty);// calls the recirsive functions with initial coordinates of 'R'
}


void Robot::recursive(int x, int y)
{



	if ( map[x][y+1]=='F'||map[x][y-1]=='F'||map[x+1][y]=='F'||map[x-1][y]=='F')
	{
		map[x][y]='R';
		execution=false ;

		return;


	}


	
	map[x][y]='R';


	

	if (map[x][y-1]==' ')//west
		recursive(x, y-1);
	else
		if (map[x-1][y]==' ')//north
			recursive(x-1, y);
		else
			if (map[x][y+1]==' ')//east
				recursive(x, y+1);
			else
				if (map[x+1][y]==' ')//south
					recursive(x+1, y);





	// the function below only runs it it gets to a dead end 
	if (execution)
	{



		if (map[x][y-1]==' ')//west
			recursive(x, y-1);
		else
			if (map[x-1][y]==' ')//north
				recursive(x-1, y);
			else
				if (map[x][y+1]==' ')//east
					recursive(x, y+1);
				else
					if (map[x+1][y]==' ')//south
						recursive(x+1, y);
		//**************************************************
		//*******************THIS CONDITTON HELPS NOT TO PRIND THAT EXTRA EMPTY SPACE 
		//*******************TRY TO REMOVE THE if CONDITION TO SEE IT HAPPEN

		if (execution)
		{
			map[x][y]='.';
		}
		//PS. remove the above coments when you understand  


	}

}




void Robot::displayMap()
{
	for  ( int i=0 ;i<row; i++)
	{
		for (int j=0 ; j<col; j++)
		{
			if (map[i][j]=='.')
				map[i][j]=' ';
		}

	}

	cout<<endl<<"The Path to the fridge is: "<<endl<<endl;



	for (int i=0; i<row; i++)
	{
			cout<<endl<<map[i];
	}

	cout<<endl;
}



int main(int argc, char** argv) { 


	Robot robot(argv[1]); //read in the input map file. 
	robot.findFridge(); //find the path to the fridge 
	robot.displayMap(); //display the map with the path that was found 
} 

