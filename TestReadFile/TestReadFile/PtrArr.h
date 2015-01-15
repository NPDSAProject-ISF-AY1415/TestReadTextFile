#include <iostream>		//String
#include <fstream>		//File reading
#include <Windows.h>	//Console Utility
#include <ctime>		//Elapsed Time
#include "concol.h"		//Console Colors
#include "List.h"
#include "Music.h"
#include "Utility.h"
#include "Lyric.h"
#include "Graph.h"
#include "plotGraph.h"
#include "Memory.h"
#include <iomanip>		//std::setw
#include <sstream>		//String Stream
#define CONSOLE_WINDOW_SIZE 78

namespace ptrarr {
	extern int musicInfoFileLength;
	extern double addMElapsed, addWElapsed, addLElapsed, displayMElapsed, displayWElapsed, sequSearchElapsed;
	extern double removeElapsed;

	extern SIZE_T addMVTime, addWVTime, addLVTime, displayMVTime, displayWVTime, sequSearchVTime, removeVTime;
	extern SIZE_T addMPTime, addWPTime, addLPTime, displayMPTime, displayWPTime, sequSearchPTime, removePTime;

	static inline void loadbar(unsigned int x, unsigned int n, clock_t beginClock, SIZE_T beginPMem, SIZE_T beginVMem, unsigned int w = 10);
	Lyric parseLyricData(string lyricStr);
	void parseFiles(List &musInfoList, List &wordList, List &lyricList);
	void readTopWords(List &list);
	void readMatchFile(List &list, int count);
	void readSongLyricCount(List &list, int count);
	void mainPtrArrMenu();
	void searchSong(List &list);
	void listAllSongs(List &list);
	void listTopWords(List &list);
	void removeMusicInfo(List &list);
	void printStats();
	void makeGraph();
	int mainLoop();
}