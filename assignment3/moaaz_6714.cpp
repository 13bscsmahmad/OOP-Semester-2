// Mohammad Moaaz Ahmad	  	 //
// Registration # 6714	  	 //
// BS(CS) - 3A		  	 //
// 4th April, 2014	  	 //
// Assignment 03 - March Madness //		
///////////////////////////////////

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <string.h>

std::string getID(std::string teamName);
std::string* token(std::string str);
std::string getSeasonLetter(std::string season);
std::string rpiChampion(std::string season);
std::string champion(std::string season);
void list(std::string season, std::string team);
void finalRecord(std::string season, std::string team);
std::string mostWins(std::string season);
std::string mostAwayWins(std::string season);
std::string bestWinPercentage(std::string season);
std::string mostPoints(std::string season);
std::string fewestPointsAllowed(std::string season);
std::string largestMargin(std::string season);


int main (int argc, char** argv){

  //Q1

  if (!strcmp(argv[1], "rpiChampion")){
    std::cout << rpiChampion(argv[2]) << std::endl; 
  } 
	
  //Q2

  if (!strcmp(argv[1], "champion"))
      std::cout << champion(argv[2]) << std::endl;
  //Q3

  if (!strcmp(argv[1], "list"))
    list(argv[2], argv[3]);
	
  //Q4

  if (!strcmp(argv[1], "finalRecord"))
    finalRecord(argv[2], argv[3]);

  //Q5
	
  if (!strcmp(argv[1], "mostWins"))
      std::cout << mostWins(argv[2]) << std::endl;

  //Q6

  if (!strcmp(argv[1], "mostAwayWins"))
      std::cout << mostAwayWins(argv[2]) << std::endl;
	
  //Q7

  if (!strcmp(argv[1], "bestWinPercentage"))
      std::cout << bestWinPercentage(argv[2]) << std::endl;
	
  //Q8

  if (!strcmp(argv[1], "mostPoints"))
      std::cout << mostPoints(argv[2]) << std::endl;
	
  //Q9

  if (!strcmp(argv[1], "fewestPointsAllowed"))
      std::cout << fewestPointsAllowed(argv[2]) << std::endl;
	
  //Q10

  if (!strcmp(argv[1], "largestMargin"))
      std::cout << largestMargin(argv[2]) << std::endl;

	return 0;
}

////////////////////////////////////////////////////////////// -- Function Definitions -- /////////////////////////////////////////////////////////////////

        /*
	season --> tokens[0]
	daynum --> tokens[1]
	wteam --> tokens[2]
	wscore --> tokens[3]
	lteam --> tokens[4]
	lscore --> tokens[5]
	wloc --> tokens[6]
	*/

std::string getID(std::string teamName){

	std::ifstream teams;
	teams.open("teams.csv");

	if (!teams.is_open()){
		return "Could not open file";
	}

	std::string line;
	std::string* tokens = new std::string[2];

	while (getline(teams, line)){
		tokens = token(line);
		if (tokens[1] == teamName){
			teams.close();
			return tokens[0];
		}
	}

	teams.close();
}
std::string getTeamName(std::string ID){

	std::ifstream teams;
	teams.open("teams.csv");

	if (!teams.is_open()){
		return "Could not open file";
	}

	std::string line;
	std::string* tokens = new std::string[2];

	while (getline(teams, line)){
		tokens = token(line);
		if (tokens[0] == ID){
			teams.close();
			return tokens[1];
		}
	}

	teams.close();

}

