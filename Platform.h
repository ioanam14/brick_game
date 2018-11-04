#pragma once
class Plaform
{
public:
	Plaform();
	Plaform(float pos_x, float pos_y, float len);
	~Plaform();

	float x;
	float y;
	float lenght;
	float height;
};
