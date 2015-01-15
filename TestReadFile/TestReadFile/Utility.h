#ifndef UTIL
#define UTIL

#include <algorithm>	//Find If
#include <Windows.h>	//Console Utility
#include <ctime>		//Elapsed Time
#include "concol.h"		//Console Colors
#include "Music.h"
#include <iostream>		//String
#include <fstream>		//File Reading
#include <sstream>		//String Stream

using namespace std;

namespace utility{
	bool is_number(const string& s);
	void printSeperator();
	double calculateElapsed(clock_t start, clock_t end);
	Music parseMusicItem(string music);
	void printAscii();
	void getStringInput(string &storein);
	string centerString(char* s, int size);
}
#endif