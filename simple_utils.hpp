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

int getFileFromCN(char file) {
  if (file == 'a') {
    return 0;
  }
  if (file == 'b') {
    return 1;
  }
  if (file == 'c') {
    return 2;
  }
  if (file == 'd') {
    return 3;
  }
  if (file == 'e') {
    return 4;
  }
  if (file == 'f') {
    return 5;
  }
  if (file == 'g') {
    return 6;
  }
  if (file == 'h') {
    return 7;
  }
  else {
    return -1;
  }
}