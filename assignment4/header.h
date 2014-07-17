/////////////////////////
//Done by:             //
//		       //	
//Rafay Ahmed Khan     //
//Mohammad Moaaz Ahmad //
//26th April, 2014     //
//  		       //
/////////////////////////

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <stdlib.h>
using namespace std;



class Hangman
{
protected:
	int m_Guesses;// max number of incorrect guesses allowed
	int m_SizeOfWord;
	bool m_PrintPossibleWords;
	vector<string> words;

public:

	Hangman();
	void run();

};


Hangman::Hangman()
{
	ifstream infile;
	vector<string>AllWords;
	string tempword;

	infile.open("dictionary.txt");

	while( getline(infile, tempword) )
	{
		AllWords.push_back(tempword);

	}

	//cout<<endl<<"Size of AllWord vector="<<AllWords.size();

	cout<<"Please enter the length of the word to guess: ";
	cin>>m_SizeOfWord;


	cout<<"Please enter the number of guesses you wish to have :";
	cin>>m_Guesses;

	char option;
	cout<<"Print the number of possible words left after each guess? (Y) or (N): ";
	cin>>option;

	if (option=='Y')
		m_PrintPossibleWords=true;
	else
		m_PrintPossibleWords=false;





	for (int i=0; i<AllWords.size(); i++)
	{
		if (AllWords[i].size()==m_SizeOfWord)
			words.push_back(AllWords[i]);
	}


	if (words.size()==0)
	{
		cout<<"\nWords of this length not found!"<<endl;
		exit(EXIT_FAILURE);
	}

	//cout<<endl<<"Size of words vector="<<words.size();


}

void Hangman::run()
{
	srand(time(0));
	random_shuffle(words.begin(),words.end());// randomizes the list of words, so as to pick a rand word from list

	const string THE_WORD= words[0];   // word to guess
	int wrong=0 ;                      // number of incorrect guesses

	string soFar(THE_WORD.size(),'-'); //word guessed so far, the bracket teel to initailze the string
	//with '-' for the size of word 

	string used= "";                   //leters already guessed

	//cout<<THE_WORD<<endl;
	cout<<"\nYou have "<< (m_Guesses - wrong) <<" guesses remaining.";
	cout<<endl<<soFar<<endl;

	//main loop
	while ( (wrong<m_Guesses ) && (soFar!= THE_WORD) )
	{
		if(m_PrintPossibleWords==true)
			cout<<"\nThere are "<<words.size()<<" possible words left.\n";


		char guess;
		cout<<"Please guess a letter: ";
		cin>>guess;



		while(used.find(guess) != string::npos)
		{
			cout<< "\nYou've already guessed '"<<guess << "'." << endl;
			cout<< "Enter your guess: ";
			cin>>guess;

		}


		used +=guess;

		if (THE_WORD.find(guess) !=string::npos)
		{
			cout<<"That's right! '"<< guess <<"' is in the word.\n";

			//update soFar to include newly guessed letter
			for (int i=0; i< THE_WORD.length(); i++)
			{
				if (THE_WORD[i] == guess)
					soFar[i] =guess;
			}

		}

		else
		{
			cout<<"Sorry, '"<< guess <<"' isn't in the word.\n";
			++wrong;

		}

		cout<<"\nYou have "<< (m_Guesses - wrong) <<" guesses remaining.";
		cout<<endl<<soFar<<endl;


	}


	if (wrong==m_Guesses)
	{

		cout << "\n\n\t    *************** Game Over ***************" << endl;
		cout << "Sorry! The word was: " << THE_WORD <<".\nYou entered: " << soFar << "." << endl;
	}
	else
	{
		cout << "\n\n\t    *************** Game Over ***************" << endl;
		cout << "You guessed right! The word was: "<<THE_WORD<<"." << endl;
	}

}

class EvilHangman : public Hangman
{
public :
	void run();

	EvilHangman(): Hangman(){};
};


void EvilHangman::run()
{
	string soFar(m_SizeOfWord,'-');
	string THE_WORD(m_SizeOfWord,'-');// just the length of the word initialized to "-"
	int wrong=0;// number of incorrect guesses
	string used= "";  //leters already guessed
	vector<string> CurrentWordList(words);


	cout<<"You have "<< (m_Guesses - wrong) <<" guesses remaining.";
	cout<<endl<<soFar;

	//main loop
	while ( (wrong<m_Guesses ) )
	{
		if(m_PrintPossibleWords==true)
			cout<<"\nThere are "<<CurrentWordList.size()<<" possible words left.";


		char guess;
		cout<<"\nPlease guess a letter: ";
		cin>>guess;



		while(used.find(guess) != string::npos)
		{
			cout<< "\nYou've already guessed "<<guess <<endl;
			cout<< "Enter your guess: ";
			cin>>guess;

		}


		used +=guess;



		map<string,vector<string> >famlies;
		for(int i=0; i<CurrentWordList.size(); i++)
		{
			string WordFormat(m_SizeOfWord,'-');
			string temp=CurrentWordList[i];

			for (int j=0; j<temp.size(); j++)
			{
				if (temp[j]==guess)
					WordFormat[j]=guess;
			}

			famlies[WordFormat.c_str()].push_back(temp);


		}

		map<string,vector<string> >:: iterator iter;
		string Highest="";
		int highestwords=0;


		for(iter=famlies.begin(); iter!=famlies.end(); iter++)
		{
			string format=iter->first;
			vector<string> &vec=iter->second;
			//cout<<endl<<"format :"<< format<<endl<<" size: "<<highestwords<<endl;
			if (vec.size()>highestwords)
			{
				Highest=format;
				highestwords=vec.size();
			}
		}


		if (Highest!=soFar)
		{
			for(int i=0; i<Highest.size(); i++)
			{
				if(Highest[i]==guess)
					soFar[i]=guess;
			}
		}

		if (Highest.find(guess) ==string::npos)
		{
			cout<<"Sorry, "<< guess <<" isn't in the word.\n";
			++wrong;
		}
		else
		{
			cout<<"That's right! "<< guess <<" is in the word.\n";
		}

		//cout<<Highest<<" "<<highestwords<<endl;
		CurrentWordList=famlies[Highest];

		cout<<"\nYou have "<< (m_Guesses - wrong) <<" guesses remaining.";
		cout<<endl<<soFar;
	}



	random_shuffle(CurrentWordList.begin(),CurrentWordList.end());
	THE_WORD=CurrentWordList[0];

	if (wrong==m_Guesses)
	{

		cout << "\n\n\t    *************** Game Over ***************" << endl;
		cout << "Sorry! The word was: " << THE_WORD <<".\nYou entered: " << soFar << "." << endl;
	}
	else
	{
		cout << "\n\n\t    *************** Game Over ***************" << endl;
		cout << "You guessed right! The word was: "<<THE_WORD<<"." << endl;
	}





}


