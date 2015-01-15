#include "plotGraph.h"

//Command is something that goes
//"plot <data> title <title>[, <2nd data> title <2nd title>,]..."

using namespace eku;

//DEPRECRATED
int plotGraph(List &graphList){
	FILE * gnuplotPipe = _popen("gnuplot -persistent", "w");
	fprintf(gnuplotPipe, "set title \"Performance Graphs\" \n");
	//Set The Display, Add, Remove, Binary Search, Sequential Search
	//fprintf(gnuplotPipe, "set xtics offset character 0,0,0 norangelimit (\"Add\" 1, \"Remove\" 2, \"Display\" 3, \"Binary Search\" 4, \"Sequential Search\" 5) \n");
	bool first_line = true;
	for (int j = 1; j <= graphList.getLength(); j++){
		string graphString = graphList.get(j);
		Graph g = Graph::createGraphObjFromString(graphString);
		if (first_line)
			fprintf(gnuplotPipe, "plot '-' t \"");
		else
			fprintf(gnuplotPipe, "'-' t \"");
		first_line = false;
		fprintf(gnuplotPipe, g.getTitle().c_str());
		fprintf(gnuplotPipe, "\" w linesp,");
	}
	fprintf(gnuplotPipe, "\n");
	for (int j = 1; j <= graphList.getLength(); j++){
		string graphString = graphList.get(j);
		//cout << graphString << endl;
		Graph g = Graph::createGraphObjFromString(graphString);
		//cout << g.getValues(1) << "lol" << endl; 
		for (int k = 0; k < g.getXValueArr().size(); k++)
		{
			vector<double> yVals = g.getYValueArr();
			vector<double> xVals = g.getXValueArr();
			//fprintf(gnuplotPipe, "%lf %lf \n", xVals[i], yVals[i]);
			//cout << k+1 << " : " << yVals[k] << " ";
			fprintf(gnuplotPipe, "%ld %lf \n", xVals[k], yVals[k]);
		}
		fprintf(gnuplotPipe, "e\n");
	}
	fflush(gnuplotPipe);
	cout << red << "Please ensure that you have closed the graph before continuing! Press any key to continue" << endl;
	cin.get();
	cin.get();
	return 0;
}

int plotGraph(List &graphList, string title){
	FILE * gnuplotPipe = _popen("gnuplot -persistent", "w");
	string titleStr = "set title \"" + title + "\" \n";
	fprintf(gnuplotPipe, titleStr.c_str());
	//Set The Display, Add, Remove, Binary Search, Sequential Search
	//fprintf(gnuplotPipe, "set xtics offset character 0,0,0 norangelimit (\"Add\" 1, \"Remove\" 2, \"Display\" 3, \"Binary Search\" 4, \"Sequential Search\" 5) \n");
	bool first_line = true;
	for (int j = 1; j <= graphList.getLength(); j++){
		string graphString = graphList.get(j);
		Graph g = Graph::createGraphObjFromString(graphString);
		if (first_line)
			fprintf(gnuplotPipe, "plot '-' t \"");
		else
			fprintf(gnuplotPipe, "'-' t \"");
		first_line = false;
		fprintf(gnuplotPipe, g.getTitle().c_str());
		fprintf(gnuplotPipe, "\" w linesp,");
	}
	fprintf(gnuplotPipe, "\n");
	for (int j = 1; j <= graphList.getLength(); j++){
		string graphString = graphList.get(j);
		//cout << graphString << endl;
		//cout << "String created: " << graphString << endl << endl;
		Graph g = Graph::createGraphObjFromString(graphString);
		//cout << g.getValues(1) << "lol" << endl; 
		for (int k = 0; k < g.getXValueArr().size(); k++)
		{
			vector<double> yVals = g.getYValueArr();
			vector<double> xVals = g.getXValueArr();
			//Case 1: Size of Arr more than 1000
			if (g.getXValueArr().size() > 1000){
				//If > arrSize - 10, all
				//> 1000, %10
				//>100, %50
				//%100
				if (k > (g.getXValueArr().size() - 10)){}
				else if (k > 1000 && (k % 10 != 0)) continue;
				else if (k > 100 && (k % 50 != 0)) continue;
				else if (k % 100 != 0) continue;
			}

			//Case 2: Size of Arr Less than 1000 but more than 100
			else if (g.getXValueArr().size() > 100){
				//>990, all
				//>900, %5
				//>500, %10
				//>100, %50
				//%100
				if (k > 990) {}
				else if (k > 900 && (k % 5 != 0)) continue;
				else if (k > 500 && (k % 10 != 0)) continue;
				else if (k > 100 && (k % 50 != 0)) continue;
				else if (k % 100 != 0) continue;

			}

			//Case 3: Size of Arr Less than 100
			else {
				//>90, all
				//>50, %5
				//>10, %10
				if (k > 90){}
				else if (k > 50 && (k % 5 != 0)) continue;
				else if (k > 10 && (k % 10 != 0)) continue;
			}
			fprintf(gnuplotPipe, "%ld %lf \n", (int) xVals[k], yVals[k]);
		}
		fprintf(gnuplotPipe, "e\n");
	}
	fflush(gnuplotPipe);
	cout << red << "Please ensure that you have closed the graph before continuing! Press any key to continue" << endl;
	cin.get();
	cin.get();
	return 0;
}