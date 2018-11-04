#pragma once
class Wall
{
public:
	Wall();
	Wall(float pos_x, float pos_y, float scaleX, float scaleY);
	~Wall();

	float x, y;
	float scale_x, scale_y;
};