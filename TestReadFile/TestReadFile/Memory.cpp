#include "Memory.h"

using namespace std;

SIZE_T getVMUsed(){
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
	SIZE_T virtualMemUsedByMe = pmc.PagefileUsage;
	return virtualMemUsedByMe;
}


SIZE_T getPMUsed(){
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
	SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
	return physMemUsedByMe;
}

SIZE_T getPeakPMUsed(){
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
	SIZE_T physMemUsedByMe = pmc.PeakWorkingSetSize;
	return physMemUsedByMe;
}

