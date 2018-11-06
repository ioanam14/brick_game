#pragma once

class Powerup
{
public:
	Powerup();
	~Powerup();

	float x, y;
	bool floating;
	bool active;
	float time;

	static const float WIDTH;
	static const float HEIGHT;
};
