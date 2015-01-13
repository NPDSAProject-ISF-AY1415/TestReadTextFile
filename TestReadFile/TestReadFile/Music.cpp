#include "Music.h"
using namespace std;
using namespace eku;

Music::Music(string id, string art, string title, string mid, string mart, string mtitl){
	this->tid = id;
	this->tArtist = art;
	this->tTitle = title;
	this->mxmid = mid;
	this->mArtist = mart;
	this->mTitle = mtitl;
}
void Music::setTid(string id){ this->tid = id; }
string Music::getTid(){ return this->tid; }
void Music::setTArtist(string art){ this->tArtist = art; }
string Music::getTArtist(){ return this->tArtist; }
void Music::setTTitle(string title){ this->tTitle = title; }
string Music::getTTitle(){ return this->tTitle; }
void Music::setMid(string mid){ this->mxmid = mid; }
string Music::getMid(){ return this->mxmid; }
void Music::setMArtist(string mart){ this->mArtist = mart; }
string Music::getMArtist(){ return this->mArtist; }
void Music::setMTitle(string mtitl){ this->mTitle = mtitl; }
string Music::getMTitle(){ return this->mTitle; }

/*
Prints out a song's information
*/
void Music::printMusicInfo(){
	cout << white << "Million Song Track DB ID: " << blue << this->tid << endl;
	cout << white << "Million Song Track Artist: " << blue << this->tArtist << endl;
	cout << white << "Million Song Track Title: " << blue << this->tTitle << endl;
	cout << white << "musicXmatch Track DB ID: " << blue << this->mxmid << endl;
	cout << white << "musicXmatch Track Artist: " << blue << this->mArtist << endl;
	cout << white << "musicXmatch Track Title: " << blue << this->mTitle << endl;
}