std::string rpiChampion(std::string season){

	std::string seasonL = getSeasonLetter(season);

	std::ifstream tourney_combined;
	tourney_combined.open("regular_tourney_combined_results.csv");

	if (!(tourney_combined.is_open()))
		return "Error opening file.\n";

	std::map<int, int> wins;
	std::map<int, int> TotalGamesPlayed;
	std::map<int, std::vector<int>> Opponents;
	std::map<int, float> TeamWinPercent;
	std::map<int,float> TeamRPI  ;

	std::string line;
	std::string* tokens = new std::string[7];

	
	while (getline(tourney_combined, line)){

		tokens = token(line);
		if (tokens[0] == seasonL){
			wins[atoi(tokens[2].c_str() )] += 1;
			Opponents[stoi(tokens[2])].push_back(stoi(tokens[4]));
			Opponents[stoi(tokens[4])].push_back(stoi(tokens[2]));
			TotalGamesPlayed[stoi(tokens[2])] += 1;
			TotalGamesPlayed[stoi(tokens[4])] += 1;
		}

	}


	for(int team = 501; team < 856; team++)
	{

		if (wins[team]==0) //Hack
			continue;

		float total = TotalGamesPlayed[team];
		float w = wins[team];
		float percent = (w / total)*100;
		TeamWinPercent[team] = percent;
	}

	for(int team=501; team<856; team++){

		float TotalOpGames = 0;
		float OpWins = 0;
		float OpWinPercent = 0;
		float TotalOpsOpGames = 0;
		float OpsOpWins = 0;
		float OpsOpWinPercent = 0;


		if (wins[team]==0) 
			continue;


		for (std::map<int, std::vector<int> >::iterator it = Opponents.begin(); it != Opponents.end(); it++){
			int t = it->first;
			std::vector<int>& vec = it-> second;

			if (t==team){
				for (int i = 0; i < vec.size(); i++){
					TotalOpGames+=TotalGamesPlayed[vec[i]];
					OpWins += wins[vec[i]];

					for (std::map<int, std::vector<int> >::iterator itr = Opponents.begin(); itr != Opponents.end(); itr++){
						int iter = itr->first;
						std::vector<int>& vec2 = itr->second;

						if(iter == vec[i]){

							for (int j = 0; j < vec2.size(); j++){

								TotalOpsOpGames += TotalGamesPlayed[vec2[j]];
								OpsOpWins += wins[vec2[j]];
							}
						}
					}
				}
			}
		}

		OpWinPercent = (OpWins / TotalOpGames) * 100;
		OpsOpWinPercent= (OpsOpWins / TotalOpsOpGames) * 100;
		TeamRPI[team] = 0.25 * TeamWinPercent[team] + 0.5 * OpWinPercent + 0.25 * OpsOpWinPercent;
	}


	int highest=501;

	for(int team = 501; team < 856; team++){
		if (TeamRPI[highest] <= TeamRPI[team]){
			highest = team;
		}
	}

	tourney_combined.close();

	return getTeamName(std::to_string(highest)); 
} //Borrowed from Rafay

std::string getSeasonLetter(std::string season){

	std::ifstream seasons;
	seasons.open("seasons.csv");
	if (!(seasons.is_open()))
		return "Error opening file";

	std::string line;
	std::string* tokens = new std::string[2];

	while (getline(seasons, line)){
		tokens = token(line);
		if (tokens[1] == season){
			seasons.close();
			return tokens[0];
		}
	}

	seasons.close();
}

std::string champion(std::string season){

	//Q2

	std::string letter = getSeasonLetter(season);

	std::ifstream tourney_results;
	std::string championID;

	tourney_results.open("tourney_results.csv");
	if (!(tourney_results.is_open())){
		return "Error opening file";
	}

	std::vector<std::string> records;

	std::string line;

	while(getline(tourney_results, line)){
		records.push_back(line);
	}

	std::string* tokens = new std::string[6];
	std::string* next_tokens = new std::string[6];

	for (int i = 0; i < records.size(); i++){

		tokens = token(records[i]);

		if (tokens[0] == letter){
			next_tokens = token(records[i+1]);

			if (next_tokens[0] != tokens[0]){
				tourney_results.close();
				return getTeamName(tokens[2]);
			}
		}

	}

	tourney_results.close();
}

