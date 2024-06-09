#include "Platform.h"

Platform::Platform(const int &a_x, const int &a_y, const int &a_z, const PlatformState &a_state)
    : _x(a_x),
    _y(a_y),
    _z(a_z),
    _state(a_state)
{  
}

Platform::Platform(const std::vector<int> &a_pos, const PlatformState &a_state)
    : _x(a_pos[0]),
    _y(a_pos[1]),
    _z(a_pos[2]),
    _state(a_state)
{
}



Platform::~Platform()
{
}



void Platform::setState(const PlatformState &a_state)
{
    _state = a_state;
}



std::vector<int> Platform::getPos() const
{
    std::vector<int> pos {_x, _y, _z};
    return pos;
}



PlatformState Platform::getState()
{
    return _state;
}