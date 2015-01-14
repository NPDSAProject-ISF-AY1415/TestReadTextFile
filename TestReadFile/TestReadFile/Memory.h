#include <Windows.h>
#include <Psapi.h>

SIZE_T getVMUsed();
SIZE_T getPMUsed();
SIZE_T getPeakPMUsed();