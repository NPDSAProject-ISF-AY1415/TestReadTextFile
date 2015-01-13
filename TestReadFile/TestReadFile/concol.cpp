#include "concol.h"

using namespace eku;

HANDLE eku::std_con_out;
//Standard Output Handle
bool eku::colorprotect = false;
//If colorprotect is true, background and text colors will never be the same
eku::concol eku::textcol, eku::backcol, eku::deftextcol, eku::defbackcol;
/*textcol - current text color
backcol - current back color
deftextcol - original text color
defbackcol - original back color*/