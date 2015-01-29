#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <iostream>
#include <array>

using namespace std;

ostream & operator<<(ostream & os, uint8_t const value);
ostream & operator<<(ostream & os, array<uint8_t,9> const & grid);

#endif // UTILS_H_INCLUDED
