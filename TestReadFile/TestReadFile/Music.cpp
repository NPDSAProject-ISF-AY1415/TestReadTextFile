#include "Music.h"
using namespace std;
using namespace eku;

Music::Music(string id, string art, string title, string mid, string mart, string mtitl){
	tid = id;
	tArtist = art;
	tTitle = title;
	mxmid = mid;
	mArtist = mart;
	mTitle = mtitl;
}
void Music::setTid(string id){ tid = id; }
string Music::getTid(){ return tid; }
void Music::setTArtist(string art){ tArtist = art; }
string Music::getTArtist(){ return tArtist; }
void Music::setTTitle(string title){ tTitle = title; }
string Music::getTTitle(){ return tTitle; }
void Music::setMid(string mid){ mxmid = mid; }
string Music::getMid(){ return mxmid; }
void Music::setMArtist(string mart){ mArtist = mart; }
string Music::getMArtist(){ return mArtist; }
void Music::setMTitle(string mtitl){ mTitle = mtitl; }
string Music::getMTitle(){ return mTitle; }

/*
Prints out a song's information
*/
void Music::printMusicInfo(){
	cout << white << "Million Song Track DB ID: " << blue << tid << endl;
	cout << white << "Million Song Track Artist: " << blue << tArtist << endl;
	cout << white << "Million Song Track Title: " << blue << tTitle << endl;
	cout << white << "musicXmatch Track DB ID: " << blue << mxmid << endl;
	cout << white << "musicXmatch Track Artist: " << blue << mArtist << endl;
	cout << white << "musicXmatch Track Title: " << blue << mTitle << endl;
}