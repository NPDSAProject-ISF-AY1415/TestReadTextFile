#include "plotGraph.h"
#define MAX_POINTS 5

//Command is something that goes
//"plot <data> title <title>[, <2nd data> title <2nd title>,]..."

using namespace eku;

int plotGraph(List &graphList){
	FILE * gnuplotPipe = _popen("gnuplot -persistent", "w");
	fprintf(gnuplotPipe, "set title \"Unsorted Pointer Based Array\" \n");
	//Set The Display, Add, Remove, Binary Search, Sequential Search
	fprintf(gnuplotPipe, "set xtics offset character 0,0,0 norangelimit (\"Add\" 1, \"Remove\" 2, \"Display\" 3, \"Binary Search\" 4, \"Sequential Search\" 5) \n");
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
		for (int k = 0; k < MAX_POINTS; k++)
		{
			double* yVals = g.getValues();
			//fprintf(gnuplotPipe, "%lf %lf \n", xVals[i], yVals[i]);
			//cout << k+1 << " : " << yVals[k] << " ";
			fprintf(gnuplotPipe, "%ld %lf \n", k + 1, yVals[k]);
		}
		fprintf(gnuplotPipe, "e\n");
	}
	fflush(gnuplotPipe);
	cout << red << "Please ensure that you have closed the graph before continuing! Press any key to continue" << endl;
	cin.get();
	cin.get();
	return 0;
}