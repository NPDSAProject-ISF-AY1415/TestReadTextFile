#include "PtrArr.h"

using namespace std;
using namespace eku;
using namespace utility;

namespace ptrarr {
	int musicInfoFileLength = 779074;
	//All the counters
	double addMElapsed = 0, addWElapsed = 0, addLElapsed = 0, displayMElapsed = 0, displayWElapsed = 0, sequSearchElapsed = 0;
	double removeElapsed = 0;

	/*
	Color Legend
	Yellow - Progress Bar/Status Message
	Pink - Input Message
	Cyan - Input/Numbers
	White - Progress Message
	Blue - String Message
	Red - Title
	*/

	//START OF UTILITY

	/* An Inline Progress Bar
	@param x Current Index
	@param n Total Number of Progress
	@param w Width of the bar
	@param beginClock Start of elapsed time
	*/
	static inline void loadbar(unsigned int x, unsigned int n, clock_t beginClock, unsigned int w )
	{
		if ((x != n) && (x % (n / 100 + 1) != 0) && n >= 2000) return;

		//Get Elapsed Time
		clock_t endClock = clock();
		double elapsedSec = calculateElapsed(beginClock, endClock);

		float ratio = x / (float)n;
		int   c = ratio * w;

		cout << setw(3) << white << "Parsed: " << cyan << x << white << "/" << green << n << yellow << " [" << red;
		for (int x = 0; x < c; x++) cout << "=";
		for (int x = c; x < w; x++) cout << " ";
		cout << yellow << "] " << (int)(ratio * 100) << "%" << white << " Time Elapsed: " << cyan << setprecision(2) << fixed << elapsedSec;
		cout << " sec\r" << flush;
		settextcolor(white);
	}

	/*
	Parsing each Lyric String File
	@param lyricStr String of the Lyric
	@return Created Lyric File
	*/
	Lyric parseLyricData(string lyricStr){
		istringstream lyrStream(lyricStr);
		string token;
		int ct = 0;	//0 - Track ID, 1 - MusicXMatch ID, >2 Word Count
		Lyric l;
		while (getline(lyrStream, token, ',')){
			if (ct == 0){
				l.setTrackID(token);
				ct++;
			}
			else if (ct == 1){
				l.setMusicXMatchID(token);
				ct++;
			}

			//Parse Words
			l.addWordAndCount(token);
		}

		return l;
	}

	//END OF UTILITY


	/*
	Method that calls the other file parsing methods
	@param musInfoList List for Music Information
	@param wordList List for Top Words in Lyrics
	@param lyricList List for lyrics in Songs
	*/
	void parseFiles(List &musInfoList, List &wordList, List &lyricList){
		cout << pink << "How many lines to read in Music File? (-1 to read all): ";
		settextcolor(cyan);
		int count;
		cin >> count;
		printSeperator();
		cout << red << "                             Parsing Text Files..." << endl;
		printSeperator();
		readMatchFile(musInfoList, count);
		readTopWords(wordList);
		cout << pink << "How many lines to read in Lyric Count File? (-1 to read all): ";
		settextcolor(cyan);
		cin >> count;
		readSongLyricCount(lyricList, count);
		printSeperator();
		cout << red << "                                Parse Completed" << endl;
		printSeperator();
		cout << endl;
	}

	/*
	Reads the dataset train Text File for top words
	@param &list Linked list to store the music data lines in
	*/
	void readTopWords(List &list){
		bool verboseMode = false; //Enable Verbose Mode

		ifstream file("mxm_dataset_train.txt");
		string str;
		int internalCounter = 0;
		int progressCounter = 5000;	//Hardcoded
		printSeperator();
		//cout << red << "                        Reading and Parsing file..." << endl;
		cout << red << "                          Parsing Songs Lyrics..." << endl;
		printSeperator();
		clock_t beginClock = clock();
		while (getline(file, str)){

			//Skip Comments
			if (str[0] == '#') continue;

			//Check if its top words
			if (str[0] == '%'){
				//Parse Top words based on comma
				str.erase(0,1);
				istringstream ss(str);
				string topwrd;
				while (getline(ss, topwrd, ',')){
					if (verboseMode)
						cout << topwrd << endl;

					list.add(topwrd);
					loadbar(internalCounter, progressCounter, beginClock);
					//Increment counter
					internalCounter++;
				}
				break;
			}
		}

		loadbar(progressCounter, progressCounter, beginClock);
		clock_t finalEndClock = clock();

		settextcolor(yellow);
		addWElapsed = calculateElapsed(beginClock, finalEndClock);
		cout << endl << "Finished Parsing Song Lyrics." << endl;
		cout << yellow << "Elapsed Time to add: " << cyan << setprecision(2) << fixed << addWElapsed << " seconds" << endl;
		cout << yellow << "Total Words Read: " << cyan << internalCounter << endl;
		cout << yellow << "Total Word List Length: " << cyan << list.getLength() << endl << endl;
	}

