#include "Wall.h"



Wall::Wall()
{
}

Wall::Wall(float pos_x, float pos_y, float scaleX, float scaleY) 
{
	x = pos_x;
	y = pos_y;
	scale_x = scaleX;
	scale_y = scaleY;
}


Wall::~Wall()
{
}
