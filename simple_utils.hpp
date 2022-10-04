#include <iostream>
#include <string.h>
#include <math.h>
typedef uint64_t U64;
using namespace std;
string printAsBin(long n)
{
  std::cout << "0";
  uint64_t i = 1;
  i <<= 63;
  string retval = "";
  for ( i; i > 0; i = i / 2)
  {
    if((n & i) != 0)
    {
      retval += "1";
    }
    else
    {
      retval += "0";
    }
  }
  return retval;
}