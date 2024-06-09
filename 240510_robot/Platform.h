#pragma once

#include <vector>

class Platform
{
public:
	Platform(const int &a_x=0, const int &a_y=0, const int &a_z=0);
	Platform(const std::vector<int> &a_pos = {0,0,0});
	~Platform();

	void setPos(const std::vector<int> &a_pos);
	void setPos(const int &a_x=0, const int &a_y=0, const int &a_z=0);
	std::vector<int> getPos() const; 

private:
	int _x;
	int _y;
	int _z;
};
