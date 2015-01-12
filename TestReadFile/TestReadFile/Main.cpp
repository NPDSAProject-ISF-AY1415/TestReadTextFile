#include <iostream>
#include <fstream>
#include "List.h"
#include "Music.h"

using namespace std;

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
	ifstream file("mxm_779k_matches.txt");
	string str;
	int internalCounter = 0;
	cout << "===============" << endl;
	cout << "Reading file..." << endl;
	cout << "===============" << endl << endl;
	while (getline(file, str)){
		if (internalCounter >= count)
			break;
		cout << str << endl; 

		//Check if string is a comment
		if (str[0] == '#'){
			//cout << "DEBUG: IS COMMENT" << endl;
		} else {
			//Parse Music Details Line
			list.add(str);
		}

		//Increment counter
		internalCounter++;
	}

	cout << endl << "Finished Reading and Adding File..." << endl;
	cout << "Total Music List Length: " << list.getLength() << endl << endl;
}

/*
Prints out the main menu
*/
void mainMenu(){
	cout << "=======================" << endl;
	cout << "       Main Menu" << endl;
	cout << "=======================" << endl;
	cout << "1) View Songs in Database" << endl;
	cout << "2) Search for a song in database with name" << endl;
	cout << "0) Quit" << endl;
}

/*
Prints out a song's information
@param musicData The Song Info Object
*/
void printMusicInfo(Music musicData){
	cout << "Million Song Track DB ID: " << musicData.getTid() << endl;
	cout << "Million Song Track Artist: " << musicData.getTArtist() << endl;
	cout << "Million Song Track Title: " << musicData.getTTitle() << endl;
	cout << "musicXmatch Track DB ID: " << musicData.getMid() << endl;
	cout << "musicXmatch Track Artist: " << musicData.getMArtist() << endl;
	cout << "musicXmatch Track Title: " << musicData.getMTitle() << endl;
}

/*
Option 2 : Search for a song
@param &list Linked List of the songs
*/
void searchSong(List &list){
	cout << "=========================" << endl;
	cout << "     List Songs in DB" << endl;
	cout << "=========================" << endl;
	string target;
	string empty;
	getline(cin, empty);
	cout << "Enter Exact Song Name: ";
	getline(cin, target);

	for (int i = 1; i <= list.getLength(); i++){
		string res = list.get(i);
		Music musIfo = parseMusicItem(res);
		if (musIfo.getMTitle() == target){
			cout << endl << "Music Found! Details of the music file is found below:" << endl;
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
	cout << "=========================" << endl;
	cout << "     List Songs in DB" << endl;
	cout << "=========================" << endl;

	//cout << "ITEMS IN LIST " << endl;
	//list.print();
	//cout << "=============" << endl;
	//cout << "DEBUG SIZE: " << list.getLength() << endl;
	for (int i = 1; i <= list.getLength(); i++){
		string res = list.get(i);
		//cout << "DEBUG STR OF INDEX " << i << ": " << res << endl;
		Music musIfo = parseMusicItem(res);
		cout << "=========================================================" << endl;
		cout << "                 Song " << i << endl;
		cout << "=========================================================" << endl;
		printMusicInfo(musIfo);
		cout << "=========================================================" << endl;
	}
}


/*
Main Method
@return End Error Code
*/
int main(){
	List mainList;
	cout << "How many lines to read?: ";
	int count;
	cin >> count;
	readMatchFile(mainList, count);

	if (mainList.getLength() == 0){
		cout << "As Database do not have any music item, the program will quit." << endl;
		return 0;
	}

	//Main Menu
	while (true) {
		mainMenu();
		int selection;
		cin >> selection;
		switch (selection)
		{
		case 1: listAllSongs(mainList); break;
		case 2: searchSong(mainList); break;
		case 0: return 0;
		//case 4: mainList.print(); break;
		default: cout << "Invalid Selection." << endl; break;
		}
	}
	return 0;
}