	/*
	Reads the dataset train Text File for song lyrics count
	@param &list Linked list to store the music data lines in
	*/
	void readSongLyricCount(List &list, int count){
		bool verboseMode = false; //Enable Verbose Mode

		ifstream file("mxm_dataset_train.txt");
		string str;
		int internalCounter = 0;
		int fullCounter = 210519;		//Hardcoded
		int progressCounter = count;	//Hardcoded

		settextcolor(white);
		if (count > musicInfoFileLength){
			cout << "Lines to read specified exceeds lines in file. Defaulting to read all" << endl;
			count = -1;
		}
		if (count == -1){
			progressCounter = fullCounter;
			cout << "As the file is extremely large, this may take a couple of minutes..." << endl;
		}
		settextcolor(yellow);

		printSeperator();
		//cout << red << "                        Reading and Parsing file..." << endl;
		cout << red << "                       Parsing Songs Lyrics Count..." << endl;
		printSeperator();
		clock_t beginClock = clock();
		while (getline(file, str)){

			//Skip Comments
			if (str[0] == '#' || str[0] == '%') continue;

			else{
				if (internalCounter >= progressCounter) break;

				list.add(str);
				loadbar(internalCounter, progressCounter, beginClock);
				//Increment counter
				internalCounter++;
			}
		}

		loadbar(progressCounter, progressCounter, beginClock);
		clock_t finalEndClock = clock();

		settextcolor(yellow);
		addLElapsed = calculateElapsed(beginClock, finalEndClock);
		cout << endl << "Finished Parsing Song Lyrics Count." << endl;
		cout << yellow << "Elapsed Time to add: " << cyan << setprecision(2) << fixed << addLElapsed << " seconds" << endl;
		cout << yellow << "Total Lyric Lines Read: " << cyan << internalCounter << endl;
		cout << yellow << "Total Lyric List Length: " << cyan << list.getLength() << endl << endl;
	}

	/*
	Reads the 779k Match Text File
	@param &list Linked list to store the music data lines in
	@param count How many lines in the text file to process
	*/
	void readMatchFile(List &list, int count){
		bool verboseMode = false; //Enable Verbose Mode

		ifstream file("mxm_779k_matches.txt");
		string str;
		int internalCounter = 0;
		int progressCounter = count;
		settextcolor(white);
		if (count > musicInfoFileLength){
			cout << "Lines to read specified exceeds lines in file. Defaulting to read all" << endl;
			count = -1;
		}
		if (count == -1){
			progressCounter = musicInfoFileLength;
			cout << "As the file is extremely large, this may take a couple of minutes..." << endl;
		}
		settextcolor(yellow);
		printSeperator();
		cout << red << "                          Parsing Song Information..." << endl;
		printSeperator();
		clock_t beginClock = clock();
		while (getline(file, str)){
			if (internalCounter >= progressCounter)
				break;
			if (verboseMode)
				cout << str << endl;

			//Check if string is a comment
			if (str[0] == '#'){
				//cout << "DEBUG: IS COMMENT" << endl;
			}
			else {
				//Parse Music Details Line
				list.add(str);
			}
			loadbar(internalCounter, progressCounter, beginClock);
			//Increment counter
			internalCounter++;
		}

		loadbar(progressCounter, progressCounter, beginClock);
		clock_t finalEndClock = clock();

		settextcolor(yellow);
		addMElapsed = calculateElapsed(beginClock, finalEndClock);
		cout << endl << "Finished Parsing and Adding Song Information." << endl;
		cout << yellow << "Elapsed Time to add: " << cyan << setprecision(2) << fixed << addMElapsed << " seconds" << endl;
		cout << yellow << "Total Lines Read: " << cyan << internalCounter << endl;
		cout << yellow << "Total Music List Length: " << cyan << list.getLength() << endl << endl;
	}

