#ifndef GRAPH_DATA
#define GRAPH_DATA

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Graph{
private:
	string title;		//Title of the Graph (Includes the name)
	double yValues[5];	//Timing of the stuff
public:
	Graph(string title, double add, double remove, double display, double seqSearch, double binSearch);
	void setTitle(string title);
	string getTitle();
	void setValues(double add, double remove, double display, double seqSearch, double binSearch);
	double* getValues();
	void printValues();
	string createGraphString();
	static Graph createGraphObjFromString(string str);
};

#endif