#include <math.h>

#include "Ball.h"



Ball::Ball()
{
}

Ball::Ball(float rad, float pos_x, float pos_y)
{
	x = pos_x;
	y = pos_y;
	radius = rad;
	direction_x = 1;
	direction_y = 1;
	angle = acos(0);
}


Ball::~Ball()
{
}
