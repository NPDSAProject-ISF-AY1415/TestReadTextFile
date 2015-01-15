#include "Graph.h"

using namespace std;


//Y Values
//0 - Add, 1 - Remove, 2-Display, 3-Sequential Search, 4-Binary Search


Graph::Graph(string title, vector<double> x, vector<double> y){
	this->title = title;
	this->xValues = x;
	this->yValues = y;
}

Graph::Graph(string title, int xCt, vector<double> y){
	this->title = title;
	this->yValues = y;
	this->xValues.resize(xCt);
	for (int i = 0; i < this->xValues.size(); i++){
		this->xValues[i] = (i + 1);
	}
}

void Graph::setTitle(string title){ this->title = title; }
string Graph::getTitle(){ return this->title; }
void Graph::setValues(vector<double> x, vector<double> y){
	this->xValues = x;
	this->yValues = y;
}

void Graph::addValues(double x, double y){
	int newSize = this->xValues.size() + 1;
	this->xValues.resize(newSize);
	this->xValues.resize(newSize);
	this->xValues[newSize - 1] = x;
	this->yValues[newSize - 1] = y;
}

vector<double> Graph::getXValueArr(){
	return this->xValues;
}

vector<double> Graph::getYValueArr(){
	return this->yValues;
}

double Graph::getXValue(int index){
	return this->xValues[index];
}

double Graph::getYValue(int index){
	return this->yValues[index];
}

void Graph::printValues(){
	cout << "Title of Graph: " << this->title << endl;
	for (int i = 0; i < 5; i++){
		cout << this->yValues[i] << " : ";
	}
	cout << endl;
}
string Graph::createGraphString(){
	//Format: title,len,x0:y0,x1:y1,....
	ostringstream s;
	string createdStr;
	if (this->title != "")
		s << this->title;
	else
		s << "NULL";
	s << "," << this->xValues.size();
	for (int i = 0; i < this->xValues.size(); i++)
		s << "," << this->xValues[i] << ":" << this->yValues[i];

	//cout << "DEBUG: " << s.str() << endl;
	return s.str();
}

Graph Graph::createGraphObjFromString(string str){
	istringstream stream(str);
	string token;
	int tokenCt = 0;
	
	//cout << "String: " << str << endl;
	//Temp Var
	string title;
	vector<double> x;
	vector<double> y;
	int counter = 0;
	while (getline(stream, token, ',')){
		if (tokenCt == 0)
			title = token;
		else if (tokenCt == 1){
			//Set Lengths of Array
			x.resize(stoi(token));
			y.resize(stoi(token));
		}
		else {
			//Add Values (Split into :)
			stringstream subStr(token);
			string xAndY;
			bool first = true;
			while (getline(subStr, xAndY, ':')){
				if (first){
					first = false;
					x[counter] = stod(xAndY);
				}
				else {
					y[counter] = stod(xAndY);
				}
			}
			//cout << "LEL: " << x[counter] << ":" << y[counter] << ", ";
			counter++;
		}
		tokenCt++;
	}

	Graph newG(title, x, y);
	return newG;
}