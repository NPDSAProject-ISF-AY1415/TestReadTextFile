#include "Graph.h"

using namespace std;


//Y Values
//0 - Add, 1 - Remove, 2-Display, 3-Sequential Search, 4-Binary Search


Graph::Graph(string title, double add, double remove, double display, double seqSearch, double binSearch){
	this->title = title;
	this->yValues[0] = add;
	this->yValues[1] = remove;
	this->yValues[2] = display;
	this->yValues[3] = seqSearch;
	this->yValues[4] = binSearch;
}
void Graph::setTitle(string title){ this->title = title; }
string Graph::getTitle(){ return this->title; }
void Graph::setValues(double add, double remove, double display, double seqSearch, double binSearch){
	this->yValues[0] = add;
	this->yValues[1] = remove;
	this->yValues[2] = display;
	this->yValues[3] = seqSearch;
	this->yValues[4] = binSearch;
}

double* Graph::getValues(){
	return this->yValues;
}

void Graph::printValues(){
	cout << "Title of Graph: " << this->title << endl;
	for (int i = 0; i < 5; i++){
		cout << this->yValues[i] << " : ";
	}
	cout << endl;
}
string Graph::createGraphString(){
	//Format: title,y0,y1,y2,y3,y4,y5
	ostringstream s;
	string createdStr;
	if (this->title != "")
		s << this->title;
	else
		s << "NULL";
	s << "," << this->yValues[0] << "," << this->yValues[1] << "," << this->yValues[2] << "," << this->yValues[3] << "," << this->yValues[4];
	return s.str();
}

Graph Graph::createGraphObjFromString(string str){
	istringstream stream(str);
	string token;
	int tokenCt = 0;

	//Temp Var
	string title;
	double add, del, dis, ss, bs;
	while (getline(stream, token, ',')){
		switch (tokenCt)
		{
		case 0: title = token;  break;
		case 1: add = stod(token); break;
		case 2: del = stod(token); break;
		case 3: dis = stod(token); break;
		case 4: ss = stod(token); break;
		case 5: bs = stod(token); break;
		}
		tokenCt++;
	}

	Graph newG(title, add, del, dis, ss, bs);
	return newG;
}