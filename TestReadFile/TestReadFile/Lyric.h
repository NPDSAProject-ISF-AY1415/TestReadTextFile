#ifndef LYRIC
#define LYRIC

#include <string>
#include <iostream>
#include "List.h"

using namespace std;

class Lyric{
private:
	string tid;
	string mxmid;
	List word;
	List count;
public:
	Lyric(string tid, string mxmid);
	string getTrackID();
	void setTrackID(string tid);
	string getMusicXMatchID();
	void setMusicXMatchID(string mxmid);
	void addWordAndCount(string word);
	void addWord(string word);
	void addCount(string count);
	string getWordCount();
};

#endif