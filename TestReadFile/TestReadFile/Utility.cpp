#include "Utility.h"

using namespace std;
using namespace eku;

namespace utility {

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

	/*
	Prints the seperator (===) (78 chars)
	*/
	void printSeperator(){
		cout << yellow << "===============================================================================" << white << endl;
	}

	/*
	Calculate Elapsed Time in Seconds
	@param start Start of the clock
	@param end The time where it is clocked
	@return Elapsed time in seconds
	*/
	double calculateElapsed(clock_t start, clock_t end){
		return double(end - start) / CLOCKS_PER_SEC;
	}

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
	Print ASCII Art
	*/
	void printAscii(){
		ifstream file("ascii.txt");
		string print;
		while (getline(file, print)){
			cout << print << endl;
		}
	}

}