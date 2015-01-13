#include <iostream>		//String
#include <fstream>		//File reading
#include <Windows.h>	//Console Utility
#include <ctime>		//Elapsed Time
#include "concol.h"		//Console Colors
#include "List.h"
#include "Music.h"
#include "Utility.h"
#include <iomanip>		//std::setw

namespace ptrarr {
	extern int musicInfoFileLength;
	extern double addElapsed, displayElapsed, sequSearchElapsed;
	static inline void loadbar(unsigned int x, unsigned int n, clock_t beginClock, unsigned int w = 25);
	void readMatchFile(List &list, int count);
	void mainPtrArrMenu();
	void searchSong(List &list);
	void listAllSongs(List &list);
	void printStats();
	int mainLoop();
}