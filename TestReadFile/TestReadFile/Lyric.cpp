#include "Lyric.h"

using namespace std;

Lyric::Lyric(){}
Lyric::Lyric(string trackid, string mxmatchid){
	this->tid = trackid;
	this->mxmid = mxmatchid;
}
string Lyric::getTrackID(){ return this->tid; }
void Lyric::setTrackID(string trackid){ this->tid = trackid; }
string Lyric::getMusicXMatchID(){ return this->mxmid; }
void Lyric::setMusicXMatchID(string mxmatchid){ this->mxmid = mxmatchid; }
void Lyric::addWordAndCount(string word){
	istringstream wc(word);
	string token;
	bool isWord = true;
	while (getline(wc, token, ':')){
		//First will be word based on word list, second will be count
		if (isWord){
			this->word.add(token);
			isWord = false;
		}
		else {
			this->count.add(token);
			break;
		}
	}
}
string Lyric::getWordCount(){
	return "...";
}