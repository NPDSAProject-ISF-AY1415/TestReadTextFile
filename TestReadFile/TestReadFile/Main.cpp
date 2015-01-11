#include <iostream>
#include <fstream>
#include "List.h"
#include "Music.h"

using namespace std;

string* parseMusicItem(string music, int columnIndex){
	string parsed[6];
	
	string tmpToken;
	size_t pos = 0;
	string delimiter = "<SEP>";
	int column = 0;

	while (pos = music.find(delimiter) != string::npos) {
		tmpToken = music.substr(0, pos);
		parsed[column] = tmpToken;
		music.erase(0, pos + delimiter.length());
		column++;
	}

	return parsed;
}

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

void mainMenu(){
	cout << "=======================" << endl;
	cout << "       Main Menu" << endl;
	cout << "=======================" << endl;
	cout << "1) View Songs in Database" << endl;
	cout << "2) Search for a song in database with name" << endl;
	cout << "0) Quit" << endl;
}

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
		case 1: cout << "TODO: Future List" << endl; break;
		case 2: cout << "TODO: Future search" << endl; break;
		case 0: return 0;
		default: cout << "Invalid Selection." << endl; break;
		}
	}
	return 0;
}