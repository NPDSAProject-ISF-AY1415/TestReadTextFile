#include "Memory.h"

using namespace std;
using namespace eku;
using namespace utility;

/*
Gets the total Virtual Memory (Page File) that is used by the process
@return Total VM Used in bytes
*/
SIZE_T getVMUsed(){
	PROCESS_MEMORY_COUNTERS_EX pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *) &pmc, sizeof(pmc));
	SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
	return virtualMemUsedByMe;
}

/*
Gets the total Physical Memory (RAM) that is used by the process
@return Total RAM Used in bytes
*/
SIZE_T getPMUsed(){
	PROCESS_MEMORY_COUNTERS_EX pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *)&pmc, sizeof(pmc));
	SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
	return physMemUsedByMe;
}

/*
Gets the Peak Physical Memory (RAM) that is used by the process
@return Peak RAM Used in bytes
*/
SIZE_T getPeakPMUsed(){
	PROCESS_MEMORY_COUNTERS_EX pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *)&pmc, sizeof(pmc));
	SIZE_T physMemUsedByMe = pmc.PeakWorkingSetSize;
	return physMemUsedByMe;
}

/*
Converts Bytes to MB
@param bytes Bytes to convert
@return Megabytes after conversion
*/
SIZE_T convertToMB(SIZE_T bytes){
	//1MB = 1024KB = 1048576B
}

/*
Converts Bytes to KB
@param bytes Bytes to convert
@return Kilobytes after conversion
*/
SIZE_T convertToMB(SIZE_T bytes){
	//1KB = 1024B
}

/*
Converts Bytes to KB
@param bytes Bytes to convert
@return String of properly formatted code
*/
string convertMemoryToHumanReadable(SIZE_T bytes){
	if (bytes > 1048576)	//MB
		return convertToMB(bytes) + " MB";
	if (bytes > 1024)		//KB
		return convertToKB(bytes) + " KB";
	//Bytes
	return bytes + " B";
}

void printMemoryInfo(){
	cout << endl;
	cout << yellow << "==========================" << white << endl;
	cout << red << "       Memory Usage       " << white << endl;
	cout << yellow << "==========================" << white << endl;
	cout << white << "Virtual Memory: " << gray << convertMemoryToHumanReadable(getVMUsed()) << endl;
	cout << white << "Physical Memory: " << gray << convertMemoryToHumanReadable(getPMUsed()) << endl;
	cout << white << "Peak Physical Memory: " << gray << convertMemoryToHumanReadable(getPeakPMUsed()) << endl;
	cout << yellow << "==========================" << white << endl;
	cout << endl;
}