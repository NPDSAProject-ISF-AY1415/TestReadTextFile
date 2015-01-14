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
#include <iomanip>		//std::setw
#include <sstream>		//String Stream

namespace ptrarr {
	extern int musicInfoFileLength;
	extern double addMElapsed, addWElapsed, addLElapsed, displayMElapsed, displayWElapsed, sequSearchElapsed;
	extern double removeElapsed;
	static inline void loadbar(unsigned int x, unsigned int n, clock_t beginClock, unsigned int w = 25);
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
	void makeGraph(List &musicList, List &wordList, List &lyricList);
	int mainLoop();
}