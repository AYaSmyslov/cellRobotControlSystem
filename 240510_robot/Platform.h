#pragma once

#include <vector>

enum PlatformState {
    FREE,
    WALL,
    EXIT
};

class Platform
{
public:
	Platform(const int &a_x=0, const int &a_y=0, const int &a_z=0, const PlatformState &a_state = FREE);
	Platform(const std::vector<int> &a_pos = {0,0,0}, const PlatformState &a_state = FREE);
	~Platform();

	void setPos(const std::vector<int> &a_pos);
	void setPos(const int &a_x=0, const int &a_y=0, const int &a_z=0);
	void setState(const PlatformState &a_state);

	std::vector<int> getPos() const; 
	PlatformState getState();

private:
	int _x;
	int _y;
	int _z;
	PlatformState _state = FREE;
};
