#include <iostream>
#include <fstream>		//File reading
#include "List.h"
#include "Music.h"
#include <Windows.h>	//Console Utility
#include <ctime>		//Elapsed Time
#include "concol.h"		//Console Colors
#include <iomanip>		//std::setw
#include <algorithm>	//Find If


using namespace std;
using namespace eku;

int musicInfoFileLength = 779074;

/* Color Legend
Yellow - Progress Bar/Status Message
Pink - Input Message
Cyan - Input/Numbers
White - Progress Message
Blue - String Message
Red - Title
*/

//START OF UTILITY

/*
Check if string is a positive number
@param s String to check
@return Whether it is a number or not
*/
bool is_number(const string& s)
{
	return !s.empty() && find_if(s.begin(),
		s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

/* An Inline Progress Bar
@param x Current Index
@param n Total Number of Progress
@param w Width of the bar
@param beginClock Start of elapsed time
*/
static inline void loadbar(unsigned int x, unsigned int n, clock_t beginClock, unsigned int w = 20)
{
	if ((x != n) && (x % (n / 100 + 1) != 0) && n >= 2000) return;

	//Get Elapsed Time
	clock_t endClock = clock();
	double elapsedSec = double(endClock - beginClock) / CLOCKS_PER_SEC;

	float ratio = x / (float)n;
	int   c = ratio * w;

	cout << setw(3) << white << "Parsed: " << cyan << x << white << "/" << green << n << yellow << " [";
	for (int x = 0; x<c; x++) cout << "=";
	for (int x = c; x<w; x++) cout << " ";
	cout << "] " << (int)(ratio * 100) << "%" << white << " Time Elapsed: " << cyan << setprecision(2) << fixed << elapsedSec;
	cout << " sec\r" << flush;
	settextcolor(white);
}

//END OF UTILITY

/*
Parses a music info string and return a music object from it
@param music Music Info String
@return Music Object
*/
Music parseMusicItem(string music){
	string parsed[6];
	
	string tmpToken;
	size_t pos = 0;
	string delimiter = "<SEP>";
	int column = 0;

	while ((pos = music.find(delimiter)) != string::npos) {
			tmpToken = music.substr(0, pos);
		parsed[column] = tmpToken;
		music.erase(0, pos + delimiter.length());
		column++;
	}
	tmpToken = music;
	parsed[5] = tmpToken;

	Music musicResult(parsed[0], parsed[1], parsed[2], parsed[3], parsed[4], parsed[5]);

	return musicResult;
}

/*
Reads the Text File
@param &list Linked list to store the music data lines in
@param count How many lines in the text file to process
*/
void readMatchFile(List &list, int count){
	bool verboseMode = false; //Enable Verbose Mode

	ifstream file("mxm_779k_matches.txt");
	string str;
	int internalCounter = 0;
	int progressCounter = count;
	settextcolor(white);
	if (count > musicInfoFileLength){
		cout << "Lines to read specified exceeds lines in file. Defaulting to read all" << endl;
		count = -1;
	}
	if (count == -1){
		progressCounter = musicInfoFileLength;
		cout << "As the file is extremely large, this may take a couple of minutes..." << endl;
	}
	settextcolor(yellow);
	cout << "===============" << endl;
	cout << "Reading file..." << endl;
	cout << "===============" << endl << endl;
	clock_t beginClock = clock();
	while (getline(file, str)){
		if (internalCounter >= progressCounter)
			break;
		if (verboseMode)
			cout << str << endl; 

		//Check if string is a comment
		if (str[0] == '#'){
			//cout << "DEBUG: IS COMMENT" << endl;
		} else {
			//Parse Music Details Line
			list.add(str);
		}
		loadbar(internalCounter, progressCounter, beginClock);
		//Increment counter
		internalCounter++;
	}

	loadbar(progressCounter, progressCounter, beginClock);
	settextcolor(yellow);
	cout << endl << "Finished Reading and Adding File..." << endl;
	cout << yellow << "Total Lines Read: " << cyan << internalCounter << endl;
	cout << yellow << "Total Music List Length: " << cyan << list.getLength() << endl << endl;
}

/*
Prints out the main menu
*/
void mainMenu(){
	cout << red << "=======================" << endl;
	cout << yellow << "       Main Menu" << endl;
	cout << red << "=======================" << endl;
	settextcolor(white);
	cout << "1) " << yellow << "View Songs in Database" << white << endl;
	cout << "2) " << yellow << "Search for a song in database with name" << white << endl;
	cout << "0) " << yellow << "Quit" << white << endl;
}

/*
Prints out a song's information
@param musicData The Song Info Object
*/
void printMusicInfo(Music musicData){
	cout << white << "Million Song Track DB ID: " << blue << musicData.getTid() << endl;
	cout << white << "Million Song Track Artist: " << blue << musicData.getTArtist() << endl;
	cout << white << "Million Song Track Title: " << blue << musicData.getTTitle() << endl;
	cout << white << "musicXmatch Track DB ID: " << blue << musicData.getMid() << endl;
	cout << white << "musicXmatch Track Artist: " << blue << musicData.getMArtist() << endl;
	cout << white << "musicXmatch Track Title: " << blue << musicData.getMTitle() << endl;
}

/*
Option 2 : Search for a song
@param &list Linked List of the songs
*/
void searchSong(List &list){
	cout << red << "=========================" << endl;
	cout << yellow << "     List Songs in DB" << endl;
	cout << red << "=========================" << endl;
	string target;
	string empty;
	getline(cin, empty);
	cout << pink << "Enter Exact Song Name: " << cyan;
	getline(cin, target);
	settextcolor(white);

	for (int i = 1; i <= list.getLength(); i++){
		string res = list.get(i);
		Music musIfo = parseMusicItem(res);
		if (musIfo.getMTitle() == target){
			cout << endl << yellow << "Music Found! Details of the music file is found below:" << endl;
			printMusicInfo(musIfo);
			cout << endl;
			break;
		}
	}
}


/*
Option 1 : List of all songs currently in the linked list
@param &list Linked List of the songs
*/
void listAllSongs(List &list){
	cout << yellow << "=========================" << endl;
	cout << red << "     List Songs in DB" << endl;
	cout << yellow << "=========================" << endl;

	//cout << "ITEMS IN LIST " << endl;
	//list.print();
	//cout << "=============" << endl;
	//cout << "DEBUG SIZE: " << list.getLength() << endl;
	for (int i = 1; i <= list.getLength(); i++){
		string res = list.get(i);
		//cout << "DEBUG STR OF INDEX " << i << ": " << res << endl;
		Music musIfo = parseMusicItem(res);
		cout << yellow << "=========================================================" << endl;
		cout << red << "                 Song " << i << endl;
		cout << yellow << "=========================================================" << endl;
		printMusicInfo(musIfo);
		cout << yellow << "=========================================================" << endl;
	}
}


/*
Main Method
@return End Error Code
*/
int main(){
	//Initialization
	SetConsoleTitle(TEXT("Read File Test Project"));
	concolinit();

	List mainList;
	cout << pink << "How many lines to read? (-1 to read all): ";
	settextcolor(cyan);
	int count;
	cin >> count;
	readMatchFile(mainList, count);

	if (mainList.getLength() == 0){
		settextcolor(red);
		cout << "As Database do not have any music item, the program will quit." << endl;
		return 0;
	}

	//Main Menu
	while (true) {
		mainMenu();
		string selection;
		cout << pink << "Select a selection: ";
		settextcolor(cyan);
		cin >> selection;
		settextcolor(white);
		if (is_number(selection)){
			switch (stoi(selection))
			{
			case 1: listAllSongs(mainList); break;
			case 2: searchSong(mainList); break;
			case 0: return 0;
				//case 4: mainList.print(); break;
			default: cout << dark_red << "Invalid Selection." << endl; break;
			}
		}
		else {
			cout << dark_red << "Selection must be an integer" << endl;
		}
	}
	return 0;
}