void list(std::string season, std::string team){

	//Q3

	std::ifstream combined_results;
	std::vector<std::string> results;
	std::string teamID = getID(team);
	std::string sLetter = getSeasonLetter(season);

	combined_results.open("regular_tourney_combined_results.csv");

	if (!(combined_results.is_open())){
		std::cout << "Error opening file." << std::endl;
		return;
	}

	std::string line;
	while (getline(combined_results, line)){

		std::string* tokens = new std::string[7];
		tokens = token(line);
		if (tokens[2] == teamID || tokens[4] == teamID)
			results.push_back(line);
	}

	for (int i = 0; i < results.size(); i++){

		std::string* tokens = new std::string[7];
		tokens = token(results[i]);

		if (tokens[0] == sLetter){

			//W or L
			if (tokens[2] == teamID) std::cout << 'W' << " ";
			if (tokens[4] == teamID) std::cout << 'L' << " "; 

			//Opponent
			if (tokens[2] == teamID) std::cout << getTeamName(tokens[4]) << " ";
			if (tokens[4] == teamID) std::cout << getTeamName(tokens[2]) << " "; 

			//Scores
			if (tokens[2] == teamID) std::cout << tokens[3] <<"-"<< tokens[5];
			if (tokens[4] == teamID) std::cout << tokens[5] <<"-" << tokens[3]; //Scores

			std::cout << std::endl;
		}

	}

	combined_results.close();

}

void finalRecord(std::string season, std::string team){

	//Q4
	std::string teamID = getID(team);
	std::string seasonL = getSeasonLetter(season);

	std::ifstream tourney_combined;
	tourney_combined.open("regular_tourney_combined_results.csv");

	if (!(tourney_combined.is_open())){
		std::cout << "Error opening file." << std::endl;
		return;
	}

	std::string* tokens = new std::string[7];

	std::string line;
	int wins = 0;
	int losses = 0;

	while (getline(tourney_combined, line)){

		tokens = token(line);
		if (tokens[0] == seasonL){

			if (tokens[2] == teamID)
				wins++;

			if (tokens[4] == teamID)
				losses++;
		}
	}
	std::cout << wins << "-" << losses << std::endl;
	tourney_combined.close();

}

std::string mostWins(std::string season){

	//Q5

	std::ifstream tourney_combined; 
	std::string line;
	std::string seasonL = getSeasonLetter(season);
	std::map<int, int> TeamWinRecords;

	tourney_combined.open("regular_tourney_combined_results.csv");

	if (!(tourney_combined.is_open())){
		return "Error opening file\n";
	}

	std::string* tokens = new std::string[7];

	while (getline(tourney_combined, line)){

		tokens = token(line); 
		if (tokens[0] == seasonL){

			TeamWinRecords[stoi(tokens[2])] += 1;
		}
	}

	int highest=501;

	for(int team = 501; team < 856; team++){

		if (TeamWinRecords[highest] < TeamWinRecords[team])
			highest = team;
	}

	tourney_combined.close();

	return getTeamName(std::to_string(highest)); 

}

std::string mostAwayWins(std::string season){

	//Q6

	std::ifstream tourney_combined; 
	std::string line;
	std::string seasonL = getSeasonLetter(season);
	std::map<int, int> TeamWinRecords;

	tourney_combined.open("regular_tourney_combined_results.csv");

	if (!(tourney_combined.is_open())){
		return "Error opening file\n";
	}

	std::string* tokens = new std::string[7];

	while (getline(tourney_combined, line)){

		tokens = token(line); 
		if (tokens[0] == seasonL && tokens[6] == "A"){

			TeamWinRecords[stoi(tokens[2])] += 1;
		}
	}

	int highest=501;

	for(int team = 501; team < 856; team++){

		if (TeamWinRecords[highest] < TeamWinRecords[team])
			highest = team;
	}

	tourney_combined.close();

	return getTeamName(std::to_string(highest)); 


}

std::string bestWinPercentage(std::string season){

	//Q7

	std::ifstream infile; 
	std::string line;
	std::map<int, int> wins;
	std::map<int, int> AllGames;
	std::map<int,float> TWP;

	std::string seasonL = getSeasonLetter(season);

	infile.open("regular_tourney_combined_results.csv");
	std::string* tokens = new std::string[7];


	while (getline(infile, line)){


		tokens = token(line); 
		if (tokens[0] == seasonL){
			wins[stoi(tokens[2])]= wins[stoi(tokens[2])] + 1;
			AllGames[stoi(tokens[4])] = 1 + AllGames[stoi(tokens[4])];
			AllGames[stoi(tokens[2])] = 1 + AllGames[stoi(tokens[2])];
		}

	}

	for(int teams = 501; teams < 856; teams++){

		if (wins[teams] == 0) // Hack 
			continue;

		float total = AllGames[teams];
		float w = wins[teams];

		TWP[teams] = (w/total)*100;

	}


	int max = 501;

	for(int teams=501; teams<856; teams++){
		if (TWP[max] <= TWP[teams]){
			max = teams;

		}
	}

	infile.close();

	return getTeamName(std::to_string(max)); 

}

