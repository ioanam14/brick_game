#pragma once

#include "GameObject.h"

class Brick : public GameObject
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

