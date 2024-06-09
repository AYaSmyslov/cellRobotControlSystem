#include "Robot.h"

#include <iostream>

Robot::Robot(const std::vector<int> &a_pos)
    : _x(a_pos[0]),
    _y(a_pos[1]),
    _z(a_pos[2])
{
    
}



Robot::~Robot()
{
}



void Robot::setPos(const std::vector<int> &a_pos)
{
    _x = a_pos[0];
    _y = a_pos[1];
    _z = a_pos[2];
}



void Robot::setPos(const int &a_x, const int &a_y, const int &a_z)
{
    _x = a_x;
    _y = a_y;
    _z = a_z;
}



void Robot::setDir(const int &a_dir)
{
    double tmp = std::fmod(double(a_dir*60), 360.0);
    if (tmp < 0) {
        tmp += 360.0;
    }
    _direction = int(tmp/60);
}



std::vector<int> Robot::getPos() const
{
    std::vector<int> pos {_x, _y, _z};
    return pos;
}



int Robot::getDir()
{
    return _direction;
}