std::string mostPoints(std::string season){

	std::string seasonL = getSeasonLetter(season);

	std::ifstream tourney_combined;
	tourney_combined.open("regular_tourney_combined_results.csv");

	if (!(tourney_combined.is_open()))
		return "Error opening file.\n";

	std::map<int, int> mostPoints;
	std::string line;
	std::string* tokens = new std::string[7];

	while (getline(tourney_combined, line)){

		tokens = token(line);

		if (tokens[0] == seasonL){
			mostPoints[stoi(tokens[2]) ] += stoi(tokens[3]);
			mostPoints[stoi(tokens[4]) ] += stoi(tokens[5]);

		}

	}

	int max = 501;

	for(int teams = 501; teams < 856; teams++)
	{

		if(mostPoints[teams] == 0)
			continue;

		if (mostPoints[max] < mostPoints[teams])
			max = teams;
	}

	tourney_combined.close();
	return getTeamName(std::to_string(max));

}

std::string fewestPointsAllowed(std::string season){

	std::string seasonL = getSeasonLetter(season);
	std::map<int, int> FewestPoints;
	std::ifstream tourney_combined;
	tourney_combined.open("regular_tourney_combined_results.csv");

	if (!(tourney_combined.is_open()))
		return "Error opening file.\n";

	std::string line;
	std::string* tokens  = new std::string[7];

	while (getline(tourney_combined, line)){

		tokens = token(line);
		if (tokens[0] == seasonL){
			FewestPoints[stoi(tokens[2])]+=stoi(tokens[5]);
			FewestPoints[stoi(tokens[4])]+=stoi(tokens[3]);
		}
	}

	int min = 559;

	for(int teams = 501; teams < 856; teams++)
	{

		if(FewestPoints[teams]==0)
			continue;

		if (FewestPoints[min]>FewestPoints[teams])
			min=teams;

	}

	tourney_combined.close();

	return getTeamName(std::to_string(min));
}

std::string largestMargin(std::string season){

	std::string seasonL = getSeasonLetter(season);
	std::map<int, int> PointsDifference;
	std::map<int, int> totalGames;
	std::map<int,float> Margin  ;
	std::ifstream tourney_combined;
	tourney_combined.open("regular_tourney_combined_results.csv");

	if (!(tourney_combined.is_open()))
		return "Error opening file.\n";

	std::string line;
	std::string* tokens  = new std::string[7];

	while (getline(tourney_combined, line)){

		tokens = token(line);
		if (tokens[0] == seasonL){
			PointsDifference[stoi(tokens[2])] += stoi(tokens[3])-stoi(tokens[5]);
			PointsDifference[stoi(tokens[4])] -= stoi(tokens[3])-stoi(tokens[5]);
			totalGames[stoi(tokens[2])] += 1;
			totalGames[stoi(tokens[4])] += 1;
		}
	}

	for(int teams = 501; teams < 856; teams++)
	{


		if (PointsDifference[teams] == 0 || totalGames[teams] == 0)// Hack
			continue;

		float totalMargin = PointsDifference[teams];
		float games = totalGames[teams];
		Margin[teams] = totalMargin / games;
	}


	int max = 501;

	for(int teams = 501; teams < 856; teams++)
	{
		if (Margin[max] < Margin[teams])
		{
			max = teams;
		}
	}

	tourney_combined.close();

	return getTeamName(std::to_string(max)); 

}

std::string* token(std::string string)
{
	if (string.find(',') != std::string::npos){

		int countDelimiter = 0;
		std::string *strArr;

		for (int i = 0; i < string.length(); i ++){

			if (string[i] == ','){
				countDelimiter++;
			}
		}

		strArr = new std::string[countDelimiter + 1];
		std::string temp;

		for (int i = 0; i < (countDelimiter + 1); i++){

			strArr[i] = string.substr(0, string.find(','));
			temp = string.substr(string.find(',') + 1, string.length());
			string = temp;
		}
		return strArr;

	} else {
		return NULL;
	}
}
