#ifndef MEM_TOOL
#define MEM_TOOL


#include <Windows.h>
#include <Psapi.h>
#include "concol.h"
#include "Utility.h"
#include <sstream>

SIZE_T getVMUsed();
SIZE_T getPMUsed();
SIZE_T getPeakPMUsed();
SIZE_T convertToMB(SIZE_T bytes);
SIZE_T convertToKB(SIZE_T bytes);
string convertMemoryToHumanReadable(SIZE_T bytes);
string convertMemoryToHumanReadableSht(SIZE_T bytes);
void printMemoryInfo();

#endif