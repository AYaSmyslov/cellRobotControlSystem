#pragma once

#include <vector>

class Robot
{
public:
	Robot(const std::vector<int> &a_pos = {0,0,0});
	~Robot();

	void setPos(const std::vector<int> &a_pos);
	void setPos(const int &a_x=0, const int &a_y=0, const int &a_z=0);
	void setDir(const int &a_dir);
	std::vector<int> getPos() const; 
	int getDir();

private:
	int _x;
	int _y;
	int _z;
	int _direction = 0;
};
