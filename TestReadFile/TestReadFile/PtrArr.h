#ifndef UNSORT_PTR_ARR
#define UNSORT_PTR_ARR

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
#include <vector>		//Vector
#define CONSOLE_WINDOW_SIZE 78
#define SONG_FILE_LENGTH 779088
#define LYRIC_FILE_LENGTH 210519
#define WORD_LENGTH 5000

namespace ptrarr {
	extern int musicInfoFileLength;
	extern double addMElapsed, addWElapsed, addLElapsed, displayMElapsed, displayWElapsed, sequSearchElapsed;
	extern double removeElapsed;

	extern SIZE_T addMVTime, addWVTime, addLVTime, displayMVTime, displayWVTime, sequSearchVTime, removeVTime;
	extern SIZE_T addMPTime, addWPTime, addLPTime, displayMPTime, displayWPTime, sequSearchPTime, removePTime;

	extern vector<double> timingAddMCounter;
	extern vector<double> timingAddLCounter;
	extern vector<double> timingAddWCounter;
	extern vector<double> timingDisplayMCounter;
	extern vector<double> timingSeqSearchMCounter;
	extern vector<double> timingRemoveMCounter;
	extern vector<double> timingDisplayWCounter;
	extern vector<double> memoryPAddMCounter;
	extern vector<double> memoryPAddLCounter;
	extern vector<double> memoryPAddWCounter;
	extern vector<double> memoryPDisplayMCounter;
	extern vector<double> memoryPSeqSearchMCounter;
	extern vector<double> memoryPRemoveMCounter;
	extern vector<double> memoryPDisplayWCounter;
	extern vector<double> memoryVAddMCounter;
	extern vector<double> memoryVAddLCounter;
	extern vector<double> memoryVAddWCounter;
	extern vector<double> memoryVDisplayMCounter;
	extern vector<double> memoryVSeqSearchMCounter;
	extern vector<double> memoryVRemoveMCounter;
	extern vector<double> memoryVDisplayWCounter;

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
	void makeAddTimeGraph();
	void makeDisplayTimeGraph();
	void makeRemoveTimeGraph();
	void makeSeqSearchTimeGraph();
	void plotGraphMenu();
	int mainLoop();
}

#endif