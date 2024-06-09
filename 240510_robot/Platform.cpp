#include "Platform.h"

Platform::Platform(const int &a_x, const int &a_y, const int &a_z)
    : _x(a_x),
    _y(a_y),
    _z(a_z)
{  
}

Platform::Platform(const std::vector<int> &a_pos)
    : _x(a_pos[0]),
    _y(a_pos[1]),
    _z(a_pos[2])
{
}



Platform::~Platform()
{
}



std::vector<int> Platform::getPos() const
{
    std::vector<int> pos {_x, _y, _z};
    return pos;
}