#include "Memory.h"

using namespace std;

DWORDLONG getTotalVirtualMem(){
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	return memInfo.ullTotalPageFile;
}


DWORDLONG getUsedVirtualMem(){
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	return memInfo.ullTotalPageFile - memInfo.ullAvailPageFile;
}