	/*
	Prints out the main pointer-based array menu
	*/
	void mainPtrArrMenu(){
		printSeperator();
		cout << red << "                        Main Pointer-based Array Menu" << endl;
		printSeperator();
		settextcolor(white);
		cout << "1) " << yellow << "View Songs in Database" << white << endl;
		cout << "2) " << yellow << "View All the Top Words found in Lyrics" << white << endl;
		cout << "3) " << yellow << "Search for a song in database with name" << white << endl;
		cout << "4) " << yellow << "Remove a song from the database" << white << endl;
		cout << "5) " << yellow << "View Performance Statistics" << white << endl;
		cout << "9) " << yellow << "Return to Main Menu" << white << endl;
		cout << "0) " << yellow << "Quit" << white << endl;
	}

	/*
	Option 2 : Search for a song
	@param &list Linked List of the songs
	*/
	void searchSong(List &list){
		printSeperator();
		cout << yellow << "                                 Search Songs" << endl;
		printSeperator();
		string target;
		string empty;
		getline(cin, empty);
		cout << pink << "Enter Exact Song Name: " << cyan;
		getline(cin, target);
		settextcolor(white);

		clock_t start = clock();
		bool found = false;
		for (int i = 1; i <= list.getLength(); i++){
			string res = list.get(i);
			Music musIfo = parseMusicItem(res);
			if (musIfo.getMTitle() == target){
				cout << endl << yellow << "Music Found! Details of the music file is found below:" << endl;
				//printMusicInfo(musIfo);
				musIfo.printMusicInfo();
				cout << endl;
				found = true;
				break;
			}
		}
		if (!found){
			cout << endl << dark_red << "Unable to find a music file matching the search term" << endl;
		}
		clock_t end = clock();
		sequSearchElapsed = calculateElapsed(start, end);
		cout << yellow << "Elapsed Time for Sequential Search: " << cyan << setprecision(2) << fixed << sequSearchElapsed << " seconds." << endl;
	}

	/*
	Option 1 : List of all songs currently in the linked list
	@param &list Linked List of the songs
	*/
	void listAllSongs(List &list){
		printSeperator();
		cout << red << "                                List All Songs" << endl;
		printSeperator();

		clock_t start = clock();
		for (int i = 1; i <= list.getLength(); i++){
			string res = list.get(i);
			Music musIfo = parseMusicItem(res);
			cout << yellow << "=========================================================" << endl;
			cout << red << "                 Song " << i << endl;
			cout << yellow << "=========================================================" << endl;
			musIfo.printMusicInfo();
			cout << yellow << "=========================================================" << endl;
		}
		clock_t end = clock();
		displayMElapsed = calculateElapsed(start, end);
		cout << yellow << "Elapsed Time for displaying songs: " << cyan << setprecision(2) << fixed << displayMElapsed << " seconds." << endl;
	}

	/* Option 4: Display List of Top Words in Lyrics 
	@param list List of Top Words
	*/
	void listTopWords(List &list){
		printSeperator();
		cout << red << "                           List Top Words in Lyrics" << endl;
		printSeperator();
		int modder = 1;		//To split print every 6 lines

		clock_t start = clock();
		for (int i = 1; i <= list.getLength(); i++){
			if (modder % 6 == 0){
				cout << endl;
				modder = 1;
			}
			string wordString = list.get(i);
			cout << "  " << white << wordString << yellow << "  |";
			modder++;
		}
		cout << endl;
		clock_t end = clock();
		displayWElapsed = calculateElapsed(start, end);
		cout << yellow << "Elapsed Time for displaying top words in lyrics: " << cyan << setprecision(2) << fixed << displayWElapsed << " seconds." << endl;
	}

