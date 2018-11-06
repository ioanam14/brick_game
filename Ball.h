#pragma once

class Ball
{
public:
	Ball();
	Ball(float rad, float pos_x, float pos_y);
	~Ball();

	float x, y;
	float radius;
	int direction_x;
	int direction_y;
	float angle;
};
