#include <utils.h>

using namespace std;

ostream& operator<<(ostream &os, const uint8_t value)
{
    return os << (int)value;
}

ostream& operator<<(ostream &os, const array<uint8_t,9> &grid)
{
    for(uint8_t i = 0; i < 3; ++i)
    {
        for(uint8_t j = 0; j < 2; ++j)
        {
            os << grid[i*3+j] << " ";
        }
        os << grid[i*3+2] << endl;
    }

    return os;
}