	/*
	Option 5: Remove an item from the music file
	@param list List of Music File
	*/
	void removeMusicInfo(List &list){
		printSeperator();
		cout << red << "                              Remove Music Data" << endl;
		printSeperator();
		int size = list.getLength();
		string indexToRemove;
		cout << pink << "Enter index to remove (1 - " << size << "): ";
		getStringInput(indexToRemove);

		//Validation
		if (!is_number(indexToRemove)){
			cout << dark_red << "Please enter a positive number as the index" << white << endl;
			return;
		}
		if (stoi(indexToRemove) > size){
			cout << dark_red << "Entered Value is higher than the total size in the list" << white << endl;
			return;
		}

		Music toRemove = parseMusicItem(list.get(stoi(indexToRemove)));
		cout << red << "Are you sure you wish to remove the following music data from the list? " << endl;
		toRemove.printMusicInfo();
		cout << red << "To remove, Enter y or Y (default N): ";
		string confirm; 
		getStringInput(confirm);			//Check if user confirm
		cout << endl;
		if (confirm[0] == 'y' || confirm[0] == 'Y'){
			//Confirmed Remove
			clock_t start = clock();
			list.remove(stoi(indexToRemove));
			cout << green << "Music Data (" << toRemove.getMTitle() << ") has been removed from the list!" << endl;
			clock_t end = clock();
			removeElapsed = calculateElapsed(start, end);
			cout << yellow << "Elapsed Time for removing music: " << cyan << setprecision(2) << fixed << removeElapsed << " seconds." << endl;
		}
		else {
			cout << green << "Cancelled Removal of Music Data from list" << endl;
		}
	}

	/*
	Option 3 : Prints out the statistics (timing/mem usage) of list
	*/
	void printStats(){
		printSeperator();
		cout << red << "                         Pointer-based Array Statistics" << endl;
		printSeperator();
		//Add Music
		cout << red << " " << "              Add (Music)              " << yellow << "|" << red << "        " << cyan;
		if (addMElapsed != 0)
			cout << setprecision(2) << fixed << addMElapsed << " Seconds ";
		else
			cout << "  Untested ";
		cout << endl;

		//Add Music
		cout << red << " " << "              Add (Words)              " << yellow << "|" << red << "        " << cyan;
		if (addWElapsed != 0)
			cout << setprecision(2) << fixed << addWElapsed << " Seconds ";
		else
			cout << "  Untested ";
		cout << endl;

		//Add Lyric
		cout << red << " " << "              Add (Lyric)              " << yellow << "|" << red << "        " << cyan;
		if (addLElapsed != 0)
			cout << setprecision(2) << fixed << addLElapsed << " Seconds ";
		else
			cout << "  Untested ";
		cout << endl;

		//Display Music
		cout << " " << red << "            Display (Music)            " << yellow << "|" << red << "        " << cyan;
		if (displayMElapsed != 0)
			cout << setprecision(2) << fixed << displayMElapsed << " Seconds ";
		else
			cout << "  Untested ";
		cout << endl;

		//Display Top Words
		cout << " " << red << "          Display (Top Words)          " << yellow << "|" << red << "        " << cyan;
		if (displayWElapsed != 0)
			cout << setprecision(2) << fixed << displayWElapsed << " Seconds ";
		else
			cout << "  Untested ";
		cout << endl;

		//Remove
		cout << " " << red << "              Remove Item              " << yellow << "|" << red << "        " << cyan;
		if (removeElapsed != 0)
			cout << setprecision(2) << fixed << removeElapsed << " Seconds ";
		else
			cout << "  Untested ";
		cout << endl;

		//Seq Search
		cout << " " << red << "           Sequential Search           " << yellow << "|" << red << "        " << cyan;
		if (sequSearchElapsed != 0)
			cout << setprecision(2) << fixed << sequSearchElapsed << " Seconds ";
		else
			cout << "  Untested ";
		cout << endl;

		printSeperator();
	}

	/*
	Main Pointer Based Array Code
	@return Error Code (-1 for continue)
	*/
	int mainLoop(){
		List mainMusicList, mainWordList, mainLyricList;
		parseFiles(mainMusicList, mainWordList, mainLyricList);

		if (mainMusicList.getLength() == 0){
			settextcolor(red);
			cout << "As Database do not have any music item, this section will quit." << endl;
			return -1;
		}

		//Main Menu
		while (true) {
			mainPtrArrMenu();
			string selection;
			cout << pink << "Select an option: ";
			getStringInput(selection);
			if (is_number(selection)){
				switch (stoi(selection))
				{
				case 1: listAllSongs(mainMusicList); break;
				case 2: listTopWords(mainWordList); break;
				case 3: searchSong(mainMusicList); break;
				case 4: removeMusicInfo(mainMusicList); break;
				case 5: printStats(); break;
				case 9: return -1;
				case 0: return 0;
					//case 4: mainList.print(); break;
				default: cout << dark_red << "Invalid Selection." << endl; break;
				}
			}
			else {
				cout << dark_red << "Selection must be an integer" << endl;
			}
		}
		return 0;
	}
}
