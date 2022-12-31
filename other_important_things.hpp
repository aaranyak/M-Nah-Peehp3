#include "utilfuncs.hpp"
string printAsBoard(long n)
{
  uint64_t i = 1;
  i <<= 63;
  string retval = "";
  for ( i; i > 0; i = i / 2)
  {
    if((n & i) != 0)
    {
      retval += " 1";
    }
    else
    {
      retval += " .";
    }
    if (bitScanForward(i) % 8 == 0) {
      retval += "\n";
    }
  }
  return retval;
}