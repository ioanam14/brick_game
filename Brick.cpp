#include "Brick.h"

const float Brick::WIDTH = 0.2f;
const float Brick::HEIGHT = 0.15f;

Brick::Brick()
{
}

Brick::Brick(float pos_x, float pos_y)
{
	x = pos_x;
	y = pos_y;
	visible = 10;
}

void Brick::DecreaseVisibility() {
	visible -= 1;
}


Brick::~Brick()
{
}
