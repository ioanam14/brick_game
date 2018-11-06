#pragma once

class Brick
{
public:
	Brick();
	Brick(float pos_x, float pos_y);
	~Brick();

	void Brick::DecreaseVisibility();

	float x, y;
	int visible;
	
	static const float WIDTH;
	static const float HEIGHT;
};

