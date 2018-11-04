#pragma once
class Brick
{
public:
	Brick();
	Brick(float pos_x, float pos_y);
	~Brick();
	float x, y;
	float visible;
	
	static const float WIDTH;
	static const float HEIGHT;
};

