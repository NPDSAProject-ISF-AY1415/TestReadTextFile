#ifndef GRAPH_DATA
#define GRAPH_DATA

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Graph{
private:
	string title;		//Title of the Graph (Includes the name)
	vector<double> yValues;	//Timings/Mem Usage
	vector<double> xValues;	//n of items
public:
	Graph(string title, vector<double> x, vector<double> y);
	Graph(string title, int xCt, vector<double> y);
	void setTitle(string title);
	string getTitle();
	void setValues(vector<double> x, vector<double> y);
	void addValues(double x, double y);
	vector<double> getXValueArr();
	vector<double> getYValueArr();
	double getXValue(int index);
	double getYValue(int index);
	void printValues();
	string createGraphString();
	static Graph createGraphObjFromString(string str);
};

#endif