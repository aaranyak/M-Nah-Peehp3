#include <iostream>
typedef uint64_t U64;
void printAsBin(long n)
{
  std::cout << "0";
  uint64_t i = 1;
  i <<= 63;
  for ( i; i > 0; i = i / 2)
  {
    if((n & i) != 0)
    {
      std::cout << "1";
    }
    else
    {
      std::cout << "0";
    }
  }
    std::cout << "\n";
}
